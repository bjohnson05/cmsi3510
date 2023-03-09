#include <stdio.h>
#include <stdlib.h>

int main( int argc, char * argv ) {

   // declare and initialize some stuff
   double x, y, *p;
   x = 123.45;
   y = 678.9;
   p = 0;

   int a[10];
   int b[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

  // declare an array of 20 int's using malloc()
  //  we ONLY have a pointer to this array, called "c"
   int *c;
   c = (int *)malloc( 20 * sizeof( int ) );
   int *d;
   d = c;      // this keeps the starting value for later

  // initialize the array with the squares 1 through 20
  //  note the 'pointer math' to access the elements
  //  NO SQUARE BRACKETS!
   for( int i = 0; i < 20; i++ ) {
      *c = (i + 1) * (i + 1);
      c++;
   }

   printf( "\n\n   after initialization... " \
           "x is: %f, y is: %f, and p is: %d\n", \
            x, y, p );

   // now assign the pointer p to the address of x
   p = &x;
   printf( "\n\n   after assignment of p... " \
           "x is: %f, y is: %f, and p is: %d\n", \
            x, y, p );

   // now assign the value @ pointer p to y
   y = *p;
   printf( "\n\n   after assignment of y... " \
           "x is: %f, y is: %f, and p is: %d\n", \
            x, y, p );

   // load array 'a' with values
   for( int i = 0; i < 10; i++ ) {
      a[i] = (i + 1) * (i + 1);
   }

   // now display the address of 'a'
   printf( "\n\n   the start of array 'a' is at : " \
           "%d and the value of the first element is: "
           "%d\n", a, a[1] );
   printf( "\n\n   the start of array 'b' is at : " \
           "%d and the value of the first element is: "
           "%d\n", b, b[0] );
   printf( "\n\n   using addresses, the first element "\
           "of 'b' is at %d and the next location " \
           "is at %d\n", &b[0], &b[1] );
   printf( "\n\n   you can also access elements in 'b' "\
           "using pointer math\n    the fourth element in "\
           "b, 'b[3]' is *(b + 3): %d\n", *(b + 3) );

  // restore the pointer to the start of the array, then
  //  loop to output the values using pointer math
   c = d;
   printf( "\n\n   now accessing the array that was done "\
           "using malloc:\n     using pointer math\n" );
   for( int i = 0; i < 20; i++ ) {
      printf( "      *c value: %4d at address %X\n", *c, c );
      c++;
   }

  // restore the pointer to the start of the array, then
  //  loop to output the values USING SQUARE BRACKETS
   c = d;
   printf( "\n\n   now accessing the array that was done "\
           "using malloc:\n     using square brackets\n" );
   for( int i = 0; i < 20; i++ ) {
      printf( "      c[%2d] value: %4d at address %X\n", i, c[i], &c[i] );
   }

   free( c );

}
