// Because C has expressions like Java, we can write this as:
#include <stdio.h>

int main( int argc, char * argv[] ) {

   int c;

   ;
   while( (c = getchar()) != EOF ) {
      putchar( c );
   }
}
