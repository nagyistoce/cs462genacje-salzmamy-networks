/*
 * main.cc
 *
 *  Created on: Feb 15, 2011
 *      Author: salzmamy
 */

#include <iostream>
#include <stdio.h>
#include "connector.h"
#include "blowfish.h"

#define PORT 9000
#define ANDY "andy.cs.uwec.edu"
#define CLARK "clark.cs.uwec.edu"

char ask_role ();

using namespace std;

int main (void) {

	char role = ask_role();

	if (role == 'l') {
		Connector c(PORT);

                while (1) {
                    c.listen();
                    char* msg = c.getMsg();
                    Blowfish b = Blowfish();

                    b.Set_Passwd("31337");
                    cout << "Received msg: " << msg << endl;
                    b.Decrypt((void*)msg, 128);
                    cout << "Decrypted msg: " << msg << endl;

                }
		
	} else if (role == 't') {
		Connector c(ANDY, PORT);

                cout << "Talker: Enter messages to encrypt and send...\n";

                Blowfish b = Blowfish();
                b.Set_Passwd("31337");

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
                    } else if (msg != "") {

                        cout << "Encrypting msg: " << msg << endl;
                        b.Encrypt((void*)msg, 128);
                        cout << "Sending encrypted msg: " << msg << endl;
                        c.send(msg);
                    }
                }
                
		
	} else {
		perror ("incorrect role input");
		exit (1);
	}

	return 0;
}

char ask_role () {
	char role;

	cout << "What role are you?  l - listener : t - talker\n";
	cin >> role;

	return role;
}
