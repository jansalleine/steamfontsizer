#ifndef STEAMFONTSIZER_H_
#define STEAMFONTSIZER_H_

#define VERSION     "1.0"

int get_font_size_from_string( char *string );
char *newstr( char *initial_str );
char *string_replace( char *search, char *replace, char *string );
void print_info();
void print_help();

#endif // STEAMFONTSIZER_H_
