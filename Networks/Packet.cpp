/* 
 * File:   Packet.cpp
 * Author: genacje
 * 
 * Created on April 12, 2011, 4:17 PM
 */

#include "Packet.h"

Packet::Packet() {
    data = new char[8*1024]; // 8 kb = default
}

Packet::Packet(int size, int seq) {
    data = new char[size];
    seq_num = seq;
}

Packet::Packet(const Packet& orig) {
    cout << "Don't call the packet's #(" << seq_num <<
            ") copy constructor!" << endl;
}

Packet::~Packet() {
    delete [] data;
}

void Packet::set_start_time(long t) {
    this->start_time = t;
}

long Packet::get_start_time() {
    return start_time;
}

char* Packet::get_data() {
    return data;
}

