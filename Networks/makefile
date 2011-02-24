## Makefile for a typical program

CC=g++
CFLAGS=-g -Wall
LIBSSHIVA= -lpthread -lsocket -lnsl -lrt

CCFILES= $(HFILES:.h=.cpp) main_mark.cpp endian.cpp f.cpp



goonies:
	$(CC) $(CFLAGS) $(CCFILES) -o rungoonies

shiva:
	$(CC) $(CFLAGS) $(CCFILES) -o runshiva $(LIBSSHIVA)
	
	
clean:
	rm -f *.o *.*~ rungoonies runshiva
