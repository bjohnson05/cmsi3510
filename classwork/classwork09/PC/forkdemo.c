#include <unistd.h>
#include <stdio.h>

int main( int argc, char * argv() ) {
   int loopCount = 5;      // each process will get its own copy of loopCount

   printf( "I am still only one process.\n" );

   pid_t returnedValue = fork();
   if( returnedValue < 0 ) {
      // still only one process
      perror( "forking error" ); // report the error
      return -1;

   } else if( returnedValue == 0 ) {
      // this must be the child process
      while( loopCount > 0 ) {
         printf( "I am the child process.\n" );
         loopCount--;      // decrement child's counter only
         sleep( 1 );       // wait a second before repeating
      }

   } else {
      // this must be the parent process
      while( loopCount > 0 ) {
         printf( "I am the parent process; my child's ID is %d\n.", returnedValue );
         loopCount--;      // decrement parent's counter only
         sleep( 1 );       // sleep for one second
      }
   }

   return 0;               // zero means success in POSIX
}
