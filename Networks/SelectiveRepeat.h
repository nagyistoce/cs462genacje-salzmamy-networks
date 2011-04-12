/* 
 * File:   SelectiveRepeat.h
 * Author: genacje
 *
 * Created on April 12, 2011, 3:22 PM
 */

#ifndef _SELECTIVEREPEAT_H
#define	_SELECTIVEREPEAT_H

#include "connector.h"
#include <fstream>

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
    istream file_to_send;
    int file_size; // used to calculate max seq num
    int sender_base;
    int next_seq_num;
    void send_pkt_thread(void* data);

    /* Receiver */
    ostream file_to_write;
    int receiver_base;
    void send_ack(int seqnum);
    

};

#endif	/* _SELECTIVEREPEAT_H */

