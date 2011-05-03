/* 
 * File:   StopAndWait.h
 * Author: genacje
 *
 * Created on April 30, 2011, 4:51 PM
 */

#ifndef _STOPANDWAIT_H
#define	_STOPANDWAIT_H

#include "genacje_salzmamy_TransferProtocol.h"

#define HEADERSIZE 8 // sizeof(long)

class StopAndWait : public TransferProtocol {
public:
    StopAndWait();
    StopAndWait(Connector*, int pkt_size, char* filename);
    StopAndWait(const StopAndWait& orig);
    virtual ~StopAndWait();

    void run_sender();
    void run_receiver();
private:
    long ack_id;
    static void* ack_thread(void* sw);
};

#endif	/* _STOPANDWAIT_H */

