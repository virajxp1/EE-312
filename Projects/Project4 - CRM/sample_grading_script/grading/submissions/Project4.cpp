// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// <Viraj Parikh>
// <Your EID>
// Slip days used: <0>
// Spring 2018

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
Customer Inventory;
String diapers;
String bottles;
String rattles;
//String name;
int reset_;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */


/* clear the Inventory and reset the customer database to empty */
void reset(void) {
	reset_ =0;
	Inventory.diapers =0;
	Inventory.bottles =0;
	Inventory.rattles =0;
	for(int i=0;i<=num_customers;i++) {
	    StringDestroy(&(customers[i].name));
	    customers[i].rattles =0;
	    customers[i].bottles =0;
	    customers[i].diapers =0;
	}
	num_customers =0;
}

//Finds the customer that bought the most of each item by doing a search if tie first occurance is returned. Returns index
int findMost(String input) {
    int index =0;
    int temp;
    if(StringIsEqualTo(&diapers,&input)) {
        temp = customers[0].diapers;
        for (int i=1;i<num_customers;i++) {
            if (customers[i].diapers > temp) {
                index = i;
                temp = customers[i].diapers;
            }
        }
        if(customers[index].diapers == 0)
            index = -1;
        return index;
    }
    if(StringIsEqualTo(&rattles,&input)) {
        temp = customers[0].rattles;
        for (int i=1;i<num_customers;i++) {
            if (customers[i].rattles > temp) {
                index = i;
                temp = customers[i].rattles;
            }
        }
        if(customers[index].rattles == 0)
            index = -1;
        return index;
    }
    if(StringIsEqualTo(&bottles,&input)) {
        temp = customers[0].bottles;
        for (int i=1;i<num_customers;i++) {
            if (customers[i].bottles > temp) {
                index = i;
                temp = customers[i].bottles;
            }
        }
        if(customers[index].bottles == 0)
            index = -1;
        return index;
    }
    return -1;
}
//Prints status of inventory and best customers
void processSummarize() {
    diapers = StringCreate("Diapers");
    bottles = StringCreate("Bottles");
    rattles = StringCreate("Rattles");
    int mostIndex1, mostIndex2,mostIndex3;

    printf("There are %d Bottles, %d Diapers and %d Rattles in inventory",Inventory.bottles,Inventory.diapers,Inventory.rattles);
    printf("\nwe have had a total of %d different customers\n",num_customers);

    mostIndex1 = findMost(bottles);//index of most buyer if -1 then no one has bought
    mostIndex2 = findMost(diapers);
    mostIndex3 = findMost(rattles);

    if(mostIndex1 != -1 ) {
        StringPrint(&customers[mostIndex1].name);
        printf(" has purchased the most Bottles (%d)\n",customers[mostIndex1].bottles);
    }
    else {
        printf("no one has purchased any Bottles\n");
    }
    if(mostIndex2 != -1 ) {
        StringPrint(&customers[mostIndex2].name);
        printf(" has purchased the most Diapers (%d)\n",customers[mostIndex2].diapers);
    }
    else {
        printf("no one has purchased any Diapers\n");
    }
    if(mostIndex3 != -1 ) {
        StringPrint(&customers[mostIndex3].name);
        printf(" has purchased the most Rattles (%d)\n",customers[mostIndex3].rattles);
    }
    else {
        printf("no one has purchased any Rattles\n");
    }

    StringDestroy(&diapers);
    StringDestroy(&bottles);
    StringDestroy(&rattles);//clearing memory
}

int isNewCustomer(String name){ //searches through the list to see if the customer is new
    int i = 0;
    while (i < num_customers) {
        if (StringIsEqualTo(&customers[i].name, &name)) {
            return i; //returs index
        }
        i++;
    }
    return -1; //if new returns -1
}

void processPurchase() {
    String name;
    String type;
    diapers = StringCreate("Diapers");
    bottles = StringCreate("Bottles");
    rattles = StringCreate("Rattles");
    int quantity; //quantity of purchase
    int index; //index of customer
    int check =0; //To see if it is a valid buy if check = -1 then not valid and is discarded
    int flagNew =0; //Sets flag for new customer to increment later implemented for if there isnt enough in inventory for first time customer not added

    readString(&name);
    readString(&type);
    readNum(&quantity);

    index = isNewCustomer(name);
    if(quantity<=0) {
        check = -1;
    }

    if (index == -1 && check == 0) {
        customers[num_customers].diapers =0;
        customers[num_customers].rattles=0;
        customers[num_customers].bottles=0;
        index = num_customers;
        flagNew =1;
    }

    if (StringIsEqualTo(&type,&diapers) && check == 0) {
        if(Inventory.diapers >= quantity) { //checks to see if the inventory has enough for the quantity of pruchase
            customers[index].diapers += quantity;
            Inventory.diapers -= quantity;
            if(flagNew == 1) {
                customers[num_customers].name = StringDup(&name); //name is added if is new customer
                num_customers++;
            }
        }
        else {
            printf("Sorry ");
            StringPrint(&name);
            printf(", we only have %d Diapers\n", Inventory.diapers);
        }
    }
    else if (StringIsEqualTo(&type,&rattles) && check == 0) {
        if (Inventory.rattles >= quantity) {
            customers[index].rattles += quantity;
            Inventory.rattles -= quantity;
            if(flagNew == 1) {
                customers[num_customers].name = StringDup(&name);
                num_customers++;
            }
        }
        else {
            printf("Sorry ");
            StringPrint(&name);
            printf(", we only have %d Rattles\n", Inventory.rattles);
        }
    }
    else if (StringIsEqualTo(&type,&bottles) && check == 0) {
        if (Inventory.bottles >= quantity) {
            customers[index].bottles += quantity;
            Inventory.bottles -= quantity;
            if(flagNew == 1) {
                customers[num_customers].name = StringDup(&name);
                num_customers++;
            }
        }
        else {
            printf("Sorry ");
            StringPrint(&name);
            printf(", we only have %d Bottles\n", Inventory.bottles);
        }
    }

    StringDestroy(&type);
    StringDestroy(&name);
    StringDestroy(&diapers);
    StringDestroy(&bottles);
    StringDestroy(&rattles);
}

//adds to inventory # of quantity
void processInventory() {
    diapers = StringCreate("Diapers");
    bottles = StringCreate("Bottles");
    rattles = StringCreate("Rattles");

    if (reset_ == 0) { //to set inventory to 0
        Inventory.diapers =0;
        Inventory.bottles =0;
        Inventory.rattles =0;
        reset_++;
    }

    String input;
    int num =0;
    readString(&input);
    readNum(&num);
    if (StringIsEqualTo(&input,&diapers)&&num>0)
        Inventory.diapers+=num;
    else if (StringIsEqualTo(&input,&rattles)&&num>0)
        Inventory.rattles+=num;
    else if (StringIsEqualTo(&input,&bottles)&&num>0)
        Inventory.bottles+=num;

    StringDestroy(&input);
    StringDestroy(&diapers);
    StringDestroy(&bottles);
    StringDestroy(&rattles);
}
