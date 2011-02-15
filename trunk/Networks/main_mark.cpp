/*
 * main.cc
 *
 *  Created on: Feb 15, 2011
 *      Author: salzmamy
 */

#include <iostream>
#include <stdio.h>
#include "connector.h"

#define PORT 9000
#define ANDY "andy.cs.uwec.edu"
#define CLARK "clark.cs.uwec.edu"

char ask_role ();

using namespace std;

int main (void) {

	char role = ask_role();

	if (role == 'l') {
		Connector c(PORT);
		c.listen();
	} else if (role == 't') {
		Connector c(ANDY, PORT);
		c.send("testing, 1, 2, 3");
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
