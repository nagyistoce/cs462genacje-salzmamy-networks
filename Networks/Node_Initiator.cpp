/* 
 * File:   Node_Initiator.cpp
 * Author: genacje
 * 
 * Created on March 8, 2011, 5:04 PM
 */

#include "Node_Initiator.h"


Node_Initiator::Node_Initiator(Connector* c) : Node(c) {
    cout << "\n\n~~Initiator~~\n\n";

    getStr(keyA, KEYSIZE, "Enter Ka:");
    c->set_key(keyA);

}


Node_Initiator::~Node_Initiator() {
    // no new'd things to delete
}

void Node_Initiator::send_request() {
    nonce = 0;
    getNonce(&nonce, "Enter a nonce: ");
    char msg[DEFAULTPKTSIZE];
    memset(msg, '\0', DEFAULTPKTSIZE);

    // copy the nonce into the request
    memcpy(msg, &nonce, sizeof(long));
    //char* request = "Requesting session key...";
    //memcpy(&msg[8], request, strlen(request));

    // [ nonce |           string              ]

    c->send(msg);

    return;
}

void Node_Initiator::get_kdc_response() {

    // KDC response will be in the format:
    // bytes 0-7 = nonce (8 bytes)
    // bytes 8-63 = keyS (56 bytes)
    // bytes 64-119 = EKb(Ks) (56 bytes)
    // = 120 bytes total

    c->listen();

    // copy the nonce and validate it
    long checkNonce = 0;
    memcpy(&checkNonce, c->get_msg(), sizeof(long));

    if (validate(checkNonce, nonce)) {
        cout << "Nonce: " << nonce << " validated!" << endl;
    } else {
        cout << "Nonce validation failed... " << endl
                << "Sent: " << nonce << endl
                << "Received: " << checkNonce << endl;
        exit(1);
    }
    

    // copy 56 bytes starting at index 8
    memset(keyS, '\0', KEYSIZE);
    memcpy(keyS, &c->get_msg()[8], KEYSIZE);

    cout << "Ks received: " << keyS << endl;


    // copy 56 bytes from index 64 EKb(Ks)
    memset(EKb_Ks, '\0', KEYSIZE);
    memcpy(EKb_Ks, &c->get_msg()[64], KEYSIZE);

    
    return;
}

void Node_Initiator::send_session_key() {
    cout << "Sending EKb(Ks) to the receiver..." << endl;

    // set session key so that we can decrypt messages adequately
    c->set_key(keyS);

    // but this message is already encrypted with Kb
    c->send_unencrypted(EKb_Ks);

    handshake();
    

    return;
}

void Node_Initiator::handshake() {
    // listen for nonce
    c->listen();

    long n = 0;


    memcpy((void*)&n, c->get_msg(), sizeof(long));

    cout << "Received nonce: " << n << endl;

    long n2 = f(n);

    char n2c[sizeof(long)];
    memset(n2c, '\0', sizeof(long));
    memcpy(n2c, (void*)&n2, sizeof(long));
    cout << "Sending f(nonce): " << n2 << endl;

    c->send(n2c);

    cout << "Listening for ack..." << endl;
    c->listen();

    if (strcmp(c->get_msg(), "ack") == 0) {
        cout << "***Key exchange complete***\n" << endl;
    }

    transmission();
}


/* Send    transmission protocol
     *     packet size
     *     window size
     *     file name
     *
     * -Receive validation.
     * -Transmit the file.
     */

void Node_Initiator::transmission() {

    cout << "Obtaining transmission data from user...\n" << endl;


    // packet should have 141 useful bytes:
    // [    1    |      4      |       8       |      128        ]
    // [protocol |  pkt size   |  window_size  |      fname      ]
    char protocol = 'x';
    int packet_size = -1;
    long window_size = 0;
    char filename[133];
    memset(filename, '\0', 133);
    memcpy(filename, "Send/", 5);

    do {
        getStr(&filename[5], 128,
          "Enter the name of a file in the cwd/'Send' folder: ");
    } while(strcmp(&filename[5], "") == 0);

    cout << "Enter a protocol: " << endl <<
            "  'w' = stop and wait" << endl <<
            "  'g' = go back n" << endl <<
            "  's' = selective repeat" << endl;

    while (protocol != 'w' && protocol != 'g' && protocol != 's') {
        cin.ignore(1024, '\n');
        cin >> protocol;
    }

    
    while (!( (packet_size > 0) && (packet_size < 64) ) ) {
        getInt(&packet_size,
                "Enter a packet size (in kb) between 1 and 63: ");
    }
    packet_size = packet_size*1024;

    char transmit_packet[DEFAULTPKTSIZE];
    memset(transmit_packet, '\0', DEFAULTPKTSIZE);

    // transmission_data_packet will look like:
    // [protocol |  packet_size   |   window_size | file_name]
    memcpy(transmit_packet, (void*)&protocol, 1); // fill byte 0 with the protocol
    memcpy(&transmit_packet[1], (void*)&packet_size, sizeof(int)); // bytes 1-4 = pkt size
    memcpy(&transmit_packet[13], &filename[5], 128); // filename
    
    if (protocol == 'w') {

        // have all the data we need - let the receiver know of our choices
        c->send(transmit_packet);
        

        // VALIDATE //
        c->listen();
        cout << "Transmission protocol acked." << endl;

        // make TransferProtocol object, run the protocol
        c->set_msg_size(packet_size);
        StopAndWait sw = StopAndWait(c, packet_size, filename);
        sw.run_sender();
        

    } else { // the other two protocols need window size

        while (!( (window_size > 0) && (window_size < 51) ) ) {
            getLong(&window_size,
                "Enter a window size between 1 and 50: ");
        }
        memcpy(&transmit_packet[5], &window_size, sizeof(long)); // fill last slot in packet
        c->send(transmit_packet);


        // VALIDATE //
        c->listen();
        cout << "Transmission protocol acked." << endl;
        
        
        

        c->set_msg_size(packet_size);

        if (protocol == 'g') { // go back n

            // create this Transfer Protocol object
            GoBackN gbn = GoBackN(c, packet_size, filename, window_size);
            // run the protocol
            gbn.run_sender();

        } else if (protocol = 's') { // selective repeat

            // create this Transfer Protocol object
            cout << "Selective repeat: todo..." << endl;
            // run the protocol


       }
    }
}


