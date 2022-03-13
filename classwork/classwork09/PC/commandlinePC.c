#include <stdio.h>
#include <string.h>
#include <process.h>
#include <windows.h>

#define  TRUE     1

int main() {

   STARTUPINFO info;
   PROCESS_INFORMATION pInfo;
   char input[25];

   while( TRUE ) {            // loop until return
      printf( "\n   Need input [one word only] <== " );

      if( NULL == gets( input ) ) {                   // Note that this may produce a warning!
         printf( "\n   Sorry, can't do that....\n\n" );
         return -1;
      }

      if( 0 == strncmp( input, "exit", 4 ) ) {        // provides a way to "quit"
         return 0;

      } else {
//         if( -1 == _execlp( input, input, "dir", "/o:gn", NULL ) ) {
         if( CreateProcessA( NULL, "C:\\Windows\\System32\\cmd.exe", NULL, NULL, FALSE, 0, NULL, NULL, &info, &pInfo ) ) {
            perror( "error forking" );
            return -1;

         } else {
            WaitForSingleObject( pInfo.hProcess, INFINITE );
            CloseHandle( pInfo.hProcess );
            CloseHandle( pInfo.hThread );
         }
      }
   }
}
