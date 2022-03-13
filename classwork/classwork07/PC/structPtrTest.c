/**
 * filename: structPtrTest.c
 * purpose: demonstrate accessing struct using pointer
 * author: Dr. Johnson
 * date: 2022-03-05
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define FRAME_ARRAY_SIZE         9
#define NUMBER_OF_PHYSICAL_PAGES 4
#define NUMBER_OF_VIRTUAL_PAGES  6

DWORD WINAPI myThread( LPVOID );

typedef struct ThreadData_t {
   int threadID;
   int runTime;
   int *startAddress;
} ThreadData_t;

DWORD WINAPI myThread( LPVOID argStruct ) {
   ThreadData_t *myData = (ThreadData_t*)argStruct;
   int localThreadID = myData->threadID;
   int myRunTime = myData->runTime;
   int * pageFrameAddress = myData->startAddress;
   printf( "      in myThread, thread number: %d, time: %d, address: %u, value there: %u...\n", \
               myData->threadID, myData->runTime, myData->startAddress, *myData->startAddress );
   printf( "      in myThread, thread number: %d, time: %d, address: %u, instruction: %u...\n", \
               localThreadID, myRunTime, pageFrameAddress, *pageFrameAddress );
   int instruction = 0;
   for( int i = 0; i < FRAME_ARRAY_SIZE; i++ ) {
      instruction = *pageFrameAddress;
      printf( "         Thread number %d, executing VM instruction: %ld\n", myData->threadID, instruction );
      pageFrameAddress++;
   }
   Sleep( myData->runTime );
   return 0;
}

int main( int argc, char * argv[] ) {

   struct ThreadData_t tData;;

   int index[9] = {111, 222, 333, 444, 555, 666, 777, 888, 999};
   int * pIndex = index;
   tData.threadID = 77;
   tData.startAddress = index;
   tData.runTime = 123 * ((rand() % NUMBER_OF_PHYSICAL_PAGES) + 1);

   printf( "\n      tData slot %d start address : %u\n", tData.threadID, tData.startAddress );
   printf( "      tData runtime contains value: %u\n", tData.runTime);
   printf( "      calling 'myThread()'...\n\n" );

   LPVOID argLocalStruct = (LPVOID)&tData;
   myThread( argLocalStruct );

   return( 0 );
}
