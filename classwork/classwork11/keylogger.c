/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *    file: keylogger.c
 *    demonstrates system calls for mac/linux/unix
 *    @see https://securelist.com/keyloggers-how-they-work-and-how-to-detect-them-part-1/36138/
 *    @see https://securelist.com/keyloggers-implementing-keyloggers-in-windows-part-two/36358/
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// the "main()" begins here
//
int main( int argc, char * argv[] ) {

   char * filename;
   FILE * fd;

   // Check to make sure there are enough arguments to run, but not too many
   if( 1 == argc ) {
      filename = "c:\\temp\\logger.txt";     // default file name
   } else if( 2 == argc ) {
      strcpy( filename, argv[1] );           // user-supplied file name
   } else {
      printf( "\nsorry, too many arguments\n" );
      exit( 0 );
   }
   printf( "logging to file %s\n", filename );

  // open the key logger file, notify the user either success or failure
  //  open the file for "appending" so we can add to it every time
   fd = fopen( filename, "a" );
   if( NULL == fd ) {
      printf( "...can't open file %s\n", filename );
      exit( 0 );
   } else {
      printf( "\n   log file open\n\n" );
   }


   printf( "     This line will be output to the file!\n\n" );
   fprintf( fd, "     This line will be output to the file!\n" );

  // close the file for next time
   fclose( fd );
   return EXIT_SUCCESS;
}

