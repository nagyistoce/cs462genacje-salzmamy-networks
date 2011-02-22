/*
 * main.cc
 *
 *  Created on: Feb 15, 2011
 *      Author: salzmamy
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "connector.h"


#define PORT 9000
#define ANDY "andy.cs.uwec.edu"
#define CLARK "clark.cs.uwec.edu"
#define SHIVA "shiva.cs.uwec.edu"

char ask_role ();

using namespace std;

int main (void) {

	char role = ask_role();

	if (role == 'l') {
		Connector c(PORT);
                c.setKey("31337");
                while (1) {
                    c.listen();
                    char* msg = c.getMsg();
                    
                }
		
	} else if (role == 't') {
		Connector c(SHIVA, PORT);
                c.setKey("31337");
                cout << "Talker: Enter messages to encrypt and send...\n";

                
                char msg[c.getMsgSize()];
                bool quit = false;
                while(!quit) {
                    // flush input stream
                    cin.ignore(128, '\n');
                    // make sure cin gets the whole thing
                    cin.get(msg, 128);

                    if (msg == "-quit") {
                        quit = true;
                        continue;
                    } /*else if ((msg == "") || (msg[0] == "\n")) {
                        continue;
                    }*/
                    c.send(msg);
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
