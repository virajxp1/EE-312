/* Your task is to complete the following methods:
   
   // destructor; must be implemented using recursion
   ~LinkedList();

   // copy constructor; must be implemented using recursion
   LinkedList(LinkedList& other);

   // assignment operator
   LinkedList& operator=(LinkedList& other);

   // operator overload
   LinkedList& operator+(double data);
  
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "linkedlist.hpp"

using namespace std;

/* Default constructor
   - creates empty linked list
 */
LinkedList::LinkedList() {
  this->root = NULL;
  this->length = 0;
}

/* Constructor with data arguments
   - creates linked list with given data in reverse order
   - end of linked list marked with NULL pointer
 */
LinkedList::LinkedList(double* data_ptr, int num) {
  this->length = num;
  this->root = NULL;
  Node* current;
  for (int i = 0; i < num; i++) {
    current = new Node;
    current->data = data_ptr[i];
    current->next = this->root;
    this->root = current;
  }
}

/* Destructor
   - YOUR TASK
   - implement using recursion
   - you may use helper functions
   - you may not use global or static variables
 */
LinkedList::~LinkedList() {

}

/* Copy constructor
   - YOUR TASK
   - implement using recursion
   - you may use helper functions
   - you may not use global or static variables
 */
LinkedList::LinkedList(LinkedList& other) {

}

/* Assignment operator
   - YOUR TASK
 */
LinkedList& LinkedList::operator=(LinkedList& other) {

}

/* Operator overload
   - overloads "[]"
   - returns data at given index
 */
double LinkedList::operator[](int index) {
  int i = 0;
  Node* current = this->root;
  while (i < index) {
    current = current->next;
    i++;
  }
  return current->data;
}

/* Operator overload
   - YOUR TASK
   - overloads "+"
   - inserts data at beginning of linked list
 */
LinkedList& LinkedList::operator+(double data) {

}

/* Prints all elements in linked list
 */
void LinkedList::print_list() {
  int i = 0;
  Node* current = this->root;
  while (i < this->length) {
    cout << current->data << " ";
    current = current->next;
    i++;
  }
  cout << endl;
}

int main() {
  double array1[] = {0.5, 1, 1.5, 2, 2.5, 3};
  double array2[] = {0.1, 0.2, 0.3, 0.4};
  LinkedList ll1(array1, 6);
  cout << "List 1: ";
  ll1.print_list();
  cout << "Fourth number in List 1: ";
  cout<< ll1[3] << endl;
  LinkedList ll2(array2, 4);
  cout << "List 2: ";
  ll2.print_list();
  LinkedList ll3;
  ll3 = ll2;
  cout << "List 3 after copying List 2: ";
  ll3.print_list();
  ll2 = ll1;
  cout << "List 2 after copying List 1: ";
  ll2.print_list();
  ll1+3.5+4;
  cout << "List 1 after inserting 4 and 3.5: ";
  ll1.print_list();
}
