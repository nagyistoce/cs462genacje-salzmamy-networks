/* 
 * File:   Packet.h
 * Author: genacje
 *
 * Created on April 12, 2011, 4:17 PM
 */

#ifndef _PACKET_H
#define	_PACKET_H

#include <iostream>
using namespace std;

class Packet {
public:
    Packet();

    Packet(int size, int seq);
    Packet(const Packet& orig);
    virtual ~Packet();

    long get_start_time();
    void set_start_time(long t);
    char* get_data();
    int get_seq_num();
private:

    char* data;
    long start_time;
    // protocol specific //
    int seq_num;

};

#endif	/* _PACKET_H */

