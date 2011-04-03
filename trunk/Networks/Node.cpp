/* 
 * File:   Node.cpp
 * Author: GENACJE
 * 
 * Created on February 24, 2011, 4:25 PM
 */

#include "Node.h"

Node::Node(Connector* c) {
    
    this->c = c;
    cout << "Node (parent) constructor called.\n";
    
}



Node::~Node() {
}

void Node::getStr(char* strToGet, int size, char* prompt) {

    cout << prompt << endl;
    
    char input[size];

    cin.ignore(1024, '\n');
    // make sure cin gets the whole thing
    cin.get(input, size);

    memcpy((void*)strToGet, (void*)input, size);

}

void Node::getNonce(long* nonce) {


    cout << "Please enter a nonce." << endl;
    cin.ignore(2048, '\n');
    cin >>*nonce;


}

bool Node::validate(long& mine, long& theirs) {

    if (mine == theirs) {
        return true;
    } else return false;

}

void Node::newConnector(Connector* newC) {
    // delete the old connector, set c to the newC
    delete c;
    c = newC;
}
