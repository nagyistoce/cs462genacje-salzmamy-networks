/* 
 * File:   Node_Initiator.cpp
 * Author: genacje
 * 
 * Created on March 8, 2011, 5:04 PM
 */

#include "Node_Initiator.h"

Node_Initiator::Node_Initiator(Connector* c) : Node(c) {
    cout << "Node_Initiator (child) constructor." << endl;

    cout << "Enter the url of the KDC: " << endl;

    

}


Node_Initiator::~Node_Initiator() {
}

void Node_Initiator::sendRequest() {
    nonce = 0;
    getNonce(&nonce);
    char msg[128];

    

    return;
}

void Node_Initiator::getKDCResponse() {

    // KDC response will be in the format:
    // bytes 0-3 = nonce (4 bytes)
    // bytes 4-59 = keyS (56 bytes)
    // bytes 60-123 = Ekb(keyS) (64 bytes)
    // = 124 bytes total

    c->listen();

    char* msg = c->get_msg();

    

}



