/* 
 * File:   Node_Initiator.h
 * Author: genacje
 *
 * Created on March 8, 2011, 5:04 PM
 */

#include "Node.h"

#ifndef _NODE_INITIATOR_H
#define	_NODE_INITIATOR_H

class Node_Initiator : public Node {
public:
    Node_Initiator(Connector* c);
    virtual ~Node_Initiator();

    void send_request();
    void get_kdc_response();

    void send_session_key();
private:

    void handshake();
    void get_transmission_data();

    // char kdcURL[128];
    char receiverURL[128];

    long nonce;
    char keyA[KEYSIZE];
    char EKb_Ks[64];
    char keyS[KEYSIZE];

    
};

#endif	/* _NODE_INITIATOR_H */

