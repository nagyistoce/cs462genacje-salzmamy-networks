/* 
 * File:   Node_Initiator.cpp
 * Author: genacje
 * 
 * Created on March 8, 2011, 5:04 PM
 */

#include "Node_Initiator.h"

Node_Initiator::Node_Initiator(Connector* c) : Node(c) {
    cout << "Node_Initiator (child) constructor." << endl;

    

    //getStr(kdcURL, 128, "Enter the url of the KDC: \n");
    getStr(keyA, KEYSIZE, "Enter Ka:");

    c->set_key(keyA);

}


Node_Initiator::~Node_Initiator() {
}

void Node_Initiator::send_request() {
    nonce = 0;
    getNonce(&nonce, "Enter a nonce: ");
    char msg[1024];
    memset(msg, '\0', 1024);

    // copy the nonce into the request
    memcpy(msg, &nonce, sizeof(long));
    //char* request = "Requesting session key...";
    //memcpy(&msg[8], request, strlen(request));

    // [ nonce |           string              ]

    c->send(msg);

    return;
}

void Node_Initiator::get_kdc_response() {

    // KDC response will be in the format:
    // bytes 0-7 = nonce (8 bytes)
    // bytes 8-63 = keyS (56 bytes)
    // bytes 64-119 = EKb(Ks) (56 bytes)
    // = 120 bytes total

    c->listen();

    
    char* msg = c->get_msg();


    // copy the nonce and validate it
    long checkNonce = 0;
    memcpy(&checkNonce, msg, sizeof(long));

    if (validate(checkNonce, nonce)) {
        cout << "Nonce: " << nonce << " validated!" << endl;
    } else {
        cout << "Nonce validation failed... " << endl
                << "Sent: " << nonce << endl
                << "Received: " << checkNonce << endl;
        exit(1);
    }
    

    // copy 56 bytes starting at index 8
    memset(keyS, '\0', KEYSIZE);
    memcpy(keyS, &msg[8], KEYSIZE);

    cout << "Ks received: " << keyS << endl;


    // copy 56 bytes from index 64 EKb(Ks)
    memset(EKb_Ks, '\0', KEYSIZE);
    memcpy(EKb_Ks, &msg[64], KEYSIZE);

    
    return;
}

void Node_Initiator::send_session_key() {
    cout << "Sending EKb(Ks) to the receiver..." << endl;

    // set session key so that we can decrypt messages adequately
    c->set_key(keyS);

    // but this message is already encrypted with Kb
    c->send_unencrypted(EKb_Ks);

    handshake();
    

    return;
}

void Node_Initiator::handshake() {
    // listen for nonce
    c->listen();

    long n = 0;


    memcpy((void*)&n, c->get_msg(), sizeof(long));

    cout << "Received nonce: " << n << endl;

    long n2 = f(n);

    char n2c[sizeof(long)];
    memset(n2c, '\0', sizeof(long));
    memcpy(n2c, (void*)&n2, sizeof(long));
    cout << "Sending f(nonce): " << n2 << endl;

    c->send(n2c);

    cout << "Listening for ack..." << endl;
    c->listen();

    if (strcmp(c->get_msg(), "ack") == 0) {
        cout << "***Key exchange complete***\n" << endl;
    }

    get_transmission_data();
}


/* Get packet size from user
     * Send the packet size to the receiver and get an ack back.
     * Set the connector's msg size variable to the right length
     * (make sure it can hold a crc too!)
     * Get transmission method from user (s&g / gbn / sr)
     * Receive ack for transmission method
     */

void Node_Initiator::get_transmission_data() {

    cout << "Obtaining transmission data from user...\n" << endl;

    cout << "Enter a protocol: " << endl <<
            "'w' = stop and wait" << endl <<
            "'g' = go back n" << endl <<
            "'s' = selective repeat" << endl;
    char protocol = 'x';
    int packet_size = -1;
    int window_size = -1;

    while (protocol != 'w' && protocol != 'g' && protocol != 's') {
        cin.ignore(1024, '\n');
        cin >> protocol;
    }

    
    while (!( (packet_size > 0) && (packet_size < 64) ) ) {
        getInt(&packet_size,
                "Enter a packet size (in kb) between 1 and 63: ");
    }
    packet_size = packet_size*1024;

    char msg[10];
    memset(msg, '\0', 10);

    // transmission_data_packet will look like:
    // [protocol |  packet_size   |   window_size(if go back n or sel repeat)]
    memcpy(msg, (void*)&protocol, 1); // fill byte 0 with the protocol
    memcpy(&msg[1], (void*)&packet_size, sizeof(int)); // bytes 1-4 = pkt size
    
    if (protocol == 'w') {
        // have all the data we need - let the receiver know of our choices
        c->send(msg);

        // listen for a response with the same content
        c->listen();
        char temp[10];
        memcpy(temp, c->get_msg(), 10);
        // validate

        // make TransferProtocol object, run the protocol

        c->set_msg_size(packet_size);

    } else {
        while (!( (window_size > 0) && (window_size < 51) ) ) {
        getInt(&window_size,
                "Enter a window size between 1 and 50: ");
        memcpy(&msg[5], window_size, sizeof(int)); // fill last slot in packet
        c->send(msg);

        // listen for a response with the same content
        c->listen();
        char temp[10];
        memcpy(temp, c->get_msg(), 10);
        // validate

        if (protocol == 'g') { // go back n

            // make a Transfer Protocol object
            
            // run this protocol

        } else if (protocol = 's') { // selective repeat

            // make a Transfer Protocol object

            // run this protocol


        }
    }
   }


}

