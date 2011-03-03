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

void Node::getStr(char* key, char* prompt) {
    cout << prompt << endl;
    
    char input[KEYSIZE];

    cin.ignore(KEYSIZE, '\n');
    // make sure cin gets the whole thing
    cin.get(input, KEYSIZE);

    memcpy((void*)key, (void*)input, KEYSIZE);

}

bool Node::validate(int mine, int theirs) {

    if (mine == theirs) {
        return true;
    } else return false;

}
