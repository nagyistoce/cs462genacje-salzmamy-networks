#include "connector.h"

Connector :: Connector () {
	cout << "default constructor called\n";
}

Connector :: Connector (int port_num) {
	addr_len = sizeof (struct sockaddr);
	numbytes = 0;
	port = port_num;
	he = NULL;
	key = new Blowfish ();
	msg_size = 1024;
        buf = new char[msg_size];

	my_addr.sin_family = AF_INET; // host byte order
	my_addr.sin_port = htons (port); // short, network byte order
	my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
	memset (& (my_addr.sin_zero), '\0', 8); // zero the rest of the struct

	if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror ("socket");
		exit (1);
	}

	if (bind (sockfd, (struct sockaddr *) & my_addr, sizeof (struct sockaddr)) == -1) {
		perror ("bind");
		exit (1);
	}

}



Connector :: Connector (char * receiver, int port_num) {
	numbytes = 0;
	port = port_num;
	addr_len = sizeof (struct sockaddr);
	key = new Blowfish ();
	msg_size = 1024;
        buf = new char[msg_size];
        
	my_addr.sin_family = AF_INET; // host byte order
	my_addr.sin_port = htons(port); // short, network byte order
	my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
	memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct

	if ((he = gethostbyname (receiver)) == NULL) { // get the host info
			perror ("gethostbyname");
			exit(1);
		}

	their_addr.sin_family = AF_INET; // host byte order
	their_addr.sin_port = htons (port); // short, network byte order
	their_addr.sin_addr = *((struct in_addr *) he -> h_addr);
	memset (& (their_addr.sin_zero), '\0',  8); // zero the rest of the struct

	if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror ("socket");
		exit (1);
	}
}

Connector :: ~Connector () {
	close (sockfd);
	delete (key);
        delete [] buf;
}

void Connector :: listen () {

	if ((numbytes = recvfrom (sockfd, buf, msg_size, 0, (struct sockaddr *) & their_addr, (socklen_t *) & addr_len)) == -1) {
		perror ("recvfrom");
		exit (1);
	}

	cout << "Before decrypting: " << buf << endl;
	key -> Decrypt((void *) buf, msg_size);
	cout << "After decrypting: " << buf << endl;
	buf [numbytes] = '\0';

	printf ("got packet from %s\n", inet_ntoa (their_addr.sin_addr));
	printf ("packet is %d bytes long\n", numbytes);
//	printf ("packet contains \"%s\"\n", buf);
}

void Connector :: send (char * msg) {
	char msg_copy [msg_size];
	memcpy (msg_copy, msg, msg_size);

	cout << "Unencrypted message to send: " << msg_copy << endl;
	key -> Encrypt((void *) msg_copy, msg_size);
	cout << "Encrypted message to send: " << msg_copy << endl;

	if ((numbytes = sendto(sockfd, msg_copy, strlen(msg_copy), 0, (struct sockaddr *) & their_addr, sizeof (struct sockaddr))) == -1) {
		perror("sendto");
		exit(1);
	}
}

char * Connector :: get_msg () {
		return buf;
}

void Connector :: set_key (char * passwd) {
	key -> Set_Passwd(passwd);
}

void Connector :: set_msg_size (int size) {
    char buf_tmp[msg_size];
    memcpy(buf_tmp, buf, msg_size);
    msg_size = size;
    delete [] buf;
    buf = new char[msg_size];
    memcpy(buf, buf_tmp, msg_size);
}

int Connector :: get_msg_size () {
	return msg_size;
}
