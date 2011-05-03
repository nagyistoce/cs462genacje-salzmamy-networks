/* 
 * File:   GoBackN.cpp
 * Author: genacje
 * 
 * Created on April 30, 2011, 10:34 PM
 */

#include "GoBackN.h"

GoBackN::GoBackN() {
    cout << "Don't call GBN default constructor..." << endl;
}

GoBackN::GoBackN(Connector* c, int pkt_size, char* filename, int window_size) :
TransferProtocol(c, pkt_size, filename) {
    cout << "\n\n~~Go Back N~~\n\n";
    this->window_size = window_size;
}

GoBackN::GoBackN(const GoBackN& orig) {
    cout << "Don't call GBN copy constructor..." << endl;
}

GoBackN::~GoBackN() {
}

void GoBackN::run_sender() {
    cout << "~~Sender~~\n\n";
    open_infile();

    ping(get_n_pings());


    // data_window is structured like:
    // [long id|     data    ...        ]
    // [long id|     data    ...        ]
    // [long id|     data    ...        ]
    // [long id|     data    ...        ]
    //  .
    //  .
    //  .
    // [long id|     data    ...        ]
    char data_window[window_size][packet_size];
    // clean out the window
    memset(data_window, '\0', window_size*packet_size);


    struct timeval sent;
    struct timeval now;
    long time_diff = 0;
    long timeout_interval = rtt * RTTMULT + window_size;

    lowest_ack_received = -1;
    // need a temp to set as we set up the arrays
    // so the concurrent thread doesn't screw up the order
    // of the reformatted packet array
    long tmp_last_received = lowest_ack_received;

    max_packet_id = -2; // once this is set, the file has been totally read
    long last_id_sent = -1;
    long repeat_num = 0; // number of packets to repeat

    // thread for receiving acks
    pthread_t acks;
    pthread_create(&acks, NULL, ack_thread, this);

    
    // looping data
    int iterations = 0;
    bool done = false;
    bool file_read = false;
    metrics.start_timer();
    while(!done) {

        cout << "\n~~~~~Round: " << iterations << "~~~~~" <<endl;

        if (file_read) { // no more to read, just retransmitting the last frame
            // transmit items in the window need to be resent
            // they will be in order in data_window
            // at indexes 0 -> window_size

            // TRANSMIT //
            gettimeofday(&sent, NULL); // set start time.

            for (long i = 0; i < window_size; i++) {
                memcpy(&last_id_sent, data_window[i], sizeof(long));
                cout << "Resending packet: " << last_id_sent << endl;
                send_packet(data_window[i]);     
                
            }

        } else { // more to read
            // if there are elements to repeat, repeat number will be set
            // to the number of 'missed' elements. these missed elements
            // will be already loaded into the array in order, ready to be resent
            
            // there will be vacancies in the repeat array if some, but not all
            // of the packets in the previous round got acked.
            
            // if all of the packets are acked, none are repeated.


            // TRANSMIT //
            gettimeofday(&sent, NULL); // set start time.

            // need something that will not change so it will not get
            // dynamically mutated and screw up the order
            
            for (long i = 0; i < window_size; i++) {

                if (i < repeat_num) {
                    memcpy(&last_id_sent, data_window[i], sizeof(long));
                    cout << "Resending packet: " << last_id_sent << endl;
                    send_packet(data_window[i]);
                } else {
                    if (read_infile(packet_size-HEADERSIZE, &data_window[i][HEADERSIZE])) {
                        // set packet id to be lowest ack received +1 + window offset(i)

                        last_id_sent = (tmp_last_received+i+1);
                        memcpy(data_window[i], &last_id_sent, sizeof(long));
                        send_packet(data_window[i]);
                        cout << "Sending packet: " << last_id_sent << endl;
                    } else {

                        file_read = true;
                        // reset window size to be smaller!
                        window_size = i;

                        // brk
                        i = window_size;
                    }
                }

            } // for
            // clean up: if the last item of the window consumed the file, set
            // file_read to prevent packet_window from getting cleared.
            if (file_to_send.eof()) {
                file_read = true;
                // set max packet id so we can end
                memcpy(&max_packet_id, data_window[window_size-1], sizeof(long));
            }
     

        } // TRANSMIT done //

        // TIMEOUT loop //
        do { // main thread checks timeout
            gettimeofday(&now, NULL);
            time_diff = (now.tv_usec-sent.tv_usec)/1000;

            if (time_diff < 0) {
                // lets just say its a timeout and get 2 new times...
                time_diff = timeout_interval; // timeout
            }
        }while ( (lowest_ack_received != last_id_sent) && (time_diff < timeout_interval) );

        // REFACTOR NEXT ROUND //

        // combat against concurrency issues
        tmp_last_received = lowest_ack_received;

        // number to repeat
        repeat_num = last_id_sent - tmp_last_received;
        cout << "Number of packets to resend from this round: " << repeat_num << endl;
        metrics.increment_lost_pkts(repeat_num); // LOST N PACKETS
        if (repeat_num > 0) {

                int replace_index = 0; // where the repeated value should go

                for (int i = (window_size-repeat_num); i < window_size; i++) {
                    memcpy(data_window[replace_index], data_window[i], packet_size);
                    replace_index++;
                }

                if (file_read) {
                // adjust window size - scale it down based on how many transmitted
                window_size -= (window_size - repeat_num);
                }

        } else {
            // if lowest_ack_received = pax_packet_id, we are done.
            if (lowest_ack_received == max_packet_id) {
                done = true;
            }

        }
        
        iterations++;

        cout << "Lowest ack received: " << tmp_last_received << endl <<
                "Max packet id: " << max_packet_id << endl << endl;
            
        
    }
    pthread_cancel(acks);


    metrics.end_timer(); // END TIMER
    metrics.set_total_pkts(max_packet_id+1); // SET TOTAL PACKETS = the last ID +1
    metrics.set_total_bytes_sent((max_packet_id+1)*(packet_size-HEADERSIZE));
    // SET BYTES SENT: = number of packets sent * packet_size-HEADERSIZE

    // end transmission
    cout << "File sent... sending termination packet..." << endl;
    memcpy(data_window[0], "/&&", 3);
    memset(&data_window[0][3], '\0', 1);
    send_packet(data_window[0]);

    cout << "\n\n~~Done~~\n\n";


    // FINALLY, PRINT THE METRIC INFO
    metrics.print_stats();

}

// pretty much identical to S&W receiver
void GoBackN::run_receiver() {
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

                    cout << "Packet " << id << " received in order." << endl;
                    // fill data
                    memcpy(data, &c->get_msg()[HEADERSIZE], packet_size-HEADERSIZE);
                    write_to_outfile(data, packet_size-HEADERSIZE);

                    // ack the packet
                    send_ack(id);

                    expected_id++; // expect the next one
                } else if (id < expected_id) {
                    // ack must have been lost
                    cout << "Already received this packet - resending ack..." << endl;
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

void* GoBackN::ack_thread(void* gbn) {
    GoBackN* x = (GoBackN*) gbn;
    while (1) {
        x->c->listen();
        long a = 0;
        memcpy(&a, x->c->get_msg(), sizeof(long));

        if (a > x->lowest_ack_received) {
            x->lowest_ack_received = a;
            cout << "Packet " << a << " acked!" << endl;
        } else {
            cout << "'Unnexpected' ack for " << a << " received." << endl;
        }
    }
}



