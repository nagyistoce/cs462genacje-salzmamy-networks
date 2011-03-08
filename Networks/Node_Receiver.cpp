/* 
 * File:   Node_Receiver.cpp
 * Author: genacje
 * 
 * Created on March 3, 2011, 4:01 PM
 */

#include "Node_Receiver.h"

Node_Receiver::Node_Receiver(Connector* c) : Node(c){
    cout << "Node_Receiver (child class) constructor called." << endl;
    getKey();
}

Node_Receiver::~Node_Receiver() {
}

void Node_Receiver::listen() {


    //while(1) {

    //c->listen(); // listen for dgrams

        //if legitimate request received, send Eks(n2)
    //strcpy(keyS, ????);
    c->setKey(keyS);
    getNonce();
    char nonce[4];
    memcpy(nonce, &nonce2, 4);
    c->send(nonce);

    //c->listen(); // listen for the response of Eks(f(n2))
    //long receivedNonce2 = ????;
    //validate(&nonce2, &receivedNonce2);

    // ready to receive the file now :)

    //}
}

void Node_Receiver::getKey() {
    getStr(keyB, "Enter K(b):");
}

void Node_Receiver::getNonce() {

    cout << "Please enter a nonce." << endl;
    cin.ignore(2048, '\n');
    cin >>nonce2;

}



