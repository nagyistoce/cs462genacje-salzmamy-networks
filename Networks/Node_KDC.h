/* 
 * File:   Node_KDC.h
 * Author: GENACJE
 *
 * Created on February 24, 2011, 4:32 PM
 */

#include "Node.h"

#ifndef _NODE_KDC_H
#define	_NODE_KDC_H

class Node_KDC : public Node {
public:
    Node_KDC(Connector* c);
    virtual ~Node_KDC();

    void listen();
private:

    void getKeys();

    char keyA[56];
    char keyB[56];
    char keyS[56];

};

#endif	/* _NODE_KDC_H */

