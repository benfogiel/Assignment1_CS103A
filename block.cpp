#include "block.h"
#include <iostream>
#include<cstring>

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
		os << c->amount << " " << c->sender 
			<< " " << c->receiver << " " << c-> nonce
			<< " " << c->hash << endl;
		c = c -> next;
	}
	return os;

void Transaction::add(int a, string s, string r){
	Block *b = new Block;
	b->amount = a;
	strcpy(b->sender, s.c_str());
	strcpy(b->receiver, r.c_str());

	if (head == nullptr && tail == nullptr) {
		head = b;
		tail = b;
	} else {
		tail->next = b;
		b->prev = tail;
		tail = b;
	}
}

int Transaction::GetBalance (string person){
	Block *current = tail;
	strArr[person.length() + 1];
	bool matchS = True, matchR = True; 
	int balance = 50;

	strcp(strArr, person.c_str());

	while (current != NULL){
		for(int i = 0; i < person.length()+1; i++){
			if (strrArr[i] != current->receiver[i]) matchR = False;
			if (strrArr[i] != current->sender[i]) matchS = False;
			if (!matchR && !matchS) break;
		}
		if (matchR) balance += current->amount;
		if (matchS) balance -= current->amount;
		matchR = True;
		matchS = True;
		current = current->next;
	}
	return balance;
}

}
