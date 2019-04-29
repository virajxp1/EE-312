#include <iostream>
#include "Binary_ST.h"
#include "Binary_ST.cpp"
#include "Expression_Tree.cpp"
#include "Expression_Tree.h"

int main() {
    Binary_ST list;
    list.insert("k",6);
    list.insert("c",5);
    list.insert("y",5);
    list.insert("b",5);
    list.insert("z",5);
    list.insert("v",5);
    list.insert("f",5);
    list.insert("a",5);


    cout<<list.findmin()->name<<endl;
    list.remove("a");
    cout<<list.findmin()->name<<endl;
    list.remove("b");
    cout<<list.findmin()->name<<endl;
    list.remove("c");
    cout<<list.findmin()->name<<endl;
    list.remove("k");
    cout<<list.findmin()->name<<endl;

    Expression_Tree("* + 3 2 5");


}


