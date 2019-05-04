//
// Created by viraj on 5/3/2019.
//
#include <vector>
#include "Expressions.cpp"
using namespace std;

void run(vector<Expressions>& input,Binary_ST* symbols){
    while(!input.empty()){
        auto current = input[0];
        if(current.cmd == "text"){
            cout<<current.text<<flush;
            input.erase(input.begin());
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
            input.erase(input.begin());
        }
        else if(current.cmd == "var"){
            if(current.error){
                cout<<"\nvariable "<<current.variable<<" incorrectly re-initialized"<<endl;
            }
            input.erase(input.begin());
        }
        else if(current.cmd == ""){
            input.erase(input.begin());
        }
    }
}
