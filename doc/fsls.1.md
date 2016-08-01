% FSLS(1) USER MANUAL
% Walter Davies <Walter.Davies1@aexp.com>; BigData Automation Engineering <BigDataAutomationEngineering3@aexp.com>
% July 2016

# NAME

fsls - Fast/Filesystem List

# SYNOPSIS

fsls [*options*] [*directory*]

# DESCRIPTION

`fsls` is a utility program for very quickly returning **approximate** numbers of directory entries. A typical example is finding the number of files in a filesystem directory where the number of files may be in the hundreds of thousands or higher. Using the standard filesystem `ls` command may take many minutes or even several hours depending on system load and network speed, amongst other factors. Under similar circumstances, however, `fsls` has been shown to return results within a matter of minutes*.

The secret to this rapid return is in the **approximate** nature of the number of entries returned. On the one hand the number is precise, but in its most basic (that is, fastest) operation, `fsls` is only counting up the number of inode entries for the specified directory. That means files, directories, symlinks, hardlinks, sockets, &c -- anything that has an inode entry -- is counted. This makes `fsls` ideal -- and fastest -- for counting up files in directories where it is known that there are a large number of files but no other entry types, e.g subdirectories, symlinks, &c.

`fsls` can also be used to collect and print directory statistics and do so rapidly by virtue of parallel threads.

*[Some very ad-hoc testing showed speed increases everywhere from 2x to over 60x versus standard filesystem `ls`. Although many factors affect directory access, the speed differential tends to be geometric; that is, the fewer the number of files, the closer the completion time will be between `fsls` and `ls`. Thus, on the order of 10k files, `fsls` might complete in 1 - 3 seconds whereas `ls` will complete in 4 - 8 seconds but on the order of 500k files, standard `ls` might not complete for over 5 minutes whereas `fsls` can complete in under 5 seconds.]

# OPTIONS

In its basic form, `fsls` prints the number of directory entries for the specified (or current) directory (minus the entries '.' and '..'). With no options or directory specified, returns the number of entries for the current working directory. `fsls` may only take one directory argument (though c.f the `descend` option, below); if more than one directory is specified, `fsls` will print a brief usage statement and exit with an error. See also **[EXAMPLES]**. Additional functionality may be gained using the following options:

-d, \--descend [**CURRENTLY UNSUPPORTED**]
:	Count up the number of files, sockets, symlinks, &c for **all** directories below the specified directory. This option causes a new `fsls` thread to spin up for each directory entry found and return the results when available. Note that this option still returns a single number for **all** entries under the specified directory. To get more detailed information, see the `stats` and `verbose` options, below.

-s, \--stats
:	Print a list of all file types found. This can be useful for double-checking that a given directory really does only contain files or, in combination with the `descend` option, for seeing the balance of files inside a directory structure (e.g comparing two different test or use-case directories).

-v, \--verbose [**CURRENTLY UNSUPPORTED**]
:	When used with the `descend` option, print the individual entry count for each subdirectory encountered. When used in conjunction with both the `descend` and `stats` options, print the detailed statistics list for **each** directory found under the specified directory. Note the the `verbose` option does not change the `stats` output, otherwise. 

-j, \--json [**CURRENTLY UNSUPPORTED**]
:	Write the output in JSON format rather than key-value pair formatted for the command line. This is most useful for redirecting the output to a REST handler such as the Splunk Forwarder. 

-?, \--help
:	Print a help message showing a brief explanation of each option. 

\--usage
:	Print a short usage statement.

# EXAMPLES

Print the number of directory entries for the current directory:

```
fsls
```

Do the same for /var/tmp:

```
fsls /var/tmp
```

Print a breakdown of the various types of files, [sub]directories, links, sockets, &c under /dev:

```
fsls --stats /dev
```

Show a cumulative count for all directory entries under `/data`:

```
fsls --descend /data
```

Show the count of each subdirectory encountered under `/data`:

```
fsls --descend --verbose /data
```

Show a statistical breakdown of each subdirectory encountered under `/data`:

```
fsls -dsv /data
```

# SEE ALSO

ls (1)

dirent.h (0P)

sys/stat.h (0P)

# COPYRIGHT

Copyright (c) 2016, Walter G Davies

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

