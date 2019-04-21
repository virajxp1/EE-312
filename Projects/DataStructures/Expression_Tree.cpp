//
// Created by viraj on 4/18/2019.
//

#include "Expression_Tree.h"
#include <string>

using namespace std;

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
    this->var = nullptr;
}

Expression_Tree :: node::node(int operand) {
    this->optr = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->is_var = false;
    this->is_operand = true;
    this->var = nullptr;
    this->operand = operand;
}

Expression_Tree :: node::node(string var) {
    this->operand = 0;
    this->is_operand = false;
    this->is_var = true;
    this-> var = var;
    this->left = nullptr;
    this->right = nullptr;
    this->optr = nullptr;
}

Expression_Tree ::Expression_Tree() {
    root = new node;
}
Expression_Tree ::Expression_Tree(string expr) {
    root = parse(expr);
}


Expression_Tree:: node* Expression_Tree::parse(string expr) {
    if(expr.size() == 0)
        return nullptr;
    string token = "";
    expr.erase(expr.begin());
    if(token == "+" || token == "-" || token == "*" || token == "/"){
        node* left = parse(expr);
        node* right = parse(expr);
        return new node(token,left,right);
    }
    else{
        bool var = false;
        for(int i = 0 ;i<token.size();i++){
            if(!isdigit(token[i])){
                var = true;
            }
        }
        if(var){
            return new node(token);
        }
        else
            return new node(stoi(token));
    }
}

int Expression_Tree::Evalulate() {
    return eval(root);
}

int Expression_Tree::eval(node* n) {
    if(n->is_operand)
        return n->operand;
    else{
        int lv = eval(n->left);
        int rv = eval(n->right);
        if(n->optr =="+")
            return lv+rv;
        else if(n->optr == "-")
            return lv-rv;
        else if(n->optr=="*")
            return lv*rv;
        else if(n->optr =="/")
            return lv/rv;
    }
}