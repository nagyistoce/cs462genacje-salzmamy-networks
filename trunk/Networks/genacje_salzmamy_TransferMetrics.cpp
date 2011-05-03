/* 
 * File:   TransferMetrics.cpp
 * Author: genacje
 * 
 * Created on May 2, 2011, 5:14 PM
 */

#include "genacje_salzmamy_TransferMetrics.h"

TransferMetrics::TransferMetrics() {
    
    lost_pkts = 0;
    total_bytes_sent = 0;
    total_pkts = 0;
    
}


TransferMetrics::TransferMetrics(const TransferMetrics& orig) {
}

TransferMetrics::~TransferMetrics() {
}

void TransferMetrics::set_total_pkts(long pkts) {
    this->total_pkts = pkts;
}

void TransferMetrics::increment_lost_pkts(long lost) {
    this->lost_pkts += lost;
}

void TransferMetrics::set_total_bytes_sent(long bytes) {
    this->total_bytes_sent = bytes;
}

void TransferMetrics::start_timer() {
    gettimeofday(&start_transmit, NULL);
}

void TransferMetrics::end_timer() {
    gettimeofday(&end_transmit, NULL);
}

void TransferMetrics::print_stats() {
    // calculate a detailed time in seconds for the transmission
    double duration = (double)( (end_transmit.tv_sec + (end_transmit.tv_usec / 1000000.0))
                           - (start_transmit.tv_sec + (start_transmit.tv_usec / 1000000.0)) );

    // in kbps
    double throughput = (double)total_bytes_sent / (duration * 1024);

    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~" << endl <<
              "~~~~~TransferMetrics~~~~~" << endl <<
              "Duration: " << duration << " sec" << endl <<
              "Total Bytes Sent: " << total_bytes_sent << endl <<
              "Total Packets Sent: " << total_pkts << endl <<
              "Total packet losses: " << lost_pkts << endl <<
              "Throughput: " << throughput << "kbps" << endl <<
              "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

}





