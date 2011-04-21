/* 
 * File:   Node.h
 * Author: GENACJE
 *
 * Created on February 24, 2011, 4:25 PM
 */

#ifndef _NODE_H
#define	_NODE_H

#define KEYSIZE 56 // max blowfish pw length

#include "Connector.h"

#include <iostream>
using namespace std;

class Node {
public:
    Node(Connector*);
    virtual ~Node();
    static void getStr(char* strToGet, int size, char* prompt);
    static void getInt(int* intToGet, char* prompt);
    void newConnector(Connector* newC);
    static long f(long nonce);
protected:
    Connector* c;
    TransferProtocol* tp;

    
    void getNonce(long* nonce, char* msg);
    bool validate(long& mine, long& theirs);

};

#endif	/* _NODE_H */

