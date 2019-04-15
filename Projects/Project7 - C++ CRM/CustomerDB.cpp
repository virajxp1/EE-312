/*
 * Name:
 * EID:
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

Customer& CustomerDB::operator[](String name) {
	//if customer in DB has name that matches the argument return the Customer by reference
	//else add a new customer to data base and then return a reference to that new customer
	// if capacity not enough double it

	if(!isMember(name)) {
		if(length >= capacity) { // create more space if length >= capacity
			Customer* other = new Customer[this->capacity *2];//create new instance
			for(int i =0;i<this->length;i++) { // copy over
				other[i].name = this->data[i].name;
                other[i].bottles = this->data[i].bottles;
                other[i].rattles = this->data[i].rattles;
                other[i].diapers = this->data[i].diapers;
			}
			delete [] this-> data; // free the data
			this->data = other;
			this->capacity *=2;
		}
		this->length++;
		this->data[length-1].name = name; //initilize values of new customer
		this->data[length-1].bottles = 0;
		this->data[length-1].rattles = 0;
		this->data[length-1].diapers = 0;
		return this->data[length-1]; //return reference
	}
	else { // if here than it is a member and just return the reference
		for(int i = 0; i<this->length;i++) {
			if(this->data[i].name == name)
				return this->data[i];
		}
	}
	return this->data[length]; // never reaches here just so complier dont complain
}

bool CustomerDB::isMember(String name) {
	//Searches through the current set of customers and returns true if it finds a customer with matching name
	for(int i = 0; i<this->length;i++) {
		if(this->data[i].name == name) // if names == return true
			return true;
	}
	return false;
}
