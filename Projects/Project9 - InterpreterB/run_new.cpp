//
// Created by viraj on 5/3/2019.
//
#include <vector>
#include "Expressions.cpp"
using namespace std;


void Parse(vector<Expressions>& parse, Binary_ST& symbols) {
    while(next_token_type != END) {
        read_next_token();
        string a = next_token();
        Expressions expr;
        parse.push_back(expr.Expression_create(symbols));
    }
}


void exec(Expressions input[],Binary_ST* symbols){
    auto current = input[0];
    if(current.cmd == "")
        return;
    if(current.cmd == "text"){
        cout<<current.text<<flush;
        exec(input+1,symbols);
    }
    else if(current.cmd == "output"){
        if(current.num != INT32_MIN)
            cout<<current.num<<flush;
        else if(current.variable != "")
            cout<<symbols->val(current.variable)<<flush;
        else {
            Expression_Tree expression(current.expr);
            cout<<expression.Evalulate(*symbols)<<flush;
        }
        exec(input+1,symbols);
    }
    else if(current.cmd == "var"){
        if(current.error){
            cout<<"\nvariable "<<current.variable<<" incorrectly re-initialized"<<endl;
        }
        auto node = symbols->find(current.variable);
        auto expression = new Expression_Tree(current.expr);
        symbols->change(node,expression->Evalulate(*symbols));
        delete expression;
        exec(input+1,symbols);
    }
    else if(current.cmd == "set"){
        if(current.error){
            cout<<"\nvariable "<<current.variable<<" not declared"<<endl;
        }
        auto node = symbols->find(current.variable);
        auto expression = new Expression_Tree(current.expr);
        symbols->change(node,expression->Evalulate(*symbols));
        delete expression;
        exec(input+1,symbols);
    }
    else if(current.cmd == "if"){
        Expression_Tree expression(current.condition);
        if(expression.Evalulate(*symbols)) {
            exec(input+1,symbols);
        }
        else{
            while(input[0].cmd != "fi" && input[0].cmd != "else"){
                input++;
            }
            exec(input+1,symbols);
        }
    }
    else if(current.cmd =="do"){
        Expression_Tree expression(current.condition);
        while(expression.Evalulate(*symbols)) {
            exec(input+1,symbols);

        }
        while(input[0].cmd != "od"){
            input++;
        }
        exec(input+1,symbols);

    }
    else if(current.cmd =="fi"){
        exec(input+1,symbols);
    }
    else if(current.cmd == "else"){
        while(input[0].cmd != "fi"){
            input++;
        }
        exec(input+1,symbols);
    }
    else if(current.cmd == "od"){
        return;
    }
}

void run(){
    vector<Expressions> parse;
    auto symbols = new Binary_ST;
    Parse(parse,*symbols);
    Expressions input[parse.size()];
    for(int i = 0;i<parse.size();i++){
        input[i] = parse[i];
    }
    exec(input,symbols);
    delete symbols;
}





