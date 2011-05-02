#include "connector.h"

Connector :: Connector () {
    cout << "default constructor called\n";
}

Connector :: Connector (int port_num) {
    crc = new CCRC32();
    crc->Initialize();
    print_encrypted = false;
    addr_len = sizeof (struct sockaddr);
    numbytes = 0;
    port = port_num;
    he = NULL;
    key = new Blowfish ();
    msg_size = DEFAULTPKTSIZE +TAILSIZE; // default size for establishing connection
    memset(buf, '\0', MAXPKTSIZE); // edited

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
    crc->Initialize();
    print_encrypted = false;
    numbytes = 0;
    port = port_num;
    addr_len = sizeof (struct sockaddr);
    key = new Blowfish ();
    msg_size = DEFAULTPKTSIZE+TAILSIZE; // default size for establishing connection
    memset(buf, '\0', MAXPKTSIZE); // edited

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
    // delete [] buf; // buf is not newed anymore
}

bool Connector :: listen () {
    memset(buf, '\0', msg_size);
  
    if ((numbytes = recvfrom (sockfd, buf, msg_size, 0, (struct sockaddr *) & their_addr, (socklen_t *) & addr_len)) == -1) {
        cout << "Error in listen(): Failed to receive. Terminating...\n";
        exit (1);
    }

    /*
    if (print_encrypted) {
        cout << "Encrypted message received: " << buf << endl;
    }
     */

    key -> Decrypt((void *) buf, msg_size);
    buf [numbytes] = '\0';

    cout << "Decrypted message received: " << buf << endl;
    //printf ("%d bytes received\n", numbytes);


    // CRC
    unsigned long received_crc = 0;
    memcpy(&received_crc, &buf[msg_size-TAILSIZE], sizeof(unsigned long));
    unsigned long expected_crc = crc->FullCRC((const unsigned char*)buf, (unsigned long) msg_size-TAILSIZE);

    
    //cout << "CRC received: " << received_crc << endl;
    //cout << "CRC expected: " << expected_crc << endl;


    if (received_crc == expected_crc) {
        cout << "CRC: Valid packet!" << endl;
        return true;
    } else {
        cout << "Invalid packet... may be valid if cross architecture." << endl;
        return false;
    }
    
    
}

void Connector :: send (char * msg) {
    char msg_copy [msg_size];
    memset(msg_copy, '\0', msg_size); // clear it out.
    memcpy (msg_copy, msg, msg_size-TAILSIZE);

    // CRC before we encrypt and send...
    unsigned long c = crc->FullCRC((const unsigned char*)msg_copy, (unsigned long) msg_size-TAILSIZE);
    
    memcpy(&msg_copy[msg_size-TAILSIZE], &c, sizeof(long)); // fill in the crc slot

    cout << "Unencrypted message to send: " << msg_copy << endl;

    //cout << "CRC value: " << (unsigned long)c << endl;
        
    key -> Encrypt((void *) msg_copy, msg_size);

    /*
    if (print_encrypted) {
       cout << "Encrypted message to send: " << msg_copy << endl;
    }*/

    if ((numbytes = sendto(sockfd, msg_copy, msg_size, 0, (struct sockaddr *)
            & their_addr, sizeof (struct sockaddr))) == -1) {
        cout << "Error in send(): Failed to send. Terminating...\n";
        exit(1);
    }
    //cout << numbytes << " bytes sent." << endl;
}

void Connector :: send_unencrypted (char * msg) {
    
    char msg_copy [msg_size];
    memset(msg_copy, '\0', msg_size); // clear it out.
    memcpy (msg_copy, msg, msg_size-TAILSIZE); // copy user's msg

    cout << "Unencrypted message to send: " << msg_copy << endl;

    // CRC before we send...
    unsigned long c = crc->FullCRC((const unsigned char*)msg_copy, (unsigned long) msg_size-TAILSIZE);

    memcpy(&msg_copy[msg_size-TAILSIZE], &c, sizeof(long)); // fill in the crc slot

    
    //cout << "CRC value: " << c << endl;

    if ((numbytes = sendto(sockfd, msg_copy, msg_size, 0, (struct sockaddr *) & their_addr, sizeof (struct sockaddr))) == -1) {
        cout << "Error in send_unencrypted(): Failed to send. Terminating...\n";
        exit(1);
    }
}

char * Connector :: get_msg () {
    return buf;
}

void Connector::set_print_encrypted(bool print) {
    print_encrypted = print;
    if (print) {
        cout << "Connector: Encrypted sends and receives will be displayed.\n";
    } else {
        cout << "Connector: Encrypted data will not be displayed.\n";
    }
}

void Connector :: set_key (char * passwd) {
    key -> Set_Passwd(passwd);
    cout << "Encryption password set to: " << passwd << endl;
}

void Connector :: set_msg_size (int size) {

    if (size+TAILSIZE > MAXPKTSIZE) {
        cout << "Error! Packet size too high... aborting..." << endl;
        exit(1);
    }

    // the user will only be able to use [size] bytes of the send/rcv buffer
    msg_size = (size+ TAILSIZE); // compensates for the CRC and end of string char;
    

}

int Connector :: get_msg_size () {
    return msg_size-TAILSIZE; // return how many bytes the user may send as data
}
