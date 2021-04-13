//block.h
// Author: Benjamin Fogiel
#include<iostream>
#include<cstring>

#ifndef TRANSACTION_H
#define TRANSACTION_H

using namespace std;

class Transaction {
public:
	Transaction(); // constructor
	Transaction(const Transaction &other); // copy constructor
	~Transaction(); // destructor

	void add(int a, string s, string r);
	int GetBalance(string person);
	void print() const;
	string hash(Transaction *b);

	friend std::ostream& operator<<(std::ostream &os, const Transaction &l);
	Transaction &operator=(const Transaction &other); // copy assignment

private:	
	struct Block
	{
		Block* prev; // points previous transaction
		Block* next;
	       	int amount; // amount o f money that has been transferred
		string sender; // sender of money
		string receiver; // receiver of money
		string nonce; // random string that will be used to simulate PoW
		string hash; // hash of content of previous transaction
	};
	Block *head;
	Block *tail;	
};

std::ostream& operator<<(std::ostream &os, const Transaction &l);

#endif
