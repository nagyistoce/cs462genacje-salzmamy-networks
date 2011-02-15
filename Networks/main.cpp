/* 
 * File:   main.cpp
 * Author: genacje
 *
 * Created on February 15, 2011, 3:34 PM
 */
#include "blowfish.h"

#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include <string>
using namespace std;

/*
 * 
 */


// Requirements for blowfish to work:
// a key known to both parties
// a data size common to both parties
//  ->message data size must be a multiple of 8 bytes.

void encryption_demo() {
    int inputsize = 512;

    char input[inputsize];


    Blowfish b = Blowfish();
    b.Set_Passwd("313337");


    bool goodInput = false;
    cout << "Enter a message to encrypt." << endl;
    while (!goodInput) {

        // flush input stream
        cin.ignore(inputsize, '\n');
        // make sure cin gets the whole thing
        cin.get(input, inputsize);

        if (input != "") {
            goodInput = true;
        } else continue;

    }

    cout << "Input: " << input << endl;

    b.Encrypt((void*) input, inputsize);

    cout << "Encrypted message: " << input << endl;

    b.Decrypt((void*) input, inputsize);

    cout << "Decrypted message: " << input << endl;

    //b.~Blowfish();

}

int main(int argc, char** argv) {

    // enter 'client', 'server', or 'receiver'
    bool goodInput = false;

    cout << "Enter your role ('k'=kdc, 'i'=initiator, 'r'=receiver)" << endl;

    int inputsize = 512;

    char input[inputsize];
    while (!goodInput) {
        cin >> input;
        goodInput = true;
        if (input[0]=='k') {
            
        } else if (input[0]=='i') {
            
        } else if (input[0] == 'r') {
            
        } else {
            goodInput = false;
            cout << "Invalid input" << endl;
        }
    }

    encryption_demo();

    
    return (0);
}

