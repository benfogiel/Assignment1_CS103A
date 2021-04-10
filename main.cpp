// main.cpp
// Author: Benjamin Fogiel
#include<iostream>
#include "block.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <cstring>
#include "openssl/sha.h"

using namespace std;

// When compiling this file use:
// g++ -o main main.cpp -lssl -lcrypto

string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX c;
    SHA256_Init(&c);
    SHA256_Update(&c, str.c_str(), str.size());
    SHA256_Final(hash, &c);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    string s = ss.str();
    s.back() = '0';
    return s;
}

int main() {
	int input = 0;

// cout << sha256("6666661234567890_1") << endl;

	Transaction t;

	while (input != 4){
	cout << "Welcome to the transaction-chain application.... \n1) Add a transaction to the chain.\n2) Find balance of a person.\n3) Print the chain.\n4) Exit.\nWhich operation do you want to make? (1,2,3,4):" << endl;
	cin >> input;

	if (input == 1) {
		int amount;
		string sender, receiver;
		cout << "Integer amount of money:" << endl;
		cin >> amount;
		cout << "Sender name" << endl;
		cin >> sender;
		cout << "Receiver name" << endl;
		cin >> receiver;
		
		t.add(amount, sender, receiver);
	}

	if(input == 2){
		string person;

		cout << "Please type name (case-sensitive)" << endl;
		cin >> person;

		t.GetBalance(person);
	}

	if(input == 3) t.print();

	if(input == 4) break;
	}
	return 0;
}


