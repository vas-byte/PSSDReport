#ifndef LOSTPARENTHESES_OLD
#define LOSTPARENTHESES_OLD

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LostParenthesesOld{

    public:
    int minResult(string e) {

        bool minus = false;
        int total = 0;
        string num;
        int pos = 0;

        for(int i = 0; i < e.size(); i++){

            if(e[i] == '-'){
                minus = true;
                pos = i;
                break;
            }

            if(e[i] == '+'){
                pos = i;
                break;
            }

            num += e[i];
            pos = i;
        }

        total = stoi(num);

        if(pos == e.size() - 1){
            return total;
        }

        num.clear();
        char op;

        for(int i = pos; i < e.size(); i++){
            
            if((e[i] == '+' || e[i] == '-') && num.empty()){
                op = e[i];
                continue;
            }

            if((e[i] == '+' || e[i] == '-') && !num.empty()){

                if(op == '+' && !minus){
                    total += stoi(num);
                    num.clear();
                    op = e[i];
                } else {
                    minus = true;
                    total -= stoi(num);
                    num.clear();
                    op = e[i];
                }

            } else {
                num += e[i];
            }

        }

        if(op == '+' && !minus){
            total += stoi(num);
        } else {
            total -= stoi(num);
        }


        return total;
    }

   


};

#endif