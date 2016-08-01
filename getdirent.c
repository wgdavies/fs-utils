/** 
 *  @file
 *
 *  fsls - statistical model fast/filesystem list
 *
 *  @see http://webcache.googleusercontent.com/search?q=cache:3yIPmymklX8J:be-n.com/spw/you-can-list-a-million-files-in-a-directory-but-not-with-ls.html+&cd=1&hl=en&ct=clnk&gl=us
 *  @see getdents(2)
 *  @see nftw(3)
 *  @see fts(3)
 *  @see https://github.com/xaionaro/libpftw
 */

#define BUF_SIZE 1024*1024*8

struct linux_dirent {
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

int getdirent( char *g_dir_arg )
{
    int fd, nread, bpos;
    char d_type, buf[BUF_SIZE];
    unsigned long d_regular, d_directory, d_buffer, d_socket, d_symlink, d_block_sp, d_char_sp, d_unknown;
    struct linux_dirent *d;
    
    d_regular = d_directory = d_buffer = d_socket = d_symlink = d_block_sp = d_char_sp = d_unknown = 0;
    fd = open(g_dir_arg, O_RDONLY | O_DIRECTORY);

    if ( fd == -1 ) handle_error("open");
    
    for ( ; ; ) {
	nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);

	if ( nread == -1 ) handle_error("getdents");
	if ( nread ==  0 ) break;

	for ( bpos = 0 ; bpos < nread ; ) {
	    d = (struct linux_dirent *) (buf + bpos);
	    d_type = *(buf + bpos + d->d_reclen - 1);

	    switch(d_type) {
	    case DT_REG: ++d_regular; break;
	    case DT_DIR: ++d_directory; break;
	    case DT_FIFO: ++d_buffer; break;
	    case DT_SOCK: ++d_socket; break;
	    case DT_LNK: ++d_symlink; break;
	    case DT_BLK: ++d_block_sp; break;
	    case DT_CHR: ++d_char_sp; break;
	    case DT_UNKNOWN: ++d_unknown; break;
	    }

	    bpos += d->d_reclen;
	}
    }
    
    d_directory = d_directory - 2; /// remove '.' and '..' from count list

    printf("Directory: %s\n", g_dir_arg);
    printf("%20s: %lu\n", "regular file", d_regular);
    printf("%20s: %lu\n", "subdirectory", d_directory);
    printf("%20s: %lu\n", "FIFO buffer", d_buffer);
    printf("%20s: %lu\n", "socket", d_socket);
    printf("%20s: %lu\n", "symlink", d_symlink);
    printf("%20s: %lu\n", "block device", d_block_sp);
    printf("%20s: %lu\n", "character special", d_char_sp);
    
    return nread;
}
