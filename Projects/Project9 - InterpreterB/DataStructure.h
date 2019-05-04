
#ifndef PROJECT8___INTERPRETER_DATASTRUCTURE_H
#define PROJECT8___INTERPRETER_DATASTRUCTURE_H

#include <stdlib.h>
#include <string>
#include "Parse.h"
#include <vector>
#include <iostream>

using namespace std;
class Binary_ST {
    class node{
    public:
        string name;
        int val;
        node* left;
        node* right;
        node* parent;
        node(string name,int el){
            this->val = el;
            this->name = name;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
        }
        node(const node&other){
            this->val = other.val;
            this->name = other.name;
            if(other.parent != nullptr)
                parent = new node (*(other.parent));
            else
                parent = nullptr;
            if(other.left == nullptr)
                left = nullptr;
            else
                left = new node(*(other.left));
            if(other.right == nullptr)
                right = nullptr;
            else
                right = new node(*(other.right));
            }
        ~node(){
            delete left;
            delete right;
        }
    };
    node* root;

    public:
        Binary_ST() : root(nullptr) {}
        ~Binary_ST(){
            delete root;
        }
        Binary_ST(const Binary_ST& other){
            root = new node(*(other.root));
        }
        Binary_ST& operator = (const Binary_ST& other){
            if(this == &other)
                return *this;
            delete root;
            root = new node (*(other.root));
            return *this;
        }

        Binary_ST&operator+=(string name){
            insert(name,0);
            return *this;
        }

        void insert(string name, int val);
        node* find(string name);
        void change(node* n,int val);
        int val(string name);
    };
 class Expression_Tree {
        class node {
        public:
            bool is_operand;
            bool is_var;
            int operand;
            string optr;
            string var;
            node* left;
            node* right;

            node();
            node(string token,node* left,node* right); //operator
            node(int operand);//operand and variable
            node(string var);
            ~node();
            node(const node& other);
        };
        node* root;
        node* parse(vector<string> &expr);
        int eval(node* n,Binary_ST &var);

    public:
        Expression_Tree();
        Expression_Tree(vector<string> expr);
        ~Expression_Tree();
        int Evalulate(Binary_ST &var);

    };

#endif //PROJECT8___INTERPRETER_DATASTRUCTURE_H
