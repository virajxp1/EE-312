//
// Created by viraj on 4/18/2019.
//

#include "DataStructure.h"
#include "Parse.h"
#include <iostream>
#include <string>

using namespace std;

/*
 * Binary search tree
 */

void Binary_ST ::insert(string name, int val) {
    if(root == nullptr){
        root = new node(name,val);
    }
    else{
        node* current = root;
        node* prev = nullptr;
        while(current!= nullptr) {
            prev = current;
            if(name>current->name)
                current = current->right;
            else
                current = current->left;
        }
        if(name>prev->name){
            prev->right = new node(name,val);
            prev->right->parent = prev;
        }
        else{
            prev->left = new node(name,val);
            prev->left->parent = prev;
        }
    }
}

Binary_ST::node * Binary_ST::find(string name) {
    node* current = root;
    while(current != nullptr){
        if(current->name == name){
            return current;
        }
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

int Binary_ST::val(string n) {
    if (!n.empty() && n[n.size() - 1] == '\r')
        n.erase(n.size() - 1);
    node* current = root;
    while(current != nullptr){
        if(n == current->name){
            return current->val;
        }
        else{
            if(n>current->name){
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
    return 0;
}


void Binary_ST::change(Binary_ST::node *n,int val) {
    n->val = val;
}

///////////////////////////////////////////////////////////////////////////////////

/*
 * Expression Tree implementation
 */


Expression_Tree::node::node() {
    is_operand = false;
    is_var = false;
    var = nullptr;
    operand = 0;
    optr = nullptr;
    left = nullptr;
    right = nullptr;
}
Expression_Tree::node::~node() {
    delete left;
    delete right;
}

Expression_Tree::node::node(const Expression_Tree::node &other) {
    is_operand = other.is_operand;
    is_var = other.is_var;
    operand = other.operand;
    optr = other.optr;
    var = other.var;
    if(other.left != nullptr)
        left = new node(*(other.left));
    else
        left = nullptr;
    if(other.right != nullptr)
        right = new node(*(other.right));
    else
        right = nullptr;
}

Expression_Tree :: node ::node(string token, Expression_Tree::node *left,Expression_Tree::node *right) {
    this->is_var = false;
    this->is_operand = false;
    this->operand = 0;
    this->left = left;
    this->right = right;
    this->optr = token;
    this->var = "";
}

Expression_Tree :: node::node(int operand) {
    this->optr = "";
    this->left = nullptr;
    this->right = nullptr;
    this->is_var = false;
    this->is_operand = true;
    this->var = "";
    this->operand = operand;
}

Expression_Tree :: node::node(string var) {
    this->operand = 0;
    this->is_operand = false;
    this->is_var = true;
    this-> var = var;
    this->left = nullptr;
    this->right = nullptr;
    this->optr = "";
}

Expression_Tree ::Expression_Tree() {
    root = new node;
}
Expression_Tree ::Expression_Tree(vector<string> expr) {
    root = parse(expr);
}

Expression_Tree::~Expression_Tree() {
    delete root;
}

Expression_Tree:: node* Expression_Tree::parse(vector<string> &expr) {
    if(expr.size() == 0)
        return nullptr;
    string token = expr[0];
    expr.erase(expr.begin());
    if(token == "~" || token == "!"){
        node* left = parse(expr);
        node* right = nullptr;
        return new node(token,left,right);
    }
    else if(token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token =="&&" || token == "||"
        || token =="<" || token ==">" || token == "==" || token == "!=" || token == "<=" || token == ">="){
        node* left = parse(expr);
        node* right = parse(expr);
        return new node(token,left,right);
    }
    else{
        if(!isdigit(token[0]))
            return new node(token);
        else
            return new node(stoi(token));
    }
}

int Expression_Tree::Evalulate(Binary_ST &var) {
    return eval(root,var);
}

int Expression_Tree::eval(node* n,Binary_ST &var) {
    if(n == nullptr){return 0;}
    if (n->is_operand)
        return n->operand;
    else if(n->is_var)
        return var.val(n->var);
    else {
        int lv = eval(n->left,var);
        int rv = eval(n->right,var);
        if (n->optr == "+")
            return lv + rv;
        else if (n->optr == "-")
            return lv - rv;
        else if (n->optr == "*")
            return lv * rv;
        else if (n->optr == "/")
            return lv / rv;
        else if(n->optr == "%")
            return lv%rv;
        else if(n->optr == "&&"){
            if(lv&&rv){return 1;}
            else{return 0;}
        }
        else if(n->optr == "||"){
            if(lv||rv){return 1;}
            else{return 0;}
        }
        else if(n->optr == "<"){
            if(lv<rv){return 1;}
            else{return 0;}
        }
        else if(n->optr == ">"){
            if(lv>rv){return 1;}
            else{return 0;}
        }
        else if(n->optr == "=="){
            if(lv==rv){return 1;}
            else{return 0;}
        }
        else if(n->optr == "!="){
            if(lv!=rv){return 1;}
            else{return 0;}
        }
        else if(n->optr == "<="){
            if(lv<=rv){return 1;}
            else{return 0;}
        }
        else if(n->optr == ">="){
            if(lv>=rv){return 1;}
            else{return 0;}
        }
        else if(n->optr == "~"){
            return -1*lv;
        }
        else if(n->optr == "!"){
            if(lv ==0){
                return 1;
            }
            return 0;
    }
    return 0;
    }
}
