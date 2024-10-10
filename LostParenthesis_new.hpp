#ifndef LOSTPARENTHESES_NEW
#define LOSTPARENTHESES_NEW

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LostParenthesesNew{

    public:
    int minResult(string e) {

        bool minus = false;
        int total = 0;
        string num;
        char op = '+';

        // Change 1: Merge the two loops into one
        for(int i = 0; i < e.size(); i++){
            if(e[i] == '+' || e[i] == '-') {
            if(!num.empty()) {
                if(op == '+' && !minus) {
                total += stoi(num);
                } else {
                total -= stoi(num);
                }
                num.clear();
            }
            op = e[i];
            if(e[i] == '-') {
                minus = true;
            }
            } else {
            num += e[i];
            }
        }

        if(!num.empty()) {
            if(op == '+' && !minus) {
            total += stoi(num);
            } else {
            total -= stoi(num);
            }
        }

        return total;
    }

   


};

#endif