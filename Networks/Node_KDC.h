/* 
 * File:   Node_KDC.h
 * Author: GENACJE
 *
 * Created on February 24, 2011, 4:32 PM
 */

#include "Node.h"
#include "blowfish.h"

#ifndef _NODE_KDC_H
#define	_NODE_KDC_H

class Node_KDC : public Node {
public:
    Node_KDC(Connector* c);
    virtual ~Node_KDC();

    void listen();
    
private:

    /*~protocol methods~*/
    // called from within listen when a request comes in
    void getKeys(); // gets user input for the 3 keys
    void sendKDCResponse(); // sends the KDC response from to the initiator
    /*~~~~~~~~~~~~~~~~~~*/

    long nonce;
    char keyA[KEYSIZE];
    char keyB[KEYSIZE];
    char keyS[KEYSIZE];

};

#endif	/* _NODE_KDC_H */

