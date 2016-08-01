/** 
 *  @file
 *
 *  fsls - simplest and fastest fast/filesystem list
 *
 */

int quickcount( char *g_dir_arg )
{
    int ret_val = 0;
    unsigned long numfiles = 0;
    struct dirent *dir;
    DIR *d;

    d = opendir(g_dir_arg);
    
    while ( (dir = readdir(d)) != NULL ) {
	++numfiles;
    }
	
    ret_val = closedir(d);
    
    printf("%s entry count: %lu\n", g_dir_arg, numfiles - 2);

    return ret_val;
}
