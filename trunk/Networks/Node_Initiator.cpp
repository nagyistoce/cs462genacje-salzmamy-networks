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
    // bytes 60-123 = EKb(Ks) (64 bytes)
    // = 124 bytes total

    c->listen();

    
    char* msg = c->get_msg();


    // copy the nonce and validate it
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
    

    // copy 56 bytes starting at index 4
    memset(keyS, '\0', KEYSIZE);
    memcpy(keyS, &msg[4], KEYSIZE);

    cout << "Ks received: " << keyS << endl;


    // copy 64 bytes from index 60 EKb(Ks)   
    memset(EKb_Ks, '\0', 64);
    memcpy(EKb_Ks, &msg[60], 64);

    cout << "EKb(Ks) received: " << EKb_Ks << endl;


    
    return;
}

void Node_Initiator::sendSessionKey() {
    cout << "Sending EKb(Ks) to the receiver..." << endl;

    // set session key so that we can decrypt messages adequately
    c->set_key(keyS);

    // but this message is already encrypted with Kb
    c->send_unencrypted(EKb_Ks);


    // listen for nonce
    c->listen();

    long n = 0;


    memcpy((void*)&n, c->get_msg(), 4);

    cout << "Received nonce: " << n << endl;

    long n2 = f(n);

    char n2c[4];
    memset(n2c, '\0', 4);

    cout << "Sending f(nonce): " << n2 << endl;

    c->send(n2c);

    return;
}

