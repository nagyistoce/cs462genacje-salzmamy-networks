/*
 * main.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: salzmamy
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "connector.h"
#include "Node.h"
#include "Node_KDC.h"
#include "Node_Initiator.h"
#include "Node_Receiver.h"

#define PORT 9001
#define ANDY "andy.cs.uwec.edu"
#define CLARK "clark.cs.uwec.edu"
#define SHIVA "shiva.cs.uwec.edu"

char ask_role ();

using namespace std;

int main (void) {

        char role = ask_role();

        // example for KDC:
        // Node kdc = Node_KDC(c);
        // kdc.listen();

        Connector *c;
        
        
        if (role == 'k') {
            c = new Connector(PORT); // listening constructor
            Node_KDC kdc = Node_KDC(c);
            kdc.listen();
                
        } else if (role == 'i') {
            // initiator:

            
            
            // get KDC URL
            char kdc[128];
            memset(kdc, '\0', 128);
            Node::getStr(kdc, 128, "Enter the KDC URL:");
            c = new Connector(kdc, PORT);

            Node_Initiator ini = Node_Initiator(c);

            // send request, receive response from kdc
            ini.sendRequest();
            ini.getKDCResponse();
            
            
            // set up connection with receiver
            char recv[128];
            memset(recv, '\0', 128);
            Node::getStr(recv, 128, "Enter the receiver URL:");
            c = new Connector(recv, PORT);
            ini.newConnector(c);

            // send encrypted ks to reciever
            ini.sendSessionKey();


            // receive encrypted nonce
            // send fnonce


            // get file name

            // sendFile

        } else if (role == 'r') {
            // receiver:
            c = new Connector(PORT); // listening constructor
            Node_Receiver rec = Node_Receiver(c);
            rec.listen();
            
            // input kb, receive ks,
            // send nonce
            // receive and validate nonce

            // receiveFile

        }
        


        if (role == 'l') {

                
                c->set_key("31337");
                while (1) {
                    c->listen();
                    char* msg = c->get_msg();
                    c->send("ack");

                }

        } else if (role == 't') {
                // hard coded to the listener for now...
                Connector* c = new Connector(CLARK, PORT);
                c->set_key("31337");
                cout << "Talker: Enter messages to encrypt and send...\n"
                << "Listener set to: " << CLARK << endl;

                
                char msg[128];
                bool quit = false;
                while(!quit) {
                    // flush input stream
                    cin.ignore(128, '\n');
                    // make sure cin gets the whole thing
                    cin.get(msg, 128);

                    if (msg == "-quit") {
                        quit = true;
                        continue;
                    }
                    c->send(msg);
                    c->listen();
                    cout << c->get_msg() << endl;
                }


        } else {
                perror ("incorrect role input");
                exit (1);
        } 

        delete c;

        return 0;
}

char ask_role () {
        char role;

        cout << "What role are you?  k - KDC : i - Initiator :: l - listener : t - talker\n";
        cin >> role;

        return role;
}
