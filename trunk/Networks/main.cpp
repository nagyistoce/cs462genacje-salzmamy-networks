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

        Connector *c = new Connector(PORT);
        
        
        if (role == 'k') {
                Node_KDC kdc = Node_KDC(c);
                kdc.listen();
        } else if (role == 'i') {
            // initiator:
            // input ka, send request, recv response from kdc
            // send encrypted ks to reciever
            // receive encrypted nonce
            // send fnonce

            // sendFile

        } else if (role == 'r') {
            // receiver:
            // input kb, receive ks,
            // send nonce
            // receive and validate nonce

            // receiveFile

        }
        


        if (role == 'l') {




                
                c->setKey("31337");
                while (1) {
                    c->listen();
                    char* msg = c->getMsg();
                    c->send("ack");

                }

        } else if (role == 't') {
                // hard coded to the listener for now...
                Connector* c = new Connector(CLARK, PORT);
                c->setKey("31337");
                cout << "Talker: Enter messages to encrypt and send...\n"
                << "Listener set to: " << CLARK << endl;


                char msg[c->getMsgSize()];
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
                    cout << c->getMsg() << endl;
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

        cout << "What role are you?  k - KDC :: l - listener : t - talker\n";
        cin >> role;

        return role;
}
