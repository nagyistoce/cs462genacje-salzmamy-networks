/* 
 * File:   Node_Receiver.cpp
 * Author: genacje
 * 
 * Created on March 3, 2011, 4:01 PM
 */

#include "Node_Receiver.h"

Node_Receiver::Node_Receiver(Connector* c) : Node(c){
    cout << "Node_Receiver (child class) constructor called." << endl;
    
    getStr(keyB, KEYSIZE, "Enter K(b):");

    c->set_key(keyB);
}

Node_Receiver::~Node_Receiver() {
}

void Node_Receiver::listen() {

    cout << "Receiver: Listening..." << endl;

    c->listen();

    char msg[64];
    memset(msg, '\0', 64);
    memcpy(msg, c->get_msg(), 64);

    strcpy(keyS, msg);

    cout << "Received Ks: " << keyS << endl;

    validateConnection();

}

void Node_Receiver::validateConnection() {
    
    c->set_key(keyS);
    cout << "Session key set! Handshaking..." << endl;
    nonce2 = 0;
    getNonce(&nonce2, "Enter a nonce: ");

    /*TODO: Urgent: adjust all packets to accomodate 8 byte longs*/

    char n[8];
    memset(n, '\0', 8);
    memcpy(n, &nonce2, 8);
    
    c->send(n);

    cout << "Sent nonce: " << nonce2 << endl;

    c->listen();

    long n2f = 0;

    memcpy((void*)&n2f, c->get_msg(), 8);

    if (f(nonce2) != n2f) {
        cout << "Nonce validation failed!" << endl
                << "Expected: " << f(nonce2) << endl
                << "Received: " << n2f << endl;
        exit(1);
    } else {
        cout << "Nonce " << n2f << " successfully validated!" << endl <<
                "Handshaking complete. Listening for protocol data..." << endl;
        c->send("ack"); // ack the handshaking
    }

    /* TODO: Get packet size from initiator
     * Send an ack back.
     * Set the connector's msg size variable to the right length
     * (make sure it can hold a crc too!)
     * TODO: Get transmission method from initiator (s&g / gbn / sr)
     * Send an ack back.
     */

    // packet should have 10 useful bytes:
    // [1 |  4  |  4  ]
    // [protocol |    pkt size     |     window_size]
    char proto = 'x';
    int pkt_size = 0;
    int window_size = 0;

    c->listen();
    memcpy(&proto, c->get_msg(), 1);
    memcpy(&pkt_size, &c->get_msg()[1], sizeof(int));
    memcpy(&window_size, &c->get_msg()[5], sizeof(int));

    cout << "Protocol data received: \n" <<
            "Protocol: " << proto << endl <<
            "Packet size: " << pkt_size << endl <<
            "Window size: " << window_size << endl;

    if (proto = 'w') { // stop and wait
        // create this Transfer Protocol object

        // send validation
        c->send(c->get_msg()); // send the exact same thing back.

        // run the protocol


    } else if (proto = 'g') { // go back n
        // create this Transfer Protocol object

        // send validation
        c->send(c->get_msg()); // send the exact same thing back.

        // run the protocol
    } else if (proto = 's') { // selective repeat
        // create this Transfer Protocol object

        // send validation
        c->send(c->get_msg()); // send the exact same thing back.
        
        // run the protocol
    }
    
    
}






