//
// Created by viraj on 4/18/2019.
//

#ifndef DATASTRUCTURES_EXPRESSION_TREE_H
#define DATASTRUCTURES_EXPRESSION_TREE_H


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
    node* parse(string expr);
    int eval(node* n);

public:
    Expression_Tree();
    Expression_Tree(string expr);
    ~Expression_Tree();
    Expression_Tree(const Expression_Tree& other);
    int Evalulate();
};


#endif //DATASTRUCTURES_EXPRESSION_TREE_H
