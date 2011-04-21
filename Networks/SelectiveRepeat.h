/* 
 * File:   SelectiveRepeat.h
 * Author: genacje
 *
 * Created on April 12, 2011, 3:22 PM
 */

#ifndef _SELECTIVEREPEAT_H
#define	_SELECTIVEREPEAT_H

#include "connector.h"
#include "Packet.h"

#include <fstream>
#include <list>
#include <iterator>

//using namespace std;

class SelectiveRepeat  {
public:
    SelectiveRepeat();
    SelectiveRepeat(Connector* c);
    SelectiveRepeat(const SelectiveRepeat& orig);
    virtual ~SelectiveRepeat();

    /* Sender/Receiver protocol methods */
    void run_sender();
    void run_receiver();
    
    
private:
    Connector* c;
    /* Shared vars */
    int window_size;
    int packet_size;
    char* filename; // file being sent or received

    // waiting packets on sender side
    // packets received on receiver side
    list<Packet> packets;
    

    /* Sender */
    
    int file_size; // used to calculate max seq num
    int sender_base;
    int next_seq_num;
    void send_pkt_thread(void* data);

    /* Receiver */
    
    int receiver_base;
    void send_ack(int seqnum);
    

};

#endif	/* _SELECTIVEREPEAT_H */

