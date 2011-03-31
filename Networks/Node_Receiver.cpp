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
}

Node_Receiver::~Node_Receiver() {
}

void Node_Receiver::listen() {

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

    getNonce(&nonce2);
    
    char n[4];
    memset(n, '\0', 4);
    memcpy(n, &nonce2, 4);
    
    c->send(n);

    cout << "Sent nonce: " << nonce2 << endl;

    c->listen();

    char n2f[4]
    
}






