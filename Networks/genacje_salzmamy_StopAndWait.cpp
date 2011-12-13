/* 
 * File:   StopAndWait.cpp
 * Author: genacje
 * 
 * Created on April 30, 2011, 4:51 PM
 */

#include "genacje_salzmamy_StopAndWait.h"

StopAndWait::StopAndWait() {
}

StopAndWait::StopAndWait(Connector* c, int pkt_size, char* filename) :
TransferProtocol(c, pkt_size, filename) {
    cout << "\n\n~~~Stop and Wait~~~\n\n";
}

StopAndWait::StopAndWait(const StopAndWait& orig) {
    cout << "Don't call StopAndWait's copy constructor..." << endl;
}

StopAndWait::~StopAndWait()  {
    //~TransferProtocol();
}

void StopAndWait::run_sender() {
    cout << "~~Sender~~\n\n";
    
    open_infile();

    ping(get_n_pings());


    // packet is structured like: 
    // [long id|     data    ...        ]
    char data[packet_size];
    memset(data, '\0', packet_size);
    // header info
    long pkt_id = 0;

    struct timeval sent;
    struct timeval now;
    long time_diff = 0;
    long timeout_interval = rtt * RTTMULT;

    bool pkt_sent = false;
    pthread_t listenthread; // thread for listening
    ack_id = -1;

    pthread_create(&listenthread,
              NULL, ack_thread, this ); // modifies ack_id when done

    metrics.start_timer(); // START TIMER //

    int attempts = 0;
    // Read data from file:
    // Stop looping once file is completely read & sent.
    while(read_infile(packet_size-HEADERSIZE, &data[HEADERSIZE])) {

        // fill header (id number)
        memcpy(data, &pkt_id, sizeof(long));

        // send the filled packet

        do {
            
            
            sent = send_packet(data); // sent time is stored
            
            
            cout << "Packet " << pkt_id << " sent." << endl <<
                    "Attempt: " << attempts << endl;
            


            // must either receive ack or hit a timeout to resend...
            do { // main thread checks timeout
                gettimeofday(&now, NULL);
                time_diff = (now.tv_usec-sent.tv_usec)/1000;

                if (time_diff < 0) {
                    // lets just say its a timeout and get 2 new times...
                    time_diff = timeout_interval; // timeout
                }
            }while ( (ack_id != pkt_id) && (time_diff < timeout_interval) );
            
            
            
            if (ack_id == pkt_id) { // got the ack
                pkt_sent = true;
                attempts = 0;
                cout << "Packet " << pkt_id << " acked." << endl;
            } else {
                attempts++;
                cout << "Packet " << pkt_id << " timed out. Resending..." << endl;
                metrics.increment_lost_pkts(1); // LOST A PACKET
            }

        }while(!pkt_sent);

        // packet sent, clean up
        pkt_id++;
        pkt_sent = false;
        memset(data, '\0', packet_size);
    }
    pthread_cancel(listenthread);
    metrics.end_timer(); // END TIMER
    metrics.set_total_pkts(pkt_id+1); // SET TOTAL PACKETS = the last ID +1
    metrics.set_total_bytes_sent((pkt_id+1)*(packet_size-HEADERSIZE));
    // SET BYTES SENT: = number of packets sent * packet_size-HEADERSIZE


    // end transmission
    cout << "File sent... sending termination packet..." << endl;
    memcpy(data, "/&&", 3);
    c->send(data);

    // FINALLY, PRINT THE METRIC INFO
    metrics.print_stats();

}

void StopAndWait::run_receiver() {
    cout << "~~Receiver~~\n\n";
    open_outfile();

    listen_for_pings();

    // packet is structured like:
    // [long id|     data    ...        ]
    char data[packet_size];
    memset(data, '\0', packet_size);

    // header info
    long id = -1;
    long expected_id = 0;

    bool done = false;
    while(!done) {

        // if we received a crc-validated packet
        if (c->listen()) {

            // check for last packet: "/&&"
            if (strcmp(c->get_msg(), "/&&") == 0) {
                cout << "\n\n~~Done~~\n\n";
                done = true;
            } else { // not last packet
                // fill header
                memcpy(&id, c->get_msg(), sizeof(long));

                // if this is the packet that we are expecting, store it
                if (id == expected_id) {

                    cout << "Packet " << id << " received." << endl;
                    // fill data
                    memcpy(data, &c->get_msg()[HEADERSIZE], packet_size-HEADERSIZE);
                    write_to_outfile(data, packet_size-HEADERSIZE);

                    // ack the packet
                    send_ack(id);

                    expected_id++; // expect the next one
                } else if (id < expected_id) {
                    // ack must have been lost
                    send_ack(id);
                } else { // out of order packet
                    cout << "Ignoring out of order packet...\n" <<
                            "Expected: " << expected_id << endl <<
                            "Received: " << id << endl << endl;
                }

            }

        }  else { //packet has been corrupted
            cout << "Ignoring damaged packet..." << endl << endl;
        }
    }

}

void* StopAndWait::ack_thread(void* sw) {
        cout << "ack_thread started..." << endl << endl;
        StopAndWait* s = (StopAndWait* )sw;

        while(1) {
            s->c->listen();
            // store the packet_id of the ack into id
            memcpy(&s->ack_id, s->c->get_msg(), sizeof(long));
        }

        
        
        

        cout << "ack_thread finished... id:" << (s->ack_id) << endl;
}
