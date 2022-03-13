/**
 * filename: VMSimulator3.c
 * purpose: simulate virtual memory page loading
 * author: Dr. Johnson
 * date: 2019-03-15
 * updated: 2022-02-27
 * NOTE: built on VMSimulatorPC2.c
 *
 * NOTES:  This is a simulation to show the mapping of virtual pages into
 *    physical memory.  Remember that 'pages' means the virtual pages and
 *    'page frames' means the physical pages in memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define FRAME_ARRAY_SIZE         4096
#define NUMBER_OF_PHYSICAL_PAGES 4
#define NUMBER_OF_VIRTUAL_PAGES  6

int *pageFrames;        // used for an array of physical pages of FRAME_ARRAY_SIZE size each
int *pageFramesStart;   // used to keep a permanent reference to the start of 'pageFrames'
int *pageTable;         // used for page REFERENCES to the mapping of virtual into physical
int *tableStart;        // used to keep a permanent referrece to the start of pageTable
int *vPages;            // used for an array of virtual pages of FRAME_ARRAY_SIZE size each
int *vPagesStart;       // used to keep a permanent reference to the start of 'pages'

// declare the child thread function
DWORD WINAPI myThread( LPVOID );

// declare the thread data structure that will be passed into each thread at startup
typedef struct ThreadData_t {
   int threadID;        // the thread ID for each thread
   int runTime;         // the random run time for each thread
   int * startAddress;  // pointer to starting address for 'instructions' for each thread
} ThreadData_t;

// this is the main program [as if you couldn't tell....]
int main( int argc, char * argv[] ) {

   HANDLE hThreads[NUMBER_OF_VIRTUAL_PAGES];
   DWORD  threadIDs[NUMBER_OF_VIRTUAL_PAGES];
   struct ThreadData_t tData[NUMBER_OF_VIRTUAL_PAGES];

   printf( "\n\n   Welcome to the Virtual Memory Base Table Simulator......\n" );

  // allocate space for the physical pages; to help with understanding the code
  //  we'll call them 'pageFrames' which is like 'page frames' in the book
   pageFrames = (int *)malloc( (sizeof(int) * FRAME_ARRAY_SIZE) * NUMBER_OF_PHYSICAL_PAGES );
   if( NULL == pageFrames ) {
      printf( "\n    Could not allocate array of %d size.\n\n",
                  (sizeof(int) * FRAME_ARRAY_SIZE) * NUMBER_OF_PHYSICAL_PAGES );
      exit( -1 );
   }
   printf( "\n   Array of size %d allocated for physical pages...\n\n", \
                 (sizeof(int) * FRAME_ARRAY_SIZE) * NUMBER_OF_PHYSICAL_PAGES );
   pageFramesStart = pageFrames;

  // allocate space for the virtual pages; to help with understanding the code
  //  we'll call them 'vPages' which is like 'pages' in the book
   vPages = (int *)malloc( (sizeof(int) * FRAME_ARRAY_SIZE) * NUMBER_OF_VIRTUAL_PAGES );
   if( NULL == vPages ) {
      printf( "\n    Could not allocate array of %d size.\n\n",
                  (sizeof(int) * FRAME_ARRAY_SIZE) * NUMBER_OF_VIRTUAL_PAGES );
      exit( -1 );
   }
   printf( "\n   Array of size %d allocated for physical pages...\n\n", \
                 (sizeof(int) * FRAME_ARRAY_SIZE) * NUMBER_OF_VIRTUAL_PAGES );
   vPagesStart = vPages;

  // Fill up the virtual pages with random numbers to simulate program code in each page
   printf( "\n   Filling virtual pages with random values to simulate instructions...\n\n" );
   srand( time( NULL ) );     // Feed me, Seymore!!
   int j = 0;
   for( int i = 0; i < FRAME_ARRAY_SIZE * NUMBER_OF_VIRTUAL_PAGES; i++ ) {
      *vPages = (rand() % (RAND_MAX * RAND_MAX) );
      vPages++;
      if( 0 == (i % 4096) ) {
         printf( "            vPages %d starting address: %lu\n", j++, vPages );
      }
   }
   vPages = vPagesStart;
   printf( "         Reset vPages to start, vPages location 0 contains %lu\n", *vPages );
   vPages++;
   for( int i = 1; i < 10; i++ ) {
      printf( "                                vPages location %d contains %lu\n", i, *vPages );
      vPages++;
   }
   vPages = vPagesStart;

  // copy the first four virtual pages into the four physical pages
   for( int i = 0; i < NUMBER_OF_PHYSICAL_PAGES; i++ ) {
      *pageFrames = *vPages;
      pageFrames++;
      vPages++;
   }
   pageFrames  = pageFramesStart;
   vPagesStart = vPages;

  // NOW the fun begins
  // We need to create four threads, each one will read from the array at a different page
  //  the page table slot will be determined by the thread's initialization
  //  the page frame starting location will be determined by the VALUE in the page table slot
  //  the thread will read and display a certain number of "pseudo-instructions" for each time
  //    it is accessed
   for( int i = 0; i < NUMBER_OF_PHYSICAL_PAGES; i++ ) {
      tData[i].threadID = i;
      tData[i].runTime = 123 * ((rand() % NUMBER_OF_PHYSICAL_PAGES) + 1);
      tData[i].startAddress = pageFrames;
      printf( "      tData slot %d start address is    : %lu\n", i, tData[i].startAddress );

      hThreads[i] = CreateThread( NULL, 0, myThread, (LPVOID)(&tData[i]), 0, &threadIDs[i] );
      if( hThreads[i] ) {
         printf( "      child myThread %d created successfully and launched...\n", i );
         Sleep( 1000 );
      } else {
         fprintf( stderr, "CreateThread failed on myThread %d with code %d\n", hThreads[i] );
      }
      pageFrames += FRAME_ARRAY_SIZE;
   }
   Sleep( 5000 );

   printf( "\n\n   Done.  Thanks for playing!\n\n" );

  // free up the memory we've used
   free( pageFrames );
   free( vPages );
   free( pageTable );
   return( 0 );
}

// This is the child thread code.  The child thread will print the current value
//    of what its instruction pointer is pointing to.  It is loaded from the
//    'pages' array when it is started, then iterates through its 'instructions'
//    printing them out.  When it gets to the end of its block of FRAME_ARRAY_SIZE
//    elements, it is done.
DWORD WINAPI myThread( LPVOID argStruct ) {
   ThreadData_t *myData = (ThreadData_t*)argStruct;
   int localThreadID = myData->threadID;
   int myRunTime = myData->runTime;
   int * pageFrameAddress = myData->startAddress;
   printf( "      in myThread, thread number: %d, time: %d, address: %lu, value there: %lu...\n", \
               myData->threadID, myData->runTime, myData->startAddress, *myData->startAddress );
   printf( "      in myThread, thread number: %d, time: %d, address: %lu, instruction: %lu...\n", \
               localThreadID, myRunTime, pageFrameAddress, *pageFrameAddress );
   Sleep( 250 );
   if( 0 == myData->runTime ) {
      myData->runTime = 17;
   }
   int instruction = 0;
   for( int i = 0; i < FRAME_ARRAY_SIZE; i++ ) {
      instruction = *pageFrameAddress;
      printf( "         Thread number %d, executing VM instruction: %lu, at address %lu\n",
            myData->threadID, instruction, pageFrameAddress );
      Sleep( 100 );
      pageFrameAddress++;
      if( myRunTime == myData->runTime ) {
         Sleep( myData->runTime );
         myRunTime = 0;
      }
   }
   Sleep( myData->runTime );
   return 0;
}

