/*
 * Name:
 * EID:
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */

#include <stdio.h>
#include <iostream>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"

void readString(String&);
void readNum(int&);

CustomerDB database;

using namespace std;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	database.clear();
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the 
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(String word) {
	if (word == "Bottles") {
		return &num_bottles;
	} else if (word == "Diapers") {
		return &num_diapers;
	} else if (word == "Rattles") {
		return &num_rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
	if (word == "Bottles") {
		return &cust.bottles;
	} else if (word == "Diapers") {
		return &cust.diapers;
	} else if (word == "Rattles") {
		return &cust.rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 * 
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the 
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
	Customer* result = 0;
	int max = 0;
	for (int k = 0; k < database.size(); k += 1) {
		Customer& cust = database[k];
		int *p = selectInventItem(type, cust); 
		if (*p > max) {
			max = *p;
			result = &cust;
		}
	}
	
	return result;
}

void processPurchase() {
    String name;
    String type;
    int purchase;
    readString(name); // name = customer name
    readString(type); // type = item
    readNum(purchase);  // purchase = quantity
    if(selectInventItem(type) != 0) { //check if input is bad
        if (purchase > *selectInventItem(type)) { //check if purchase is not more than inventory
            cout << "Sorry " << name.c_str() << ", we only have " << *(selectInventItem(type)) << " " << type.c_str()
                  << endl;
        }   else if (purchase > 0) { //check if purchase is 0
        *(selectInventItem(type)) -= purchase;
        *(selectInventItem(type, database[name])) += purchase;
        }
    }
}

void processSummarize() {
    cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory"; //print inventory summary
    cout <<"\nwe have had a total of " << database.size() << " different customers\n"; // print customers number
    if(findMax("Bottles") != nullptr) // check if 0
        cout << (findMax("Bottles")->name).c_str() << " has purchased the most Bottles (" << (findMax("Bottles")->bottles) << ")\n"; //print max
    else
        cout << "no one has purchased any Bottles\n";
	if(findMax("Diapers") != nullptr) //check if 0
		cout << (findMax("Diapers")->name).c_str() << " has purchased the most Diapers (" << (findMax("Diapers")->diapers) << ")\n";
	else
		cout << "no one has purchased any Diapers\n";
	if(findMax("Rattles") != nullptr) //check if 0
	    cout << (findMax("Rattles")->name).c_str() << " has purchased the most Rattles (" << (findMax("Rattles")->rattles) << ")\n";
	else
		cout << "no one has purchased any Rattles\n";
}

void processInventory() {
    String input; // type to modify
    int num; // number to add
    readString(input);
    readNum(num);
    if(num>0 && selectInventItem(input) != 0) { // checks to make sure valid input and num >0
        *(selectInventItem(input)) += num;
    }
}
