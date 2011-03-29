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
    getStr(keyA, KEYSIZE, "Enter Ka: \n");

    c->set_key(keyA);

}


Node_Initiator::~Node_Initiator() {
}

void Node_Initiator::sendRequest() {
    nonce = 0;
    getNonce(&nonce);
    char msg[128];

    // copy the nonce into the request
    memcpy(msg,&nonce, 4);
    char* request = "Requesting session key...";
    memcpy(&msg[4], request, strlen(request));

    // [ nonc |           string              ]

    c->send(msg);

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

    long checkNonce = 0;
    memcpy(&checkNonce, msg, 4);

    if (validate(checkNonce, nonce)) {
        cout << "Nonce: " << nonce << " validated!" << endl;
    } else {
        cout << "Nonce validation failed... " << endl
                << "Sent: " << nonce << endl
                << "Received: " << checkNonce << endl;
        exit(1);
    }

    cout << "Now forward EKb(Ks) to Receiver..." << endl;

    
    return;
}



