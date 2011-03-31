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
#include "blowfish.h"

using namespace std;

//#define MAXBUFLEN (1024*1024)

class Connector {

public:
	Connector ();
	Connector (int);  // constructor that sets up a listening port right away
	Connector (char *, int); // allows sending of messages right away (and listening)
	~Connector ();

	void send (char *);
        void send_unencrypted(char*);

	void listen ();
	char * get_msg ();
	void set_key (char *);
	void set_msg_size (int);
	int get_msg_size ();

private:
	Blowfish * key;
	struct sockaddr_in their_addr; // connector�s address information
	struct sockaddr_in my_addr; // my address information
	int sockfd;
	int numbytes;
	int port;
	int addr_len;
	int msg_size;
	struct hostent * he;
	char *buf;
};

#endif /* CONNECTOR_H_ */
