//block.h
// Author: Benjamin Fogiel
#include<iostream>
#include<cstring>

#ifndef BLOCK_H
#define BLOCK_H

using namespace std;

class Transaction {
public:
	Transaction(); // constructor
	Transaction(const Transaction &other); // copy constructor
	~Transaction(); // destructor

	void add(int a, string s, string r);
	int GetBalance(string person);
	void print() const;

	friend std::ostream& operator<<(std::ostream &os, const Transaction &l);

private:
	struct Block
	{
		Block* prev; // points previous transaction
		Block* next;
	       	int amount; // amount o f money that has been transferred
		char sender[100]; // sender of money
		char receiver[100]; // receiver of money
		char nonce[100]; // random string that will be used to simulate PoW
		char hash[100]; // hash of content of previous transaction
	};
	Block *head;
	Block *tail;	
};

std::ostream& operator<<(std::ostream &os, const Transaction &l);

#endif
