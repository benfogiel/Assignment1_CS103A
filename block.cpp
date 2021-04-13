//block.cpp

#include "block.h"
#include <iostream>
#include<cstring>
#include<iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include "openssl/sha.h"

using namespace std;

// creates empty list
Transaction::Transaction() : head(nullptr), tail(nullptr) {}

// destructor
Transaction::~Transaction() {
	Block* current = head;
	while (current != nullptr){
		Block* next = current -> next;
		delete current;
		current = next;
	}
}

// << operator to print transactions
std::ostream& operator<<(std::ostream &os, const Transaction &l) {
	Transaction::Block *c = l.head;

	while (c != nullptr){
		os << "Amount: " << c->amount << "\n" << "Sender: " << c->sender 
			<< "\n" << "Receiver: " << c->receiver << "\n" << "Nonce: "
			<< c-> nonce << "\nHash: " << c->hash << endl;
		c = c -> next;
	}
	return os;
}

void Transaction::print() const{
	cout << *this << endl;
}

//returns a hash given a string
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
    return ss.str();
}

void Transaction::add(int a, string s, string r){
	Block *b = new Block;

	b->amount = a;
	b->sender = s;
	b->receiver = r;

	if (head == nullptr && tail == nullptr) {
		head = b;
		tail = b;
	} else {
		tail->next = b;
		b->prev = tail;
		tail = b;
		b->hash = hash(this);
	}
	

	//Nonce Hash
	string am = to_string(b->amount);
        string cat = am + s + r + b->hash;
        string nonce = "a";

        while(sha256(cat + nonce).back() != '0'){
                nonce = rand()%26+97;
        }
        b->nonce = nonce;
}


// Given a block, hash will return based on the prev block data
// Cannot be the head block
string Transaction::hash(Transaction *t){
	Transaction:Block *b = t->tail;
	Block *p = b->prev;
	string a = to_string(p->amount);
	string cat = a + p->sender + p->receiver + p->hash + p->nonce;

	return sha256(cat);
}

int Transaction::GetBalance(string person){
	Block *current = head;
	char strArr[person.length() + 1];
	bool matchS = true; 
	bool matchR = true; 
	int balance = 50;

	strcpy(strArr, person.c_str());

	while (current != NULL){
		for(int i = 0; i < person.length()+1; i++){
			if (strArr[i] != current->receiver[i]) matchR = false;
			if (strArr[i] != current->sender[i]) matchS = false;
			if (!matchR && !matchS) break;
		}
		if (matchR) balance += current->amount;
		if (matchS) balance -= current->amount;
		matchR = true;
		matchS = true;
		current = current->next;
	}
	return balance;
}
