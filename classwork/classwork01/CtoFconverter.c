
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char * argv[] ) {

   double degreesF;
   char   input[25];
   printf( "\n\n   Enter a temperature in degrees Fahrenheit: " );
   fgets( input, sizeof(input), stdin );
   degreesF = atof( input );
   printf( "   %10.3f degrees F is %10.3f degrees C.\n\n", degreesF, (((degreesF - 32.0) * 5.0) / 9.0) );
   exit( 0 );

}
