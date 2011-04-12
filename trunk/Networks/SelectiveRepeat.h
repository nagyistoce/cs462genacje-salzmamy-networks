/* 
 * File:   SelectiveRepeat.h
 * Author: genacje
 *
 * Created on April 12, 2011, 3:22 PM
 */

#ifndef _SELECTIVEREPEAT_H
#define	_SELECTIVEREPEAT_H

#include "connector.h"

class SelectiveRepeat {
public:
    SelectiveRepeat(Connector* c);
    SelectiveRepeat(const SelectiveRepeat& orig);
    virtual ~SelectiveRepeat();

    /* Sender/Receiver protocol methods */
    void run_sender();
    void run_receiver();
private:
    
    /* Shared */
    int window_size;
    Connector* c;

    /* Sender */
    int send_base;
    int next_seq_num;
    void send_pkt_thread(void* data);

    /* Receiver */
    int recv_base;
    void send_ack(int seqnum);
    

};

#endif	/* _SELECTIVEREPEAT_H */

