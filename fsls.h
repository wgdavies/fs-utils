/**
 * @file
 *
 * fsls - header file fast/filesystem list
 *
 */

/** Set up the header guard to prevent re-initialising the variables
 */
#ifndef FSLS_HEADER
#define FSLS_HEADER 1

/** This enables GNU asprintf functionality under GLibC stdio.h
 *  Would this be better under LLVM/Clang/BSD? Other than the obvious? 
 */
#define _GNU_SOURCE

/** Libraries needed by source files
 */
#include <dirent.h>  /// Defines DT_* constants
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <popt.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/syscall.h>

/** My name
 */
#define PROGNAME "fsls"

/** Include a message when a given feature is unimplemented
 */
#define UNIMPL "[**CURRENTLY UNSUPPORTED**] "

/** Global error macro
 */
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

/** Global Directory Arg
 *  This is the argument variable that is passed between source file functions.
 */
extern char *g_dir_arg;

/** Global return value declaration
 *  Since this is static, it can be defined privately in each source; this just sets the standard.
 */
static int ret_val;

/** Global function prototypes
 */
extern int quickcount( char *g_dir_arg );
extern int getdirent( char *g_dir_arg );

/** Close the header file.
 */
#endif
