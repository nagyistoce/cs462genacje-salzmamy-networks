/* 
 * File:   Node.cpp
 * Author: GENACJE
 * 
 * Created on February 24, 2011, 4:25 PM
 */

#include "genacje_salzmamy_Node.h"

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

void Node::getInt(int* intToGet, char* prompt) {
    cout << prompt << endl;
    cin.ignore(1024, '\n');
    cin >>*intToGet;
}

void Node::getLong(long* longToGet, char* prompt) {
    cout << prompt << endl;
    cin.ignore(1024, '\n');
    cin >>*longToGet;
}

void Node::getNonce(long* nonce, char* msg) {


    cout << msg << endl;
    cin.ignore(1024, '\n');
    cin >>*nonce;


}

bool Node::validate(long& mine, long& theirs) {

    if (mine == theirs) {
        return true;
    } else return false;

}

void Node::newConnector(Connector* newC) {
    c = newC;
}

long Node::f(long nonce) {
    const long A = 48271;
    const long M = 2147483647;
    const long Q = M/A;
    const long R = M%A;

	static long state = 1;
	long t = A * (state % Q) - R * (state / Q);

	if (t > 0)
		state = t;
	else
		state = t + M;
	return (long)(((double) state/M)* nonce);
}



