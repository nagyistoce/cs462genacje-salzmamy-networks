/* 
 * File:   GoBackN.h
 * Author: genacje
 *
 * Created on April 30, 2011, 10:34 PM
 */

#ifndef _GOBACKN_H
#define	_GOBACKN_H

#include "genacje_salzmamy_TransferProtocol.h"


#define HEADERSIZE 8 // sizeof(long)

class GoBackN : public TransferProtocol{
public:
    GoBackN();
    GoBackN(Connector* c, int pkt_size, char* filename, int window_size);
    GoBackN(const GoBackN& orig);
    virtual ~GoBackN();

    void run_sender();
    void run_receiver();

private:
    // threadable method that will run from the sender, collecting acks,
    // modifying the lowest ack received and highest id_acceptable vars
    // also sets 'done' when the algorithm is finished.
    static void* ack_thread(void* gbn);

    // sender vars only: receiver doesn't use them
    int window_size; // sender or receiver    
    long lowest_ack_received;
    long max_packet_id;
    

};

#endif	/* _GOBACKN_H */

