
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char * argv[] ) {

   char input[25];
   printf( "\n\b   What is your name? " );
   gets( input );
   printf( "\n   Greetings, Earthling %s!\n\n", input );
   exit( 0 );

}
