
#ifndef PROJECT8___INTERPRETER_RUN_H
#define PROJECT8___INTERPRETER_RUN_H

#include "Parse.h"
#include "DataStructure.h"
#include <string>
#include <iostream>

using namespace std;
void run(){
    auto variables = new Binary_ST();
    while(true){
     read_next_token();
     if(next_token_type == END){
         break;
     }
     else if(next_token_type == NAME){
         auto c = next_token();
         string cmd(c);
        if(cmd =="text"){ //if the command is text output that text to screen
            read_next_token();
            string text = next_token();
            cout<<text<<flush;
        }
        else if(cmd == "output"){ //if command is output
            read_next_token();
            if(next_token_type == NUMBER) //if the output is a straight number send to screen
                cout << token_number_value<<flush;
            else if(next_token_type == NAME){ //if output is a variable
                auto name = next_token();
                string n(name);
                cout<<variables->val(name)<<flush;
            }
            else if(next_token_type == SYMBOL){ //infix expression
                vector<string> expr; //vector of expression tokens
                expr.push_back(next_token());
                do{
                    read_next_token();
                    expr.push_back(next_token());
                }
                while((string)peek_next_token() != "text"  && (string)peek_next_token() !="output" && (string)peek_next_token() != "var" && (string)peek_next_token() !="set"&& (string)peek_next_token() !="//"&&(string)peek_next_token() !="" );
                auto expression = new Expression_Tree(expr); //creates tree
                cout<<expression->Evalulate(*variables)<<flush; //outputs the evaulation of the tree
                delete expression;
            }
        }
        else if(cmd=="var"){ //if command is var -> create new variable
            read_next_token();
            auto name = next_token();
            string n(name);
            if(variables->find(n) != nullptr){
                cout<<"\nvariable "<<name<<" incorrectly re-initialized"<<endl;
            }
            //ERROR code ->variable already exist
            else{variables->insert(n,0);}// initilize variable to 0
            auto node = variables->find(n); //pointer to the new node
            read_next_token(); //read next token to get number
            if(next_token_type == NUMBER){ //if variable is assigned to a number
                variables->change(node,token_number_value); //change the value of the
            }
            else if(next_token_type == NAME){
                variables->change(node,variables->val(n));
            }
            else if(next_token_type == SYMBOL){ // if variable is assigned to a expression
                vector<string> expr; //creates a vector which will hold the expression
                expr.push_back(next_token());
                do{
                    read_next_token();
                    expr.push_back(next_token());
                }
                while((string)peek_next_token() != "text"  && (string)peek_next_token() !="output" && (string)peek_next_token() != "var" && (string)peek_next_token() !="set"&& (string)peek_next_token() !="//"&&(string)peek_next_token() !="" );
                auto expression = new Expression_Tree(expr); //creates expression tree which holds the expression
                variables->change(node,expression->Evalulate(*variables)); //sets variable to the value of the expression
                delete expression;
            }
        }
        else if(cmd == "set"){ //if command is set -> change the value of existing variable
            read_next_token();
            auto name = next_token();
            string n(name);
            if(variables->find(n) == nullptr){             //ERROR message -> variable is not in memory
                cout<<"\nvariable "<<name<<" not declared"<<endl;
                variables->insert(n,0);
            }
            auto node = variables->find(n); //pointer to the new node
            read_next_token();
            if(next_token_type == NUMBER){ //if to set var to a number
                variables->change(node,token_number_value);
            }
            else if(next_token_type == NAME){ //if to set var to another var
                variables->change(node,variables->val(n));
            }
            else if(next_token_type == SYMBOL){ //if set to an expression
                vector<string> expr;
                expr.push_back(next_token());
                do{
                    read_next_token();
                    expr.push_back(next_token());
                }
                while((string)peek_next_token() != "text"  && (string)peek_next_token() !="output" && (string)peek_next_token() != "var" && (string)peek_next_token() !="set"&& (string)peek_next_token() !="//"&&(string)peek_next_token() !="" );
                auto expression = new Expression_Tree(expr);
                variables->change(node,expression->Evalulate(*variables));
                delete expression;
            }

        }
     }
     else if(next_token_type == SYMBOL){ //this will only get here if its a comment
         string cmd = next_token();
         if("//" == cmd)
             skip_line();
     }
    }
    delete variables;
}

#endif //PROJECT8___INTERPRETER_RUN_H
