//
// Created by viraj on 4/18/2019.
//

#include "Binary_ST.h"
using namespace std;

void Binary_ST ::insert(string name, int val) {
    if(root == nullptr){
        root = new node(name,val);
    }
    else{
        node* current = root;
        while(current->right!= nullptr && current->left != nullptr) {
            if(name>current->name)
                current = current->right;
            else
                current = current->left;
        }
        if(name>current->name){
            current->right = new node(name,val);
            current->right->parent = current;
        }
        else{
            current->left = new node(name,val);
            current->left->parent = current;
        }
    }
}

Binary_ST::node * Binary_ST::find(string name) {
    node* current = root;
    while(current != nullptr){
        if(current->name == name)
            return current;
        else{
            if(name>current->name){
                if(current->right != nullptr)
                    current= current->right;
                else
                    break;
            }
            else{
                if(current->left != nullptr)
                    current = current->left;
                else
                    break;
            }
        }
    }
    return nullptr;
}
void Binary_ST::remove(string name) {
    node* n = find(name);
    if(n == nullptr)
        return;
    node* prev = n->parent;

    if(n->left == nullptr && n->right == nullptr){ //no sub branches
        if(prev->left->name == name)
            prev->left = nullptr;
        else
            prev->right = nullptr;
        delete n;
        if(n==root)
            root = nullptr;
        return;
    }

    if(n->left != nullptr && n->right == nullptr){ //one sub branch to the left
        if(prev->left->name == name){ //parent from the left
            if(n->left != nullptr){
                prev->left = n->left;
                n->left->parent = prev;
            }
            else{
                prev->left = n->right;
                n->right->parent = prev;
            }

        }
        else { //parent from the right
            if(n->left != nullptr){
                prev->right = n->left;
                n->left->parent = prev;
            }
            else{
                prev->right = n->right;
                n->right->parent = prev;
            }

        }
        n->parent = nullptr;
        n->left = nullptr;
        n->right = nullptr;
        delete n;
        if(n == root)
            root = nullptr;
        return;
    }

    if(n->right != nullptr && n->left == nullptr){
        if(prev->left->name == name){
            if(n->left != nullptr){
                prev->left = n->left;
                n->left->parent = prev;
            }
            else{
                prev->left = n->right;
                n->right->parent = prev;
            }

        }
        else {
            if(n->left != nullptr){
                prev->right = n->left;
                n->left->parent = prev;
            }
            else{
                prev->right = n->right;
                n->right->parent = prev;
            }

        }
        if(n==root)
            root = nullptr;
        n->parent = nullptr;
        n->left = nullptr;
        n->right = nullptr;
        delete n;
        return;
    }
    // 2 sub branches
    node* next = Successor(n);
    n->name = next->name;
    n->val = next->val;
    if(next->parent->left->name == next->name)
        next->parent->left = nullptr;
    if(next->parent->right->name == next->name)
        next->parent->right = nullptr;
    delete next;
}
Binary_ST:: node* Binary_ST::Successor(Binary_ST::node *n) {
    node* current = n;
    if(n->right != nullptr){
        current = current->right;
        while(current->left != nullptr)
            current = current->left;
        return current;
    }
    else{
        while(current->parent->left->name != current->name)
            current = current->parent;
        return current;
    }
}
Binary_ST:: node* Binary_ST ::findmin() {
    node* n = root;
    while(n->left != nullptr)
        n = n->left;
    return n;
}