/**
 * @file
 *
 * fsls - control program fast/filesystem list
 */

/// All library inclusions are performed by the project header
#include "fsls.h"

/// Initialise all global variables
char *g_dir_arg;

/** Process command line arguements and decide how to proceed.
 *  Includes explanatory text for inline help and self-documentation.
 */
int main( int argc, char *argv[] )
{
    int descend_flag = 0, hadoop_flag = 0, stats_flag = 0, verbose_flag = 0, json_flag = 0;
    int count = 0, ret_val = 0;
    g_dir_arg = "."; /// set the default directory argument to "here"
    poptContext pc;
    struct poptOption po[] = {
	{"descend", 'd', POPT_ARG_NONE, &descend_flag, 0, UNIMPL"Parallelise and descend into subdirectories.", NULL},
	{"stats",   's', POPT_ARG_NONE, &stats_flag,   0, "Print detailed statistics.", NULL},
	{"verbose", 'v', POPT_ARG_NONE, &verbose_flag, 0, UNIMPL"Expand statistics output for each subdirectory.", NULL},
	{"json",    'j', POPT_ARG_NONE, &json_flag,    0, UNIMPL"Write output in JSON format.", NULL},
	POPT_AUTOHELP
	POPT_TABLEEND
    };
    
    pc = poptGetContext(NULL, argc, (const char **)argv, po, 0);
    poptSetOtherOptionHelp(pc, "[directory]");
    
    while ( (count = poptGetNextOpt(pc) ) >= 0 ) {
	printf("poptGetNextOpt return val %d\n", count);
    }

    for ( count = 0 ; poptPeekArg(pc) != NULL ; ++count ) {
	asprintf(&g_dir_arg, (char*)poptGetArg(pc));
	
	if ( count > 0 ) {
	    poptPrintUsage(pc, stderr, 0);
	    goto EXITNOW;
	}
    }
    
    if ( descend_flag + hadoop_flag + stats_flag + verbose_flag + json_flag > 5 ) {
	poptPrintUsage(pc, stderr, 0);
	goto EXITNOW;
    } else {
	if ( descend_flag != POPT_ARG_NONE ) printf("%s: %s %s\n", PROGNAME, UNIMPL, "descend");
	else if ( stats_flag != POPT_ARG_NONE ) ret_val = getdirent(g_dir_arg);
	else if ( verbose_flag != POPT_ARG_NONE ) printf("%s: %s %s\n", PROGNAME, UNIMPL, "verbose");
	else if ( json_flag != POPT_ARG_NONE ) printf("%s: %s %s\n", PROGNAME, UNIMPL, "json");
	else ret_val = quickcount(g_dir_arg);
    }
    
    if ( ret_val == 0 ) { 
	exit(EXIT_SUCCESS);
    } else {
	goto EXITNOW;
    }

EXITNOW:
    exit(EXIT_FAILURE);
}
