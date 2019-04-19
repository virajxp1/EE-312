
#include "Linked_List.h"
#include <stdlib.h>
#include <iostream>


/*
 * C++ linked list implementation
 */

template <class T> Linked_List <T> ::Linked_List() { //constructor
    this->root = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template <class T> Linked_List <T> ::Linked_List(T el) {
    this->root = new Node(el);
    this->root->Prev = nullptr;
    this->root->Next = nullptr;
    this->tail = nullptr;
    this->size = 1;
}

template <class T> Linked_List <T> :: Node ::Node(T el) {
    this->val = el;
    this->Prev = nullptr;
    this->Next = nullptr;
}


template <class T> Linked_List <T> ::~Linked_List() { //destructor
    destroy(this);
}

template <class T> void Linked_List <T> ::destroy(Linked_List &other) {
    Node* current = other.root;
    if(current == nullptr)
        return;
    while(current->Next != nullptr){
        current = current->Next;
        delete current->Prev;
    }
    delete current->Prev;
}

template <class T> void Linked_List <T> ::copy(Linked_List &other) { //helper function
    this->size = other.size;
    this->root = nullptr;
    Node* old = other.root;
    Node* n = nullptr;

    while(old!= nullptr){
        Node* nn = new Node(old->val);
        if(root == nullptr) {
            root = nn;
            n = nn;
        }
        else if(old->Next == nullptr){
            tail = nn;
            nn->Next = nullptr;
            nn->Prev = n;
            n->Next = nn;
        }
        else{
            n->Next = nn;
            nn->Prev = n;
            n=n->Next;
        }
        old=old->Next;
    }
}

template <class T> Linked_List <T> :: Linked_List( Linked_List &other){ //copy constructor
    copy(other);
}

template <class T> void Linked_List <T> ::insert(T el) {
    Node* n = new Node(el);
    n->Next = nullptr;
    if(root == nullptr){
        this->root = n;
        size++;
    }
    else if(tail == nullptr){
        n->Prev = this->root;
        this->tail = n;
        this->root->Next = n;
        size++;
    }
    else{
        Node* tail = this->tail;
        tail -> Next = n;
        n->Prev = tail;
        this->tail = n;
        size++;
    }
}

template <class T> void Linked_List <T> ::insert(T el, int location) {
    if(location >= size)
        this->insert(el);
    else{
        Node* current = this->root;
        for(int i = 0;i<location;i++) {
            current = current->Next;
        }
        Node* n = new Node(el);
        n->Next = current ->Next;
        n->Prev = current;
        if(tail == current){
            tail = n;
        }
        current->Next = n;
        size++;
    }
}

template <class T> void Linked_List <T> ::remove(T el) {
    Node* current = root;
    while(current != nullptr){
        if(current->val== el){
            if(current == root){
                root = root->Next;
                root->Prev = nullptr;
                delete current;
                size--;
                break;
            }
            else if(current == tail){
                tail->Prev->Next = nullptr;
                tail = tail->Prev;
                delete current;
                size--;
                break;
            }
            else {
                current->Prev->Next = current->Next;
                current->Next->Prev = current->Prev;
                delete current;
                size--;
                break;
            }
        }
        current = current->Next;
    }
}

template <class T> Linked_List<T>& Linked_List<T> ::operator=(Linked_List &other) {
    if(&other == this)
        return *this;
    destroy(&this);
    copy(other);
}

template <class T> Linked_List<T>& Linked_List<T> ::eql(Linked_List &other) {
    if(&other == this)
        return *this;
    destroy(*this);
    copy(other);
    return *this;
}

template <class T> void Linked_List <T>::operator+=(T data) {
    insert(data);
}


/*
 * C linked list implementation
 */

Linkedlist* createListC(){
    Linkedlist* list = (Linkedlist*)(malloc(sizeof(Linkedlist)));
    list->Head = NULL;
    list->size = 0;
    return list;
}

Linkedlist* createListC(int el){
    Linkedlist* list = (Linkedlist*)(malloc(sizeof(Linkedlist)));
    Node* head = (Node*)(malloc(sizeof(Node)));
    list->Head = head;
    list->Head->val = el;
    list->Head->Next = NULL;
    list->Head->Prev = NULL;
    list->size = 1;
    return list;
}

void insertC(Linkedlist* list,int el){
    Node* n = (Node*)malloc(sizeof(Node));
    n->val = el;
    n->Next = NULL;
    Node* current = list->Head;
    if(current == NULL) {
        list->Head = n;
        list->Head->Next = NULL;
        list->Head->Prev = NULL;
        list->size++;
    }
    else{
        while(current->Next != NULL) {
            current = current->Next;
        }
        current->Next = n;
        n->Prev = current;
        list->size++;
    }
}

void insertHead(Linkedlist* list,int el){
    Node* n = (Node*)malloc(sizeof(Node));
    n->val = el;
    n->Prev = NULL;
    Node* head = list->Head;
    head->Prev = n;
    n->Next = head;
    list->Head = n;
    list->size++;
}
void deleteListC(Linkedlist* list){
    Node* current = list->Head;
    Node* next = list->Head->Next;
    for(int i = 0; i<list->size-1;i++){
        free(current);
        current = next;
        next = next->Next;
    }
    free(current);
    free(list);
}

void printList(Linkedlist* list){
    Node* current = list->Head;
    for(int i = 0;i<list->size;i++){
        std::cout << current->val << " ";
        current = current->Next;
    }
    std::cout<<std::endl;
}
bool searchList(Linkedlist* list,int el){
    Node* current = list->Head;
    for(int i = 0;i<list->size;i++){
        if(current->val == el )
            return true;
        current = current ->Next;
    }
    return false;
}




