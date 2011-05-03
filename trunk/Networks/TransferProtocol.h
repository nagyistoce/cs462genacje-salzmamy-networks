/* 
 * File:   TransferProtocol.h
 * Author: James
 *
 * Created on April 27, 2011, 9:32 PM
 */

#ifndef TRANSFERPROTOCOL_H
#define	TRANSFERPROTOCOL_H

#include "connector.h"
#include "TransferMetrics.h"
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <sys/time.h>
using namespace std;

#define RTTMULT 32 // the integer that you multiply RTT by to get a timeout



class TransferProtocol {
public:
    TransferProtocol();
    TransferProtocol(Connector*, int pkt_size, char* filename);
    TransferProtocol(const TransferProtocol& orig);
    virtual ~TransferProtocol();


    // OVERRIDE IN CHILD CLASS: //
    void run_sender(); // methods are called to initiate the protocol
    void run_receiver();

    // PUBLIC METHODS //
    void set_pkt_size(int s);

    

protected:
    Connector* c; // object that is used for secure transmission
    TransferMetrics metrics; // for displaying stats of the transmit
    long rtt; // round trip time - used for calculating timeouts

    int packet_size; // size of packet in bytes


    char fname[128]; // name of sent/received file
    ifstream file_to_send;
    ofstream file_received;
    int filesize;    // size of the file to send/receive


    // PROTECTED METHODS //
    // Inherited through all classes //
    int get_n_pings();
    void ping(int times); // sets rtt by averaging a specified num of pings
    void listen_for_pings(); // will listen for pings until an end ping is sent

    struct timeval send_packet(char* pkt); // sets send time in the packet **thread**
    void send_ack(long seq);

    // thread compatible
    void listen_for_ack(void* id); // returns the seq number of the ack'd packet


    void open_infile();
    bool read_infile(int bytes_to_read, char* array_to_fill);

    void open_outfile();
    void write_to_outfile(char* msg, int bytes_to_write);

private:
    // helper methods for parent class

};

#endif	/* TRANSFERPROTOCOL_H */

