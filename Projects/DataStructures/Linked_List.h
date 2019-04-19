
#include <stdlib.h>
#ifndef DATASTRUCTURES_LINKED_LIST_H
#define DATASTRUCTURES_LINKED_LIST_H

/*
 * C++ Class
 * Double linked List
 */

template<class T>
class Linked_List {
    private:

    class Node{
    public:
            T val;
            Node* Next;
            Node* Prev;
            Node(T el);
    };

    Node* root;
    Node* tail;
    int size;

    public:

    void copy(Linked_List &other);
    void destroy(Linked_List &other);

    Linked_List(); //constructor Y
    Linked_List(T el); // Y
    ~Linked_List(); //destructor
    Linked_List(Linked_List &other); //copy constructor

    void insert(T el); //insert at end Y
    void insert(T el,int location); //insert at location Y
    void remove(T el); //delete specific element Y
    Linked_List& eql(Linked_List& other);
    Linked_List& operator=(Linked_List& other); //like copy constructor but to set equal too
    void operator+=(T data); //add to linked list
};

/*
 * C Linked list using 2 structs
 */


typedef struct Node{
    int val;
    Node* Next;
    Node* Prev;
}Node;

typedef struct Linkedlist {
    Node* Head;
    int size;
}Linkedlist;

Linkedlist* createListC(); //done
Linkedlist* createListC(int el);//done
void deleteListC(Linkedlist* list); //done
void insertC(Linkedlist* list,int el); //done
void insertHead(Linkedlist* list,int el); //done
bool searchList(Linkedlist* list,int el);
void printList(Linkedlist* list); //done


#endif //DATASTRUCTURES_LINKED_LIST_H
