/* 
 * File:   genacje_salzmamy_AccuracyTest.cpp
 * Author: James
 * 
 * Created on May 7, 2011, 6:06 PM
 */

#include "genacje_salzmamy_AccuracyTest.h"

AccuracyTest::AccuracyTest() {

    n_dropped = 0;
    index_dropped = 0;
    n_damaged = 0;
    index_damaged = 0;

}

AccuracyTest::AccuracyTest(const AccuracyTest& orig) {
}

AccuracyTest::~AccuracyTest() {
    if (n_dropped > 0) {
        delete [] ids_dropped;
    }

    if (n_damaged > 0) {
        delete [] ids_damaged;
    }
}

// returns DROPPED if the id matches ids_dropped[index]
// if there are none to drop, check if it is damaged
// if it is neither, it is ok.
int AccuracyTest::analyze_packet(long id) {

    // if there are items to drop and we havent dropped them all yet,
    if (n_dropped != 0 && (index_dropped < n_dropped)) {
        // drop the packet if its on the next id.
        if (ids_dropped[index_dropped] == id) {
            cout << "~~Packet Drop Simulator: " << id << " dropped!~~" << endl;
            index_dropped++;
            return DROPPED;
        }
    }

    // secondarily, check for a damaged packet
    if (n_damaged != 0 && (index_damaged < n_damaged)) {
        // damage the packet if its on the next id.
        if (ids_damaged[index_damaged] == id) {
            cout << "~~Packet Damage Simulator: " << id << " damaged!~~" << endl;
            index_damaged++;
            return DAMAGED;
        }
    }

    // if we get through all of that, the packet is ok.
    return OK;
}

void AccuracyTest::init_receiver() {
    
    cin.ignore(2048, '\n');
    do {
        cout << "Enter the number of acks to drop (up to 15): " << endl;
        cin >> n_dropped;
    } while ( !((n_dropped <= 15) && (n_dropped >= 0)) );

    // fill the array of dropped acks
    if (n_dropped > 0) {
        ids_dropped = new long[n_dropped];
        memset(ids_dropped, '\0', sizeof(long)*n_dropped);

        cout << "Enter the ack ids to drop (in order for proper function): " << endl;

        for (int i = 0; i < n_dropped; i++) {
            cout << "Ack id - " << i+1 << "/" << n_dropped <<": ";
            cin >> ids_dropped[i];
            cout << endl;
        }

    }

}

void AccuracyTest::init_sender() {

    cin.ignore(2048, '\n');
    do {
        cout << "Enter the number of packets to drop (up to 15): " << endl;
        cin >> n_dropped;
    } while ( !((n_dropped <= 15) && (n_dropped >= 0)) );

    // fill the array of dropped acks
    if (n_dropped > 0) {
        ids_dropped = new long[n_dropped];
        memset(ids_dropped, '\0', sizeof(long)*n_dropped);

        cout << "Enter the packet ids to drop (in order for proper function): " << endl;

        for (int i = 0; i < n_dropped; i++) {
            cout << "Packet id - " << i+1 << "/" << n_dropped <<": ";
            cin >> ids_dropped[i];
            cout << endl;
        }

    }


    do {
        cout << "Enter the number of packets to damage (up to 15): " << endl;
        cin >> n_damaged;
    } while ( !((n_damaged <= 15) && (n_damaged >= 0)) );

    // fill the array of dropped acks
    if (n_damaged > 0) {
        ids_damaged = new long[n_damaged];
        memset(ids_damaged, '\0', sizeof(long)*n_damaged);

        cout << "Enter the packet ids to damage (in order for proper function): " << endl;

        for (int i = 0; i < n_damaged; i++) {
            cout << "Packet id - " << i+1 << "/" << n_damaged <<": ";
            cin >> ids_damaged[i];
            cout << endl;
        }

    }

}




