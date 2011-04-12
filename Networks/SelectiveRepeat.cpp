/* 
 * File:   SelectiveRepeat.cpp
 * Author: genacje
 * 
 * Created on April 12, 2011, 3:22 PM
 */

#include "SelectiveRepeat.h"

SelectiveRepeat::SelectiveRepeat(Connector* c) {
    this->c = c;
}

SelectiveRepeat::SelectiveRepeat(const SelectiveRepeat& orig) {
    cout << "don't f*cking call the selective repeat copy constructor...\n" <<
        "It's a waste of memory." << endl;
}

SelectiveRepeat::~SelectiveRepeat() {
}


void SelectiveRepeat::run_sender() {
    /*TODO: complete this method: run_sender()*/
    
    // get window size as an input from the user.

    // send window size to receiver

    // receive ack + window size from receiver, validate

    // get file name as input from user

    // send file name to receiver

    // send file
}

void SelectiveRepeat::send_pkt_thread(void* data) {

}


void SelectiveRepeat::run_receiver() {
    
}

void SelectiveRepeat::send_ack(int seqnum) {

}