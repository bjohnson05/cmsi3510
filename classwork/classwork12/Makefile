mymain   :  file1.o file2.o file3.o
		gcc -o mymain.exe file1.o file2.o file3.o

file1.o	:	file1.c 	head1.h	head2.h
		gcc -c file1.c

file2.o	:	file2.c 	head1.h	head2.h
		gcc -c file2.c

file3.o	:	file3.c 	head1.h	head2.h
		gcc -c file3.c

clean	:
		del *.exe *.o


