
#include "head1.h"
#include "head2.h"

void function1( void );
void function2( void );

int main( int argc, char * argv[] ) {

   printf( "\n\n   In main calling function1.....\n" );
   function1();
   printf( "\n\n   In main calling function2.....\n" );
   function2();
   printf( "\n\n   In main no more calls.....\n\n" );
   return 0;
}
