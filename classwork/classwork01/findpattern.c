/**
 * filename:   findpattern.c
 * purpose:    "C" program demonstration
 * author:     Dr. Johnson
 * date:       2023-01-11
 * SEE:        K&R book second edition, page 69
 */

#include <stdio.h>

#define MAXLINE 1000

int getLine( char line[], int max );
int strIndex( char source[], char searchFor[] );

char pattern[] = "ould";

int main( int argc, char * argv[] ) {

   char line[MAXLINE];
   int  found = 0;

   while( getLine( line, MAXLINE ) > 0 ) {
      if( strIndex( line, pattern ) >= 0 ) {
         printf( "%s", line );
         found++;
      }
   }
   return found;
}

/**
 * the 'getLine()' function declared above
 *   gets a line into 's', and return the length
 */
int getLine( char s[], int limit ) {

   int c;
   int i = 0;

   while( --limit > 0 && (c = getchar()) != EOF && c != '\n' ) {
      s[i++] = c;
   }
   if( c == '\n' ) {
      s[i++] = c;
   }
   s[i] = '\0';
   return i;
}

/**
 * the 'strIndex()' function declared above
 *    finds if the target exists in the source string
 *    and returns the integer of the location of the
 *    first character of the target in the source
 */
int strIndex( char s[], char t[] ) {

   int i, j, k;
   for( i = 0; s[i] != '\0'; i++ ) {
      for( j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++ ) {
         ;   // nothing left to do, it's all in the 'for' statement
      }
      if( k > 0 && t[k] == '\0' ) {
         return i;
      }
   }
   return -1;
}
