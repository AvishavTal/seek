seek: seek.o seek_records.o
	gcc -g -Wall -ansi -pedantic seek_records.o seek.o -o seek
seek.o: seek.c
	gcc -g -Wall -ansi -pedantic seek.c -c
seek_records.o: seek_records.c
	gcc -g -Wall -ansi -pedantic seek_records.c -c
clean:
	rm *.o
