
#ifndef PROJECT8___INTERPRETER_RUN_H
#define PROJECT8___INTERPRETER_RUN_H

#include "Parse.h"
#include "DataStructure.h"
#include <cstring>
#include <iostream>

using namespace std;

void run(){
    auto variables = new DataStructure::Binary_ST();
    while(true){
     read_next_token();
     if(next_token_type == END)
         break;
     else if(next_token_type == NAME){
        const char* cmd = next_token();
        if(strcmp(cmd,"text")==0){ //if the command is text output that text to screen
            read_next_token();
            const char* text = next_token();
            cout<<text;
        }
        else if(strcmp(cmd,"output")==0){ //if command is output
            read_next_token();
            if(next_token_type == NUMBER) //if the output is a straight number send to screen
                cout << token_number_value;
            else if(next_token_type == NAME){ //if output is a variable
                auto name = next_token();
                cout<<variables->val(name);
            }
            else if(next_token_type == SYMBOL){ //infix expression
                vector<string> expr; //vector of expression tokens
                expr.push_back(cmd);
                do{
                    read_next_token();
                    expr.push_back(next_token());
                }
                while(strcmp(peek_next_token(),"text") != 0 && strcmp(peek_next_token(),"output") != 0 && strcmp(peek_next_token(),"var") != 0 && strcmp(peek_next_token(),"set") != 0 &&strcmp(peek_next_token(),"//") != 0 &&strcmp(peek_next_token(),"") );
                auto expression = new DataStructure::Expression_Tree(expr); //creates tree
                cout<<expression->Evalulate(*variables); //outputs the evaulation of the tree
            }
        }
        else if(strcmp(cmd,"var")==0){ //if command is var -> create new variable
            read_next_token();
            auto name = next_token();
            if(variables->find(name) != nullptr){cout<<"variable "<<name<<" incorrectly re-initialized\n";}//ERROR code ->variable already exist
            else{variables->insert(name,0);}// initilize variable to 0
            auto node = variables->find(name); //pointer to the new node
            read_next_token(); //read next token to get number
            if(next_token_type == NUMBER){ //if variable is assigned to a number
                variables->change(node,token_number_value); //change the value of the
            }
            else if(next_token_type == NAME){
                variables->change(node,variables->val(name));
            }
            else if(next_token_type == SYMBOL){ // if variable is assigned to a expression
                vector<string> expr; //creates a vector which will hold the expression
                expr.push_back(cmd);
                do{
                    read_next_token();
                    expr.push_back(next_token());
                }
                while(strcmp(peek_next_token(),"text") != 0 && strcmp(peek_next_token(),"output") != 0 && strcmp(peek_next_token(),"var") != 0 && strcmp(peek_next_token(),"set") != 0 &&strcmp(peek_next_token(),"//") != 0 &&strcmp(peek_next_token(),"") );
                auto expression = new DataStructure::Expression_Tree(expr); //creates expression tree which holds the expression
                variables->change(node,expression->Evalulate(*variables)); //sets variable to the value of the expression
            }
        }
        else if(strcmp(cmd,"set")==0){ //if command is set -> change the value of existing variable
            read_next_token();
            auto name = next_token();
            if(variables->find(name) == nullptr){             //ERROR message -> variable is not in memory
                cout<<"variable "<<name<<" not declared";
                variables->insert(name,0);
            }
            auto node = variables->find(name); //pointer to the new node
            read_next_token();
            if(next_token_type == NUMBER){ //if to set var to a number
                variables->change(node,token_number_value);
            }
            else if(next_token_type == NAME){ //if to set var to another var
                variables->change(node,variables->val(name));
            }
            else if(next_token_type == SYMBOL){ //if set to an expression
                vector<string> expr;
                expr.push_back(cmd);
                do{
                    read_next_token();
                    expr.push_back(next_token());
                }
                while(strcmp(peek_next_token(),"text") != 0 && strcmp(peek_next_token(),"output") != 0 && strcmp(peek_next_token(),"var") != 0 && strcmp(peek_next_token(),"set") != 0 &&strcmp(peek_next_token(),"//") != 0 &&strcmp(peek_next_token(),"") );
                auto expression = new DataStructure::Expression_Tree(expr);
                variables->change(node,expression->Evalulate(*variables));
            }

        }
     }
     else if(next_token_type == SYMBOL){ //this will only get here if its a comment
         const char* cmd = next_token();
         if(strcmp("//",cmd) ==0)
             skip_line();
     }
    }
}

#endif //PROJECT8___INTERPRETER_RUN_H
