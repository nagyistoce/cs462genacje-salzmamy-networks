## Makefile for a typical program

CC=g++
##CFLAGS=-g -Wall
LIBSSHIVA= -lpthread -lsocket -lnsl -lrt

HFILES=	connector.h blowfish.h Node.h Node_KDC.h Node_Initiator.h Node_Receiver.h crc.h

CCFILES= $(HFILES:.h=.cpp) main.cpp endian.cpp 

OFILES= $(CCFILES:.cpp=.o)

##rules

all: link

.cpp.o:	$(CCFILES) $(HFILES)
	$(CC) $(CFLAGS) -c $*.cpp

link:	$(OFILES)
	$(CC) $(CFLAGS)  -o rungoonies $(OFILES)

goonies:
	$(CC) $(CFLAGS) $(CCFILES) -o rungoonies

shiva:
	$(CC) $(CFLAGS) $(CCFILES) -o runshiva $(LIBSSHIVA)
	
	
clean:
	rm -f *.o *.*~ rungoonies runshiva
