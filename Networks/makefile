## Makefile for a typical program

CC=g++
##CFLAGS=-g -Wall
LIBSSHIVA= -lpthread -lsocket -lnsl -lrt

HFILES=	genacje_salzmamy_connector.h genacje_salzmamy_blowfish.h genacje_salzmamy_Node.h \
	genacje_salzmamy_Node_KDC.h genacje_salzmamy_Node_Initiator.h \
        genacje_salzmamy_Node_Receiver.h genacje_salzmamy_crc.h  \
	genacje_salzmamy_TransferProtocol.h genacje_salzmamy_StopAndWait.h \
	genacje_salzmamy_GoBackN.h genacje_salzmamy_TransferMetrics.h \
	genacje_salzmamy_PacketDropper.h 


CCFILES= $(HFILES:.h=.cpp) genacje_salzmamy_main.cpp genacje_salzmamy_endian.cpp

OFILES= $(CCFILES:.cpp=.o)

##rules

all: link

.cpp.o:	$(CCFILES) $(HFILES)
	$(CC) $(CFLAGS) -c $*.cpp

link:	$(OFILES)
	$(CC) $(CFLAGS)  -o rungoonies $(OFILES)

goonies:
	$(CC) $(CFLAGS) $(CCFILES) -o rungoonies -lpthread

shiva:
	$(CC) $(CFLAGS) $(CCFILES) -o runshiva $(LIBSSHIVA)
	
	
clean:
	rm -f *.o *.*~ rungoonies runshiva
