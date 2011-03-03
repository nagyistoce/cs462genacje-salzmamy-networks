/* 
 * File:   Node_KDC.cpp
 * Author: GENACJE
 * 
 * Created on February 24, 2011, 4:32 PM
 */

#include "Node_KDC.h"
#include "connector.h"

Node_KDC::Node_KDC(Connector *c) : Node(c) {
    
    // calls super class
    cout << "Node_KDC (child) constructor...\n";
}



Node_KDC::~Node_KDC(){
    
}


void Node_KDC::listen() {
    cout << "KDC: Listening...\n";


    // if we get a legitimate request,
    getKeys();
    /*
    while(1) {
    c.listen();

    }
    */

}

void Node_KDC::getKeys() {


    char k[KEYSIZE]; // 56 = max password for blowfish
    memset(k, '\0', KEYSIZE); // reset that memory
    
    while (strcmp(k, "") == 0) {
    Node::getStr(k, "Enter K(a):\n");
    cout << k << " received... " << endl;
    }
    memcpy(keyA, k, KEYSIZE); // copy the key into this variable
    memset(k, '\0', KEYSIZE); // reset that memory

    cout << "K(a) set to: " << keyA << endl;

    
    while (strcmp(k, "") == 0) {
    Node::getStr(k, "Enter K(b):\n");
    }
    memcpy(keyB, k, KEYSIZE); // copy the key into this variable
    memset(k, '\0', KEYSIZE); // reset that memory

    cout << "K(b) set to: " << keyB << endl;

    
    while (strcmp(k, "") == 0) {
    Node::getStr(k, "Enter K(s):\n");
    }
    memcpy(keyS, k, KEYSIZE); // copy the key into this variable
    memset(k, '\0', KEYSIZE); // reset that memory

    cout << "K(s) set to: " << keyS << endl;
    

}



