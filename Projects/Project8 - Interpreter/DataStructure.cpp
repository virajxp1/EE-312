//
// Created by viraj on 4/18/2019.
//

#include "DataStructure.h"

using namespace std;

/*
 * Binary search tree
 */

void DataStructure:: Binary_ST ::insert(string name, int val) {
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

DataStructure::Binary_ST::node * DataStructure::Binary_ST::find(string name) {
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
void DataStructure::Binary_ST::remove(string name) {
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
DataStructure::Binary_ST:: node* DataStructure::Binary_ST::Successor(DataStructure::Binary_ST::node *n) {
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
DataStructure::Binary_ST:: node* DataStructure::Binary_ST ::findmin() {
    node *n = root;
    while (n->left != nullptr)
        n = n->left;
    return n;
}

int DataStructure::Binary_ST::val(string name) {
    return find(name)->val;
}

void DataStructure::Binary_ST::change(string name, int val) {
    node* n = find(name);
    n->val = val;
}

void DataStructure::Binary_ST::change(DataStructure::Binary_ST::node *n,int val) {
    n->val = val;
}

///////////////////////////////////////////////////////////////////////////////////

/*
 * Expression Tree implementation
 */


DataStructure::Expression_Tree::node::node() {
    is_operand = false;
    is_var = false;
    var = nullptr;
    operand = 0;
    optr = nullptr;
    left = nullptr;
    right = nullptr;
}
DataStructure::Expression_Tree::node::~node() {
    delete left;
    delete right;
}

DataStructure::Expression_Tree::node::node(const DataStructure::Expression_Tree::node &other) {
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

DataStructure::Expression_Tree :: node ::node(string token, Expression_Tree::node *left,Expression_Tree::node *right) {
    this->is_var = false;
    this->is_operand = false;
    this->operand = 0;
    this->left = left;
    this->right = right;
    this->optr = token;
    this->var = "";
}

DataStructure::Expression_Tree :: node::node(int operand) {
    this->optr = "";
    this->left = nullptr;
    this->right = nullptr;
    this->is_var = false;
    this->is_operand = true;
    this->var = "";
    this->operand = operand;
}

DataStructure::Expression_Tree :: node::node(string var) {
    this->operand = 0;
    this->is_operand = false;
    this->is_var = true;
    this-> var = var;
    this->left = nullptr;
    this->right = nullptr;
    this->optr = "";
}

DataStructure::Expression_Tree ::Expression_Tree() {
    root = new node;
}
DataStructure::Expression_Tree ::Expression_Tree(vector<string> expr) {
    root = parse(expr);
}

DataStructure::Expression_Tree::~Expression_Tree() {
    delete root;
}

DataStructure::Expression_Tree:: node* DataStructure::Expression_Tree::parse(vector<string> &expr) {
    if(expr.size() == 0)
        return nullptr;
    string token = expr[0];
    expr.erase(expr.begin());
    if(token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token =="&&" || token == "||"
        || token =="<" || token ==">" || token == "==" || token == "!=" || token == "<=" || token == ">="){
        node* left = parse(expr);
        node* right = parse(expr);
        return new node(token,left,right);
    }
    else if(token == "~" || token == "!"){
        node* left = parse(expr);
        node* right = nullptr;
        return new node(token,left,right);
    }
    else{
        if(!isdigit(token[0]))
            return new node(token);
        else
            return new node(stoi(token));
    }
}

int DataStructure::Expression_Tree::Evalulate(DataStructure::Binary_ST &var) {
    return eval(root,var);
}

int DataStructure::Expression_Tree::eval(node* n,DataStructure::Binary_ST &var) {
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
    }
}