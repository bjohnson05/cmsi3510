
#include <stdio.h>
#include <dirent.h>

int main( int argc, char * argv[] ) {
   struct dirent *directoryEntry;  // Pointer for directory entry

  // opendir() returns a pointer of DIR type
  //  we are looking at the current diretory, indicated by "."
   DIR *directory = opendir( "." );

  // opendir returns NULL if couldn't open directory
   if( directory == NULL ) {
      printf("Could not open current directory" );
      return 0;
   }

  // Refer to
  //  http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
  // for readdir() details
   while( (directoryEntry = readdir( directory )) != NULL ) {
      printf("%s\n", directoryEntry->d_name);
   }

   closedir(directory);
   return 0;
}
