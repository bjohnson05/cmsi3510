
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
   for( i = 0; i < 5; i++ ) {
      printf( "   First loop: myRA2[i] as int: %d ~ myRA2[i] as float: %f ~ myRA2[i] as char: %c\n", myRA2[i], (float)myRA2[i], (myRA2[i]+48) );
   }

   printf( "%s\n", s );

   for( i = 0; i < 10; i++ ) {
      myRA1[i] = i * 2;
   }
   for( i = 0; i < 10; i++ ) {
      printf( "   Second loop: myRA1[i] as int: %d ~ myRA1[i] as float: %f ~ myRA1[i] as char: %c\n", myRA1[i], (float)myRA1[i], (myRA1[i]+48) );
   }

  // in Java this would be:
  //   public static void main( String[] args ) {}
  //      System.out.println( "\n   Hello, world!\n\n" );
  //      System.exit( 0 );
  //   }
   printf( "\n   Hello, world!\n\n" );
   exit( 0 );

}
