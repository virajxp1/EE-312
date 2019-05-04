//
// Created by viraj on 4/17/2019.
//
#include "Parse.h"
#include "run.h"
#include "DataStructure.h"
#include <string>
#include <iostream>
#include <vector>
#include "Expressions.cpp"

void Parse(vector<Expressions>& parse, Binary_ST& symbols) {
    while(next_token_type != END) {
        read_next_token();
        Expressions expr;
        parse.push_back(expr.Expression_create(symbols));
    }
}

int main() {
    set_input("../test1.blip");
    vector<Expressions> parse;
    auto symbols = new Binary_ST;
    Parse(parse,*symbols);
    run(parse,symbols);
    delete symbols;
}

