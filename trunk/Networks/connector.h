/*
 * connector.h
 *
 *  Created on: Feb 15, 2011
 *      Author: salzmamy
 */

#include <iostream>
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

#define MAXBUFLEN 100

using namespace std;

#ifndef CONNECTOR_H_
#define CONNECTOR_H_

class Connector {

public:
	Connector ();
	Connector (int);
	Connector (string, int);
	~Connector ();

	void send (string);
	void listen();

private:
	int sockfd;
	struct sockaddr_in my_addr; // my address information
	struct sockaddr_in their_addr; // connector’s address information
	int addr_len, numbytes;
	char buf[MAXBUFLEN];
	struct hostent * he;
};
#endif /* CONNECTOR_H_ */
