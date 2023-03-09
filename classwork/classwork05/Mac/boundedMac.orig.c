   #include <stdio.h>
   #include <stdlib.h>
    
   int mutex = 1;
   int full  = 0;
   int empty = 7;          // maximum of seven messages in buffer
   int x     = 0;
    
   int main()
   {
      int n;
      void producer();
      void consumer();
      int wait( int );
      int signal( int );
      while( 1 ) {
         printf( "\n\n   1.Producer\n   2.Consumer\n   3.Exit" );
         printf("\n      Enter your choice: ");
         scanf("%d",&n);
         switch( n ) {
            case 1:  if( (mutex == 1) && (empty != 0) ) {
                        producer();
                     } else {
                        printf( "\nBuffer is full!!" );
                     }
                     break;
            case 2:  if( (mutex == 1) && (full != 0) ) {
                        consumer();
                     } else {
                        printf("\nBuffer is empty!!");
                     }
                     break;
            case 3:
            default: exit( 0 );
                     break;
         }
      }
      return 0;
   }
    
   int wait( int s ) {
      return( --s );
   }
    
   int signal( int s ) {
      return( ++s );
   }
    
   void producer() {
      mutex = wait( mutex );
      full  = signal( full );
      empty = wait( empty );
      x++;
      printf( "\n  Producer produces the item %d", x );
      mutex = signal( mutex );
   }
    
   void consumer()
   {
      mutex = wait( mutex );
      full  = wait( full );
      empty = signal( empty );
      printf( "\n  Consumer consumes item %d", x );
      x--;
      mutex = signal( mutex );
   }
