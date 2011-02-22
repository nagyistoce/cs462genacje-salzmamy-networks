/*
 * connector.cc
 *
 *  Created on: Feb 15, 2011
 *      Author: salzmamy
 */

#include "connector.h"
#include "blowfish.h"

/* Used to be able to listen to a port */
Connector :: Connector (int port) {
    key = Blowfish();
    msgSize = 512;
    addr_len = 0;
    numbytes = 0;
    buf [MAXBUFLEN];

    my_addr.sin_family = AF_INET; // host byte order
    my_addr.sin_port = htons(port); // short, network byte order
    my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
    memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct

    if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) == -1) {
            perror("socket");
            exit(1);
    }

    if (bind (sockfd, (struct sockaddr *) & my_addr, sizeof (struct sockaddr)) == -1) {
            perror("bind");
            exit(1);
    }
}

/* Used to be able to send a message to addr on port */
Connector :: Connector (string addr, int port) {
    key = Blowfish();
    msgSize = 512;
    int addr_len = 0;
    int numbytes = 0;
    buf[MAXBUFLEN];

    if ((he = gethostbyname (addr.c_str())) == NULL) { // get the host info
                    perror ("gethostbyname");
                    exit (1);
    }

    their_addr.sin_family = AF_INET; // host byte order
    their_addr.sin_port = htons (port); // short, network byte order
    their_addr.sin_addr = * ((struct in_addr *) he -> h_addr);
    memset (& (their_addr.sin_zero), '\0',  8); // zero the rest of the struct

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
            perror ("socket");
            exit (1);
    }
}

Connector :: ~Connector () {
	close (sockfd);
}

/* Sends msg to specified addr on port */
void Connector :: send (char* msg) {
    cout << "Original message: " << msg << endl;
    //key.Encrypt((void*)msg, msgSize);
    if ((numbytes = sendto (sockfd, (void *) msg, strlen(msg), 0, (struct sockaddr *) & their_addr, sizeof (struct sockaddr))) == -1) {
            perror("send failed:");
            exit(1);
    }
    cout << "Encrypted message sent: " << msg << endl;
}

/* Listens to port for incoming messages - blocks */
void Connector :: listen () {

    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, (struct sockaddr *) & their_addr, (socklen_t *) & addr_len)) == -1) {
            perror("recieve failed:");
            exit(1);
    }

    cout << "Encrypted mesasge received: " << buf << endl;
    //key.Decrypt((void*)buf, msgSize);
    buf[numbytes] = '\0';

    cout << "Decrypted mesasge: " << buf << endl;
}

char* Connector::getMsg() {
    return (char*) buf;
}


void Connector::setMsgSize(int size) {
    msgSize = size;
}

int Connector::getMsgSize() {
    return msgSize;
}

void Connector::setKey(char* key) {
    this->key.Set_Passwd(key);
    cout << "Encryption key set.\n";
}

