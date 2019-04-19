//
// Created by viraj on 4/18/2019.
//

#ifndef DATASTRUCTURES_BINARY_ST_H
#define DATASTRUCTURES_BINARY_ST_H
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
    Binary_ST(string name,int val){
        root = new node(name,val);
    }
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
        cout << "overload" << endl;
        root = new node (*(other.root));
        return *this;
    }

    Binary_ST&operator+=(string name){
        insert(name,0);
        return *this;
    }

    void insert(string name, int val);
    node* find(string name);
    void remove(string name);
    node* findmin();
    node* Successor(node* n);
};

#endif //DATASTRUCTURES_BINARY_ST_H
