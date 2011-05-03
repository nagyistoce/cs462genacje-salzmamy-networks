/* 
 * File:   Node_Receiver.cpp
 * Author: genacje
 * 
 * Created on March 3, 2011, 4:01 PM
 */

#include "genacje_salzmamy_Node_Receiver.h"


Node_Receiver::Node_Receiver(Connector* c) : Node(c){
    cout << "\n\n~~Receiver~~\n\n";
    
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

    memset(keyS, '\0', KEYSIZE);
    strcpy(keyS, msg);

    cout << "Received Ks: " << keyS << endl;
    c->set_key(keyS);
    cout << "\nHandshaking..." << endl << endl;


    validate_connection();

}

void Node_Receiver::validate_connection() {

    

    nonce2 = 0;
    getNonce(&nonce2, "Enter a nonce: ");


    char msg[DEFAULTPKTSIZE];
    memset(msg, '\0', 8);
    memcpy(msg, &nonce2, 8);
    
    c->send(msg);

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
                "Handshaking complete. Listening for protocol data...\n" << endl;
        memset(msg, '\0', 4);
        memcpy(msg, "ack", 3);
        c->send(msg); // ack the handshaking

        start_protocol();
    }

    
}


/*  Get    transmission protocol
     *     packet size
     *     window size
     *     file name
     *
     * -Send an validation back.
     * -Download the file.
*/
void Node_Receiver::start_protocol() {

    // packet should have 141 useful bytes:
    // [    1    |      4      |       8       |      128        ]
    // [protocol |  pkt size   |  window_size  |      fname      ]
    char proto = 'x';
    int pkt_size = 0;
    long window_size = 0;
    char fname[138];
    memset(fname, '\0', 138);
    memcpy(fname, "Downloads/", 10);

    c->listen();
    memcpy(&proto, c->get_msg(), 1);
    memcpy(&pkt_size, &c->get_msg()[1], sizeof(int));
    memcpy(&window_size, &c->get_msg()[5], sizeof(long));
    memcpy(&fname[10], &c->get_msg()[13], 128);

    cout << "Protocol data received: \n" <<
            "Protocol: " << proto << endl <<
            "Packet size: " << pkt_size << endl <<
            "Window size: " << window_size << endl <<
            "Filename: " << &fname[10] << endl << endl;


    // VALIDATE //
    c->send(c->get_msg()); // send the exact same thing back.


    // adjust packet size for transmission
    c->set_msg_size(pkt_size);
    if (proto = 'w') { // stop and wait

        // create this Transfer Protocol object
        StopAndWait sw = StopAndWait(c, pkt_size, fname);
        // run the protocol
        sw.run_receiver();

    } else if (proto = 'g') { // go back n

        // create this Transfer Protocol object
        GoBackN gbn = GoBackN(c, pkt_size, fname, window_size);
        // run the protocol
        gbn.run_receiver();

    } else if (proto = 's') { // selective repeat

        // create this Transfer Protocol object
        cout << "Selective repeat: todo..." << endl;
        // run the protocol
        

    }

}




