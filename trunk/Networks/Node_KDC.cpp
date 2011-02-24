/* 
 * File:   Node_KDC.cpp
 * Author: GENACJE
 * 
 * Created on February 24, 2011, 4:32 PM
 */

#include "Node_KDC.h"
#include "connector.h"

Node_KDC::Node_KDC(Connector c) : Node(c) {
    
    // calls super class
    cout << "Node_KDC (child) constructor...\n";
}



Node_KDC::~Node_KDC(){
    ~Node();
}


void Node_KDC::listen() {
    cout << "KDC: Listening...\n";

    /*
    while(1) {
    c.listen();

    // if we get a legitimate request,
    getKeys();

    }
    */

}

void Node_KDC::getKeys() {


    char k[KEYSIZE]; // 56 = max password for blowfish

    while (k != "") {
    k = getStr("Enter K(a):\n");
    }
    memcpy(k, keyA, KEYSIZE); // copy the key into this variable
    memset(k, '\0', KEYSIZE); // reset that memory

    cout << "K(a) set to: " << keyA << endl;



    //TODO: get other keys.

}



