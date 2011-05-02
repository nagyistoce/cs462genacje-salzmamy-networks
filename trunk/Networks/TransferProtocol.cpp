/* 
 * File:   TransferProtocol.cpp
 * Author: James
 * 
 * Created on April 27, 2011, 9:32 PM
 */

#include "TransferProtocol.h"


TransferProtocol::TransferProtocol() {
    cout << "Default TransferProtocol constructor called - not what we want."
            << endl;
}

TransferProtocol::TransferProtocol(Connector* c, int pkt_size, char* filename) {
    this->c = c;
    this->packet_size = pkt_size;

    memset(fname, '\0', 128);
    memcpy(fname, filename, 128);

}

TransferProtocol::TransferProtocol(const TransferProtocol& orig) {
}

TransferProtocol::~TransferProtocol() {
    if (file_to_send != NULL) {
        file_to_send.close();
    }
    if (file_received != NULL) {
        file_received.close();
    }
}

void TransferProtocol::run_sender() { // not implemented in parent class
    cout << "run_sender() not implemented at the parent level..." << endl;
}

void TransferProtocol::run_receiver() { // not implemented in parent class
    cout << "run_receiver() not implemented at the parent level..." << endl;
}


void TransferProtocol::open_infile() {
    file_to_send.open(fname, ios::in);
}

bool TransferProtocol::read_infile(int bytes_to_read, char* array_to_fill) {
    if (!file_to_send.eof()) {
        file_to_send.read(array_to_fill, bytes_to_read);
        return true;
    } else {
        cout << "\n\n** end of input file **\n\n";
        return false;
    }
}

void TransferProtocol::open_outfile() {
    file_received.open(fname, ios::out);
}

void TransferProtocol::write_to_outfile(char* msg, int bytes_to_write) {
    // write the data sent minus the leading sequence info.
    file_received.write(msg, bytes_to_write);
    file_received.flush();
    cout << bytes_to_write << " bytes written to " << fname << endl;
}

void TransferProtocol::set_pkt_size(int s) {
    this->packet_size = s;
    c->set_msg_size(s);
}

int TransferProtocol::get_n_pings() {
    cin.ignore(2048, '\n');
    int i = -1;

    while (!((i > 0) && (i < 11))) {
        cout << "Enter the number of pings you wish to send (1-10):" << endl;
        cin >> i;
    }
    return i;
}

/*TODO: Test ping() and listen_for_pings()*/
// called by child sender to calculate RTT
void TransferProtocol::ping(int times) {
    long ping_sum = 0;
    struct timeval start;
    struct timeval end;
    char ping[packet_size];
    memcpy(ping, "~~Ping~~", 8);
    memset(&ping[8], '\0', 1);
    while(times--) {
        
        gettimeofday(&start, NULL);
        c->send(ping);

        c->listen(); // get ack back
        gettimeofday(&end, NULL);

        cout << "Ping: " << (long)((end.tv_usec-start.tv_usec)/1000) <<
                "ms..." << endl;
        ping_sum += (long)((end.tv_usec-start.tv_usec)/1000);

        
        sleep(1);
    }
    memcpy(ping, "~/Ping/~", 8);
    c->send(ping); // send end ping signal
    c->listen(); // gets final ack

    // finally, set rtt based on the collected data

    rtt = (ping_sum/times);
    if (rtt > 10) {
        cout << "RTT set to the average ping (" << rtt << "ms)." << endl;
    } else {
        rtt = 10; // 10 ms floor on the rtt
        cout << "RTT set to minimum: " << rtt << "ms." << endl;
    }
}

void TransferProtocol::listen_for_pings() {
    bool exit = false;
    char ack[packet_size];
    memcpy(ack, "ack", 3);
    memset(&ack[3], '\0', 1);
    while (!exit) {
        c->listen();
        if (strcmp("~/Ping/~", c->get_msg()) == 0) {
            exit = true;
        }

        c->send(ack);
        cout << "Acking a ping request." << endl;
    }
    cout << "Received end ping request." << endl << endl;
}


// the send_packet method below is thread compatible.
struct timeval TransferProtocol::send_packet(char* pkt) {

    struct timeval now;

    // set start time so we can know when to resend
    gettimeofday(&now, NULL);
    c->send(pkt);

    return now;
}

void TransferProtocol::send_ack(long seq) {
    char ack[packet_size];
    memset(ack, '\0', 8);
    memcpy(ack, &seq, sizeof(long));
    char* ackstr = "ack";
    memcpy(&ack[sizeof(long)], ackstr, strlen(ackstr));

    c->send(ack);

    cout << "Sending ack " << seq << "." << endl;

}

// ack format should be [long seq|'ack' ... ]
void TransferProtocol::listen_for_ack(void* id) {
    c->listen();
    memcpy(id, c->get_msg(), sizeof(long));
}


