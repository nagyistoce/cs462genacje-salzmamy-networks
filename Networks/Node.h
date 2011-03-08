/* 
 * File:   Node.h
 * Author: GENACJE
 *
 * Created on February 24, 2011, 4:25 PM
 */

#ifndef _NODE_H
#define	_NODE_H

//#define KEYSIZE 56 // max blowfish pw length

#include "Connector.h"

#include <iostream>
using namespace std;

class Node {
public:
    Node(Connector*);
    virtual ~Node();

protected:
    Connector* c;
    
    int KEYSIZE = 56;

    void getStr(char* key, char* prompt);
    bool validate(long& mine, long& theirs);

};

#endif	/* _NODE_H */

