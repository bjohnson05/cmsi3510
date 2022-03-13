#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define  TRUE     1

int main() {
   char input[25];
   int  retval = 0;

   while( TRUE ) {            // loop until return
      printf( "Need input [one word only] <== " );

      if( NULL == gets( input ) ) {
         printf( "\n   Sorry, can't do that....\n\n" );
         return -1;
      }

      if( 0 == strncmp( input, "exit", 4 ) ) {       // provides a way to "quit"
         return 0;

      } else {
         pid_t returnedValue = fork();          // fork a new copy of this environment

         if( returnedValue < 0 ) {
            perror( "error forking" );
            return -1;

         } else if( returnedValue == 0 ) {
            retval = execlp( input, input, NULL );
            perror( input );
            return -1;

         } else {
            // printf( "      [after execlp call, retval is: %d\n]", retval );
            if( waitpid( returnedValue, 0, 0 ) < 0 ) {
               perror( "error waiting for child" );
               return -1;
            }
         }
      }
   }
}
