#include "connector.h"

Connector :: Connector () {
    cout << "default constructor called\n";
}

Connector :: Connector (int port_num) {
    crc = new CCRC32();
    crc.Initialize();
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
        cout << "Failed to create socket. Terminating...\n";
        exit (1);
    }

    if (bind (sockfd, (struct sockaddr *) & my_addr, sizeof (struct sockaddr)) == -1) {
        cout << "Failed to bind socket. Terminating...\n";
        exit (1);
    }

}



Connector :: Connector (char * receiver, int port_num) {
    crc = new CCRC32();
    crc.Initialize();
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
        cout << "Bad host name entered; Terminating..."<<endl;
        exit(1);
    }

    their_addr.sin_family = AF_INET; // host byte order
    their_addr.sin_port = htons (port); // short, network byte order
    their_addr.sin_addr = *((struct in_addr *) he -> h_addr);
    memset (& (their_addr.sin_zero), '\0',  8); // zero the rest of the struct

    if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) == -1) {
        cout << "Socket creation failed; Terminating..." << endl;
        exit (1);
    }
}

Connector :: ~Connector () {
    close (sockfd);
    delete (key);
    delete (crc);
    delete [] buf;
}
/* TODO: FINISH CRC IN LISTEN AND SEND METHODS */
void Connector :: listen () {

    if ((numbytes = recvfrom (sockfd, buf, msg_size, 0, (struct sockaddr *) & their_addr, (socklen_t *) & addr_len)) == -1) {
        cout << "Error in listen(): Failed to receive. Terminating...\n";
        exit (1);
    }

    //cout << "Before decrypting: " << buf << endl;
    key -> Decrypt((void *) buf, msg_size);
    unsigned long cc = 0;
    memcpy(&cc, &buf[msg_size-9], sizeof(long));
    crc.FullCRC()

    cout << "Decrypted message received: " << buf << endl;
    buf [numbytes] = '\0';

    printf ("From %s\n", inet_ntoa (their_addr.sin_addr));
    printf ("%d bytes long\n", numbytes);
}

void Connector :: send (char * msg) {
    char msg_copy [msg_size];
    memset(msg_copy, '\0', msg_size); // clear it out.
    memcpy (msg_copy, msg, msg_size);

    cout << "Unencrypted message to send: " << msg_copy << endl;
    key -> Encrypt((void *) msg_copy, msg_size);
    //cout << "Encrypted message to send: " << msg_copy << endl;

    if ((numbytes = sendto(sockfd, msg_copy, msg_size, 0, (struct sockaddr *) & their_addr, sizeof (struct sockaddr))) == -1) {
        cout << "Error in send(): Failed to send. Terminating...\n";
        exit(1);
    }
}

void Connector :: send_unencrypted (char * msg) {
    unsigned long crc = 0;
    this->crc.FullCRC(msg, &crc);
    char msg_copy [msg_size];
    memset(msg_copy, '\0', msg_size); // clear it out.
    memcpy (msg_copy, msg, msg_size);

    cout << "Unencrypted message to send: " << msg_copy << endl;


    if ((numbytes = sendto(sockfd, msg_copy, msg_size, 0, (struct sockaddr *) & their_addr, sizeof (struct sockaddr))) == -1) {
        cout << "Error in send_unencrypted(): Failed to send. Terminating...\n";
        exit(1);
    }
}

char * Connector :: get_msg () {
    return buf;
}

void Connector :: set_key (char * passwd) {
    key -> Set_Passwd(passwd);
    cout << "Encryption password set to: " << passwd << endl;
}

void Connector :: set_msg_size (int size) {

    size+= 9; // compensates for the CRC and end of string char;
    // the user will only be able to use [size] bytes of the send/rcv buffer

    char buf_tmp[msg_size];
    memcpy(buf_tmp, buf, msg_size);
    msg_size = size;
    delete [] buf;
    buf = new char[msg_size];
    memcpy(buf, buf_tmp, msg_size);
}

int Connector :: get_msg_size () {
    return msg_size-9; // return how many bytes the user may send as data
}
