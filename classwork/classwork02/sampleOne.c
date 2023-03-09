#include <stdio.h>
#include <stdlib.h>

#define MY_SYMBOLIC_CONSTANT 23

int main( int argc, char * argv[] ) {

   char s[] = "This is a test string";
   int myRA1[10];
   int myRA2[5];

   int i = 0;
   for( i = 0; i < 5; i++ ) {
      myRA2[i] = i + 1;
   }

   for( i = 0; i < 10; i++ ) {
      myRA1[i] = i * 2;
   }

   printf( "\n  Sample Program #1\n" );
   printf( "Value of 's': %s\n", s );
   for( i = 0; i < 5; i++ ) {
      printf( "Value of 'myRA2[%d]': %d\n", i, myRA2[i] );
   }
   for( i = 0; i < 10; i++ ) {
      printf( "Value of 'myRA1[%d]': %d\n", i, myRA1[i] );
   }
   exit( 0 );
}
