/*
 * main.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: salzmamy
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "genacje_salzmamy_connector.h"
#include "genacje_salzmamy_Node.h"
#include "genacje_salzmamy_Node_KDC.h"
#include "genacje_salzmamy_Node_Initiator.h"
#include "genacje_salzmamy_Node_Receiver.h"

#define PORT 9001
#define ANDY "andy.cs.uwec.edu"
#define CLARK "clark.cs.uwec.edu"
#define SHIVA "shiva.cs.uwec.edu"

char ask_role();

using namespace std;

int main(void) {

    char role = ask_role();

    Connector *c;

    if (role == 'k') {

        c = new Connector(PORT); // listening constructor
        Node_KDC kdc = Node_KDC(c);
        kdc.listen();

    } else if (role == 'i') { // initiator:
        
        // get KDC URL
        char kdc[128];
        memset(kdc, '\0', 128);
        Node::getStr(kdc, 128, "Enter the KDC URL:");
        c = new Connector(kdc, PORT);

        Node_Initiator ini = Node_Initiator(c);

        // send request, receive response from kdc
        ini.send_request();
        ini.get_kdc_response();


        // set up connection with receiver
        char recv[128];
        memset(recv, '\0', 128);
        cin.ignore(128, '\n');
        Node::getStr(recv, 128, "Press Enter then enter the receiver URL:");
        cout << "Entered: " << recv << endl;
        Connector *c2 = new Connector(recv, PORT);
        ini.newConnector(c2);

        // send encrypted ks to reciever
        ini.send_session_key(); // also handles the receiver response
        // chain calls to send the file too.
        delete c2;
        
    } else if (role == 'r') {
        // receiver:
        c = new Connector(PORT); // listening constructor
        Node_Receiver rec = Node_Receiver(c);
        rec.listen();

        // receive file

    } else {
        perror("incorrect role input");
        exit(1);
    }

    delete c;
    return 0;
}

char ask_role() {
    char role;

    cout << "What role are you?  k - KDC : i - Initiator : r - Receiver\n";
    cin >> role;

    return role;
}
