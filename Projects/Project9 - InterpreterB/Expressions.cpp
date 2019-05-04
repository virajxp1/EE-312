//
// Created by viraj on 5/1/2019.
//

#ifndef PROJECT9___INTERPRETERB_EXPRESSIONS_H
#define PROJECT9___INTERPRETERB_EXPRESSIONS_H

#include "Parse.h"
#include <vector>
#include "DataStructure.h"

class Expressions {
public:
    string cmd;
    int num;
    string text;
    string variable;
    vector<string> expr;
    bool error;


    Expressions(){
        cmd = "";
        text = "";
        variable = "";
        num = INT32_MIN;
        error = false;
    }
    Expressions& Expression_create(Binary_ST& symbols) {
        while(next_token_type == SYMBOL){
            skip_line();
            read_next_token();
        }
        cmd = next_token();
        if(cmd == "text"){
            read_next_token();
            text = next_token();
        }
        else if(cmd == "output"){
            read_next_token();
            if(next_token_type == NUMBER){
                num = token_number_value;
            }
            else if(next_token_type == NAME){
                variable = next_token();
            }
            else if(next_token_type == SYMBOL){
                expr.push_back(next_token());
                do{
                    read_next_token();
                    expr.push_back(next_token());
                }
                while((string)peek_next_token() != "text"  && (string)peek_next_token() !="output" && (string)peek_next_token() != "var" && (string)peek_next_token() !="set"&& (string)peek_next_token() !="//"&&(string)peek_next_token() !="" );
            }
        }
        else if(cmd == "var"){
            read_next_token();
            variable = next_token();
            if(symbols.find(variable) != nullptr)
                error = true;
            else
                symbols.insert(variable,0);
            auto node = symbols.find(variable);
            read_next_token();
            if(next_token_type == NUMBER)
                symbols.change(node,token_number_value);
            else if(next_token_type == NAME){
                symbols.change(node,symbols.val(next_token()));
            }
            else if(next_token_type == SYMBOL){
                expr.push_back(next_token());
                do{
                    read_next_token();
                    expr.push_back(next_token());
                }
                while((string)peek_next_token() != "text"  && (string)peek_next_token() !="output" && (string)peek_next_token() != "var" && (string)peek_next_token() !="set"&& (string)peek_next_token() !="//"&&(string)peek_next_token() !="" );
                auto expression = new Expression_Tree(expr);
                symbols.change(node,expression->Evalulate(symbols));
                delete expression;
            }
        }
        else if(cmd == "set") {
            read_next_token();
            variable = next_token();
            if(symbols.find(variable) == nullptr){
                error = true;
                symbols.insert(variable,0);
            }
            auto node = symbols.find(variable);
            read_next_token();
            if(next_token_type == NUMBER)
                symbols.change(node,token_number_value);
            else if(next_token_type == NAME){
                symbols.change(node,symbols.val(next_token()));
            }
            else if(next_token_type == SYMBOL){
                expr.push_back(next_token());
                do{
                    read_next_token();
                    expr.push_back(next_token());
                }
                while((string)peek_next_token() != "text"  && (string)peek_next_token() !="output" && (string)peek_next_token() != "var" && (string)peek_next_token() !="set"&& (string)peek_next_token() !="//"&&(string)peek_next_token() !="" );
                auto expression = new Expression_Tree(expr);
                symbols.change(node,expression->Evalulate(symbols));
                delete expression;
            }

        }
        return *this;
    }
};


#endif //PROJECT9___INTERPRETERB_EXPRESSIONS_H
