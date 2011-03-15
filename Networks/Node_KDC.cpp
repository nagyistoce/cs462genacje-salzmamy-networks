/* 
 * File:   Node_KDC.cpp
 * Author: GENACJE
 * 
 * Created on February 24, 2011, 4:32 PM
 */

#include "Node_KDC.h"



Node_KDC::Node_KDC(Connector *c) : Node(c) {
    
    // calls super class
    cout << "Node_KDC (child) constructor...\n";
    getKeys();
    c->set_key(keyA); // prepare to talk to the receiver.
}



Node_KDC::~Node_KDC(){
    
}


void Node_KDC::listen() {
    cout << "KDC: Listening...\n";

    /*TODO: finish this method*/
    
    
    while(1) {
        c->listen();
        cout << "Received: " << c->get_msg() << endl;
        // if we get a legitimate request, get the keys from user input
        char k[KEYSIZE];
        memset(k, '\0', KEYSIZE); // reset that memory
        while (strcmp(k, "") == 0) {
            Node::getStr(k, KEYSIZE, "Enter K(s):");
        }
        memcpy(keyS, k, KEYSIZE); // copy the key into this variable
        

        cout << "K(s) set to: " << keyS << endl;
        // fill nonce variable
        memcpy(&nonce, c->get_msg(), 4); // nonce will be the first 4 bytes (long *)
        
        sendKDCResponse();

    }
    

}

void Node_KDC::getKeys() {


    char k[KEYSIZE]; // 56 = max password for blowfish
    memset(k, '\0', KEYSIZE); // reset that memory
    
    while (strcmp(k, "") == 0) {
        Node::getStr(k, KEYSIZE, "Enter K(a):");
    }
    memcpy(keyA, k, KEYSIZE); // copy the key into this variable
    memset(k, '\0', KEYSIZE); // reset that memory

    cout << "K(a) set to: " << keyA << endl;

    
    while (strcmp(k, "") == 0) {
        Node::getStr(k, KEYSIZE, "Enter K(b):");
    }
    memcpy(keyB, k, KEYSIZE); // copy the key into this variable
    memset(k, '\0', KEYSIZE); // reset that memory

    cout << "K(b) set to: " << keyB << endl;

    
    
    

}

void Node_KDC::sendKDCResponse() {

    // make packet with the items needed
    // Eka(nonce|ks|Ekb(ks))

    // create last part of msg
    Blowfish b = Blowfish();

    b.Set_Passwd(keyB);
    char tempS[64];// must be a multiple of 8 bytes
    strcpy(tempS, keyS); // copy the contents of keyS into tempS
    b.Encrypt((void*)tempS, 64); // tempS is now ready to be added to the response
    

    // set the connector's encryption key to keyA if not done so already
    c->set_key(keyA);

    char msg[sizeof(long)+2*KEYSIZE]; // size of the three elements within it
    memcpy(msg, &nonce, sizeof(long)); //nonce
    strcat(msg, keyS);  //|ks
    strcat(msg, tempS); //|Ekb(ks)

    c->send(msg); // send Eka(nonce|ks|Ekb(ks))
    return;
}



