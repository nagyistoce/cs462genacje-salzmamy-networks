/*
 * connector.h
 *
 *  Created on: Mar 10, 2011
 *      Author: salzmamy
 */

#ifndef CONNECTOR_H_
#define CONNECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include "genacje_salzmamy_blowfish.h"
#include "genacje_salzmamy_crc.h"

// 63 kb packet + 8 byte long checksum
// this is the size of the buf array; the packet will be taken from 
// and inserted into this array up to the pkt_size index.
#define TAILSIZE 16
#define MAXPKTSIZE ((63*1024)+TAILSIZE)
#define DEFAULTPKTSIZE 1024

using namespace std;


class Connector {

public:
	Connector ();
	Connector (int);  // constructor that sets up a listening port right away
	Connector (char *, int); // allows sending of messages right away (and listening)
	~Connector ();

	void send (char *);
        void send_unencrypted(char*);

	bool listen (); // returns false if a damaged packet is detected.
	char * get_msg ();
        void set_print_encrypted(bool print); 
	void set_key (char *);
	void set_msg_size (int);
	int get_msg_size ();

private:
	Blowfish * key;
        CCRC32* crc;
	struct sockaddr_in their_addr; // connectors address information
	struct sockaddr_in my_addr; // my address information

        bool print_encrypted;

	int sockfd;
	int numbytes;
	int port;
	int addr_len;
	int msg_size; // Important: this is larger than the user's msg size to
        // fit the CRC at the end!
	struct hostent * he;
	char buf[MAXPKTSIZE];
};

#endif /* CONNECTOR_H_ */
