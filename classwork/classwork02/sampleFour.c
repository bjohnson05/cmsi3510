#include <stdio.h>
   #define  MAXLINE  100

   int getline( char line[], int maxline );
   void copy( char to[], char from[] );

  /* main program - what does this actually *DO*?? */
   int main( int argc, char * argv[] ) {

      int len;             /* current line length */
      int max;             /* maximum length seen so far */
      char line[MAXLINE];
      char longest[MAXLINE];

      max = 0;

      while( (len = getline( line, MAXLINE )) > 0 ) {
         if( len > max ) {
            max = len;
            copy( longest, line );
         }
      }
      if( max > 0 ) {
         printf( "%s", longest );
      }
      return 0;

   }

  /* read a line into string s, and return the length */
   int getline( char s[], int lim ) {

      int c, i;

      for( i = 0; ((i < lim - 1) && ((c = getchar()) != EOF) && (c != '\n')); ++i ) {
         s[i] = c;
      }
      if( c == '\n' ) {
         s[i] = c;
         ++i;
      }
      s[i] = '\0';
      return i;

   }

  /* copy values in "from[]" into "to[]"; assume that "to[]" is big enough! */
   void copy( char to[], char from[] ) {

      int i = 0;

      while( (to[i] = from[i]) != '\0' ) {
         ++i;
      }

   }
