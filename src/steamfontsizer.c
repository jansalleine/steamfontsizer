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
    char    *searchstring       = "font-size=";
    char    *pointer_search     = NULL;

    FILE    *infile             = NULL;
    FILE    *outfile            = NULL;

    int     addvalue            = 2;
    int     c                   = 0;
    int     i                   = 0;
    int     out                 = 0;
    int     verbose             = 0;
    int     font_size           = 0;
    int     new_font_size       = 0;

    char    font_size_c[3];
    char    new_font_size_c[3];

    if ( ( argc == 1 ) ||
         ( strcmp( argv[1], "-h" ) == 0 ) ||
         ( strcmp( argv[1], "-help" ) == 0 ) ||
         ( strcmp( argv[1], "-?" ) == 0 ) ||
         ( strcmp( argv[1], "--help" ) == 0 ) )
    {
        print_info();
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
                printf( "\n// Verbose mode\n" );
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
            outfile_nopath = basename( outfile_name );
        }
    }
    else
    {
        outfile = stdout;
    }

    infile_name = newstr( argv[optind] );
    infile_nopath = basename( infile_name );

    if ( verbose )
    {
        printf( "\n" );
        printf( "// infile filename:                %s\n", infile_nopath );
        if ( out )
        {
            printf( "// outfile filename:               %s\n", outfile_nopath );
        }
        else
        {
            printf( "// output to stdout\n" );
        }
        printf( "// value to add to font-size:      %i\n", addvalue );
        printf( "\n" );
    }

    infile = fopen( infile_name, "r" );
    if ( infile == NULL )
    {
        printf( "\nError: couldn't read file \"%s\".\n", infile_name );
        fclose( outfile );
        exit( EXIT_FAILURE );
    }

    while ( fgets( tempstring, 1000, infile ) != NULL )
    {
        i++;
        pointer_search = strstr( tempstring, searchstring );
        if ( pointer_search )
        {
            font_size = get_font_size_from_string( &pointer_search[10] );
            new_font_size = font_size + addvalue;
            if ( ( font_size / 10 ) >= 1 )
            {
                font_size_c[0] = (char)( ( font_size / 10 ) + 48 );
                font_size_c[1] = (char)( font_size - ( ( font_size / 10 ) * 10 ) + 48 );
                font_size_c[2] = '\0';
            }
            else
            {
                font_size_c[0] = (char)( font_size + 48 );
                font_size_c[1] = '\0';
            }
            if ( ( new_font_size / 10 ) >= 1 )
            {
                new_font_size_c[0] = (char)( ( new_font_size / 10 ) + 48 );
                new_font_size_c[1] = (char)( new_font_size - ( ( new_font_size / 10 ) * 10 ) + 48 );
                new_font_size_c[2] = '\0';
            }
            else
            {
                new_font_size_c[0] = (char)( new_font_size + 48 );
                new_font_size_c[1] = '\0';
            }
            string_replace( font_size_c, new_font_size_c, tempstring );
            if ( verbose )
            {
                printf( "// string with font-size found in Line %d, original size: %d, new size: %d\n", i, font_size, new_font_size );
            }
        }
        else
        {

        }
        fputs( tempstring, outfile );
    }

    if ( out )
    {
        fclose( outfile );
    }
    fclose( infile );
    exit( EXIT_SUCCESS );
}

int get_font_size_from_string( char *string )
{
    int font_size = 0;
    int digit_l = -1;
    int digit_r = -1;
    int num_chars = strlen( string );
    int i = 0;
    int curval;
    for ( i = 0; i < num_chars; i++ )
    {
        curval = (int)string[i];
        if ( curval == 34 )
        {
            continue;
        }
        if ( curval == 32 || curval == 13 )
        {
            break;
        }
        if ( digit_l != -1 )
        {
            digit_r = curval;
        }
        else
        {
            digit_l = curval;
        }
    }
    if ( digit_r != -1 )
    {
        font_size = ( 10 * ( digit_l - 48 ) ) + ( digit_r - 48 );
    }
    else
    {
        font_size = digit_l - 48;
    }
    return font_size;
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

char * string_replace( char *search, char *replace, char *string )
{
    char *tempstring, *searchstart;
    int len = 0;

    searchstart = strstr( string, search );
    if ( searchstart == NULL )
    {
        return string;
    }

    tempstring = (char*) malloc( strlen( string ) * sizeof( char ) );
    if ( tempstring == NULL )
    {
        return NULL;
    }

    strcpy( tempstring, string );
    len = searchstart - string;
    string[len] = '\0';
    strcat( string, replace );
    len += strlen( search );
    strcat( string, (char*) tempstring + len );

    free(tempstring);
    return string;
}

// print stuff

void print_info()
{
    const char* version = VERSION;

    printf( "============================\n" );
    printf( "steamfontsizer - Version %s\n", version );
    printf( "============================\n" );
    printf( "\n" );
}

void print_help()
{
    printf( "Usage:\n" );
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
