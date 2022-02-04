// PC version

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// This is the data structure we will use to pass arguments to the children
typedef struct {
   char threadLetter;
   int  secondsToRun;
} MyData;

#define TIME_SLICE 40

// This is the child thread function that will be started by "CreateThread()"
DWORD WINAPI child( LPVOID passedData ) {

   MyData *childData = (MyData*)passedData;           // data struct passed in
   char threadLetter = childData->threadLetter;       // remember the struct is a pointer
   int  timeToLive   = childData->secondsToRun;       //   so we use the "->" to access fields

   // Loop until the time to live expires, then exit
   while( timeToLive >= 0 ) {
      timeToLive -= TIME_SLICE;
      if( timeToLive <= 0 ) {
         if( (timeToLive + TIME_SLICE) != 0 ) {
            printf( "%c:%d:done\n", threadLetter, timeToLive + TIME_SLICE );
         }
      } else {
         printf( "%c:%d:%d\n", threadLetter, TIME_SLICE, timeToLive );
      }
      Sleep( 500 );
   }
   return 0;

}

