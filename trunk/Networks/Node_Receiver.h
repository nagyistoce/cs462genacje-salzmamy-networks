/* 
 * File:   Node_Receiver.h
 * Author: genacje
 *
 * Created on March 3, 2011, 4:01 PM
 */
#include "Node.h"


#ifndef _NODE_RECEIVER_H
#define	_NODE_RECEIVER_H

class Node_Receiver : public Node {
public:
    Node_Receiver(Connector* c);
    virtual ~Node_Receiver();

    void listen();
private:

    /*~protocol methods~*/
    // called from within listen
    // when a request comes in
    void validate_connection(); // sends a nonce, then validates it
    void start_protocol(); // listens for the protocol packet
    /*~~~~~~~~~~~~~~~~~~*/

    char keyB[KEYSIZE];
    char keyS[KEYSIZE];
    long nonce2;


};

#endif	/* _NODE_RECEIVER_H */

