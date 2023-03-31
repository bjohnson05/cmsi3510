/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *    filename :  CI-pc.c  [Command Intepreter - PC version
 *    purpose  :  Sample command line intepreter program that uses execlp to execute commands
 *    author   :  Dr. Johnson
 *    date     :  2020-04-08
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
   #include <process.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <windows.h>

   #define  TRUE     1

   int main() {
      char input[25];
      int  retval = 0;

     // loop forever until the user inputs "exit"
      while( TRUE ) {

        // put up a prompt
         printf( "Need input [one word only] <== " );

        // read the user input
         if( NULL == gets( input ) ) {   // Note this produces a warning!
            printf( "\n   Sorry, can't do that....\n\n" );
            return -1;
         }

        // check for the word "exit" to quit
         if( 0 == strncmp( input, "exit", 4 ) ) {        // provides a way to "quit"
            return 0;

        // it's not "exit" so fork a new child process to handle the command
         } else {
            retval = _execlp( input, input, "_execlp", "two", NULL );
            if( retval < 0 ) {
               perror( "error forking" );
               return -1;
            }

           // wait for the forked child to finish
              Sleep( 1000 );
         }
      }
   }
