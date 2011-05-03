/* 
 * File:   TransferMetrics.h
 * Author: genacje
 * This is a utility for storing, modifying,
 * and displaying the metrics of a transfer protocol
 * Created on May 2, 2011, 5:14 PM
 */

#ifndef _TRANSFERMETRICS_H
#define	_TRANSFERMETRICS_H

#include <sys/time.h>
#include <iostream>
using namespace std;

class TransferMetrics {
public:
    TransferMetrics();

    TransferMetrics(const TransferMetrics& orig);
    virtual ~TransferMetrics();

    void set_total_pkts(long pkts);
    void increment_lost_pkts(long lost);
    void set_total_bytes_sent(long bytes);

    void start_timer();
    void end_timer();

    void print_stats();
    
private:

    struct timeval start_transmit;
    struct timeval end_transmit;

    long total_bytes_sent;
    long lost_pkts;
    long total_pkts;

};

#endif	/* _TRANSFERMETRICS_H */

