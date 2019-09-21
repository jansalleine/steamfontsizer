#include <ctype.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "steamfontsizer.h"

int main( int argc, char *argv[] )
{
    char    *infile_name        = NULL;
    char    *infile_nopath      = NULL;
    char    outfile_name[256]   = "";
    char    *outfile_nopath     = NULL;

    char    tempstring[1024]    = "";

    FILE    *infile             = NULL;
    FILE    *outfile            = NULL;

    int     addvalue            = 2;
    int     c                   = 0;
    int     i                   = 0;
    int     out                 = 0;
    int     verbose             = 0;

    print_info();

    if ( ( argc == 1 ) ||
         ( strcmp( argv[1], "-h" ) == 0 ) ||
         ( strcmp( argv[1], "-help" ) == 0 ) ||
         ( strcmp( argv[1], "-?" ) == 0 ) ||
         ( strcmp( argv[1], "--help" ) == 0 ) )
    {
        print_help();
        exit( EXIT_SUCCESS );
    }

    // getopt cmdline-argument handler
    opterr = 1;

    while ( ( c = getopt ( argc, argv, "va:o:" ) ) != -1 )
    {
        switch ( c )
        {
            case 'v':
                verbose = 1;
                printf( "\nVerbose mode\n" );
                break;
            case 'a':
                if ( sscanf( optarg, "%i", &addvalue) != 1 )
                {
                    printf( "\nError: -a needs an integer value for font-size add value\n" );
                    exit( EXIT_FAILURE );
                }
                break;
            case 'o':
                if ( strlen( optarg ) > 255 )
                {
                    printf( "\nError: -o outfile parameter too long\n" );
                    exit( EXIT_FAILURE );
                }
                else
                {
                    strcpy( outfile_name, optarg);
                    out = 1;
                }
                break;
        }
    }

    if ( ( optind ) == argc )
    {
        printf( "\nError: no files specified.\n" );
        exit( EXIT_FAILURE );
    }

    if ( out )
    {
        // create outfile and make sure it's writeable
        outfile = fopen( outfile_name, "w" );
        if ( outfile == NULL )
        {
            printf( "\nError: couldn't create file \"%s\".\n", outfile_name );
            exit( EXIT_FAILURE );
        }
        else
        {
            fclose( outfile );
        }
        outfile_nopath = basename( outfile_name );
    }

    infile_name = newstr( argv[optind] );
    infile_nopath = basename( infile_name );

    if ( verbose )
    {
        printf( "\n" );
        printf( "infile filename:       %s\n", infile_nopath );
        if ( out )
        {
            printf( "outfile filename:      %s\n", outfile_nopath );
        }
        else
        {
            printf( "output to stdout\n" );
        }
    }

    infile = fopen( infile_name, "r" );
    if ( infile == NULL )
    {
        printf( "\nError: couldn't read file \"%s\".\n", infile_name );
        exit( EXIT_FAILURE );
    }

    if ( fgets( tempstring, 1000, infile )!= NULL )
    {
        if ( out )
        {
            fputs( tempstring, outfile );
        }
        else
        {
            puts( tempstring );
        }
    }

    if ( out )
    {
        fclose( outfile );
    }
    fclose( infile );
    exit( EXIT_SUCCESS );
}

// string helper functions

char *newstr( char *initial_str )
{
    int num_chars;
    char *new_str;

    num_chars = strlen( initial_str ) + 1;
    new_str = malloc ( num_chars );

    strcpy ( new_str, initial_str );

    return new_str;
}

// print stuff

void print_info()
{
    const char* version = VERSION;

    printf( "=============================================\n" );
    printf( "steamfontsizer - Version %s\n", version );
    printf( "=============================================\n" );
    printf( "\n" );
}

void print_help()
{
    printf( "\nUsage:\n");
    printf( "   steamfontsizer [OPTION(s)] [FILE]\n" );
    printf( "\n" );
    printf( "Options:\n" );
    printf( "   -a NUMBER       add NUMBER to font size\n" );
    printf( "                   (default value: 2)\n" );
    printf( "   -h, --help      display this helpscreen\n");
    printf( "   -o FILE         specify output file\n" );
    printf( "                   (default stdout)\n" );
    printf( "   -v              verbose mode\n" );
    printf( "\n" );
}
