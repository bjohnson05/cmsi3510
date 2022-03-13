/**
 * filename: randTest.c
 * purpose: prints some info about the rand() function
 * author: Dr. Johnson
 * date: 2022-03-06
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char * argv [] ) {

   printf( "\n\n   Info for this compiler for rand(): \n" );
   printf( "   RAND_MAX   in long unsigned: %lu\n", RAND_MAX );
   printf( "   RAND_MAX^2 in long unsigned: %lu\n", RAND_MAX * RAND_MAX );
//   printf( "   RAND_MAX^3 in long unsigned: %lu\n", RAND_MAX * RAND_MAX * RAND_MAX );
   printf( "   Raw random number in long unsigned: %lu\n", rand() );
   printf( "   Seeding random number generator\n" );
   srand( time( 0 ) );
   printf( "   Raw random number in long unsigned: %lu\n", rand() );
   printf( "   rand() \% RAND_MAX in long unsigned: %lu\n", (rand() % RAND_MAX) );
   printf( "   rand() \% RAND_MAX^2 in long unsigned: %lu\n", (rand() % (RAND_MAX * RAND_MAX)) );

   return( 0 );

}
