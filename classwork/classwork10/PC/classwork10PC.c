#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// takes the mode value, converts it to string, parses the
// last 9 characters, and converts the string into the
// characters of "r", "w", and "x", or "-" where appropriate
// result is returned in the passed argument
void makeModeStr( unsigned long status, char * dest ) {

   char buffer[17];
   int index = 7;

   itoa( (int)status, buffer, 2 );
   if( (strlen(buffer) % 2) == 1 ) {
      index--;
   }
   strcpy( dest, &buffer[index] );
   for( int i = 0; i < strlen(dest); i++ ) {
      if( dest[i] == '0' ) {
         dest[i] = '-';
      } else {
         switch( i % 3 ) {
            case 0: dest[i] = 'r'; break;
            case 1: dest[i] = 'w'; break;
            case 2: dest[i] = 'x'; break;
         }
      }
   }
}

// the main
int main( int argc, char * argv[] ) {

   struct stat filestatus;
   char modeString[10];

   if( argc != 2 ) {
      printf( "\n   You must enter a file name for status check.\n\n" );
      return 0;
   }

   if( stat( argv[1], &filestatus ) == -1 ) {
      printf( "\n   can't get file status for %s\n\n", argv[1] );
      return 0;
   }

   printf( "\n\n   Full status for file:   %s\n", argv[1] );
   printf( "   File type:              ");
   switch (filestatus.st_mode & S_IFMT) {
      case S_IFBLK:  printf( "block device\n" );            break;
      case S_IFCHR:  printf( "character device\n" );        break;
      case S_IFDIR:  printf( "directory\n" );               break;
      case S_IFIFO:  printf( "FIFO/pipe\n" );               break;
      case S_IFREG:  printf( "regular file\n" );            break;
 // only available on Mac/Linux
 //      case S_IFLNK:  printf( "symlink\n" );                 break;
 // only available on Mac/Linux
 //      case S_IFSOCK: printf( "socket\n" );                  break;
      default:       printf( "unknown?\n" );                break;
   }

   printf( "   I-node number:          %ld\n", (long) filestatus.st_ino);
   printf( "   Mode:                   %lo (octal)\n", (unsigned long) filestatus.st_mode);
   makeModeStr( (unsigned long) filestatus.st_mode, modeString );
   printf( "   Mode in characters:     %s\n", modeString );
   printf( "   Link count:             %ld\n", (long) filestatus.st_nlink );
   printf( "   Ownership: UID:         %ld\n", (long) filestatus.st_uid );
   printf( "   Ownership: GID:         %ld\n", (long) filestatus.st_gid );
 // only available on Mac/Linux; changed to "st_size" for Windows
 // printf("   Preferred I/O blk size: %ld bytes\n", (long) filestatus.st_blksize );
   printf( "   Preferred I/O blk size: %ld bytes\n", (long) filestatus.st_size );
   printf( "   File size:              %lld bytes\n", (long long) filestatus.st_size );
  // only available on Mac/Linux; changed to "st_nlink" for Windows
  // printf("   Blocks allocated:       %lld\n", (long long) filestatus.st_blocks );
   printf( "   Blocks allocated:       %lld\n", (long long) filestatus.st_nlink );
   printf( "   Last status change:     %s", ctime(&filestatus.st_ctime) );
   printf( "   Last file access:       %s", ctime(&filestatus.st_atime) );
   printf( "   Last file modification: %s\n\n\n", ctime(&filestatus.st_mtime) );

   return 0;
}
