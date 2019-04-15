#ifndef _LINKEDLIST_HPP
#define _LINKEDLIST_HPP

typedef struct node {
  struct node* next;
  double data;
} Node;

class LinkedList {
private:
  Node* root;
  int length;

  void destroy(Node* current);
  void copy_nodes(Node* dest, Node* src);
  void copy(LinkedList& other);

public:
  LinkedList();
  LinkedList(double* data_ptr, int num);
  ~LinkedList();
  LinkedList(LinkedList& other);
  LinkedList& operator=(LinkedList& other);
  double operator[](int index);
  LinkedList& operator+(double data);
  void print_list();
};

#endif
