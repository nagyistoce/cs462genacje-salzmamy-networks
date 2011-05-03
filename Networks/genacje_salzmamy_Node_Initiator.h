/* 
 * File:   Node_Initiator.h
 * Author: genacje
 *
 * Created on March 8, 2011, 5:04 PM
 */

#include "genacje_salzmamy_Node.h"

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
    void transmission();

    char receiverURL[128];
    long nonce;
    char keyA[KEYSIZE];
    char EKb_Ks[KEYSIZE];
    char keyS[KEYSIZE];
    
};

#endif	/* _NODE_INITIATOR_H */

