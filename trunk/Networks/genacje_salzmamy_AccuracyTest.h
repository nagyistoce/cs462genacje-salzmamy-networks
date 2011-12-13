/* 
 * File:   genacje_salzmamy_AccuracyTest.h
 * Author: James
 *
 * Created on May 7, 2011, 6:06 PM
 */

#ifndef GENACJE_SALZMAMY_AccuracyTest_H
#define	GENACJE_SALZMAMY_AccuracyTest_H

#include <iostream>
using namespace std;

// Pre-defined status numbers
#define DROPPED 2
#define DAMAGED 1
#define OK 0

class AccuracyTest {
public:
    AccuracyTest();
    AccuracyTest(const AccuracyTest& orig);
    virtual ~AccuracyTest();
    
    // drops a packet if the id matches ids[index]
    int analyze_packet(long id); // returns a status

    void init_receiver();
    void init_sender();
private:

    // vars for dropped packets or acks
    int n_dropped;
    long* ids_dropped;
    int index_dropped;

    // vars for damaged packets
    int n_damaged;
    long* ids_damaged;
    int index_damaged;



};

#endif	/* GENACJE_SALZMAMY_AccuracyTest_H */

