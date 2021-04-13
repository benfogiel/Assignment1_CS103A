//block.cpp

#include "block.h"
#include <iostream>
#include<cstring>
#include<iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include "openssl/sha.h"
#include <random>

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

std::string random_string(std::size_t length)
{
    const std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}


void Transaction::add(int a, string s, string r){
	Block *b = new Block;

	b->amount = a;
	b->sender = s;
	b->receiver = r;

	if (head == nullptr && tail == nullptr) {
		head = b;
		tail = b;
		b->hash = "NULL";
	} else {
		tail->next = b;
		b->prev = tail;
		tail = b;
		b->hash = hash(this);
	}
	

	//Create nonce
	string am = to_string(b->amount);
        string cat = am + s + r + b->hash;
        string nonce = "a";
	srand (time(NULL));

        while(sha256(cat + nonce).back() != '0'){
		nonce = random_string(2);
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
	int balance = 50;

	while (current != NULL){
		if (person == current->sender) balance -= current->amount;
		if (person == current->receiver) balance += current->amount;
		current = current->next;
	}
	return balance;
}
