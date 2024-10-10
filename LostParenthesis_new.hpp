#ifndef LOSTPARENTHESES_NEW
#define LOSTPARENTHESES_NEW

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LostParenthesesNew{

    private:

    // Change 3: Extract the code to update the total into a separate function
    int updateTotal(int total, string& num, string op, bool minus){

        if(op == "+" && !minus){
            total += stoi(num);
        } else {
            total -= stoi(num);
        }
        
        // Change 2: clearing the num string is common to both cases
        // so we can move it outside the if-else block
        num.clear();

        return total;
    }

    public:
    int minResult(string e) {

        bool minus = false;
        int total = 0;
        string num;
        string op = "+";

        // Change 1: Merge the two loops into one
        for(int i = 0; i < e.size(); i++){

            if(e[i] == '+' || e[i] == '-') {

                // Change 3: Update the total using a separate function
                total = updateTotal(total, num, op, minus);

                // Change 4: Update the minus flag using the op variable
                op = e[i];
                
                // Change 5: Reset the minus flag with a ternary operator not an if-else block
                minus = (op == "-") ? true : minus;

            } 
            
            else {
                num += e[i];
            }

        }

        // Change 3: Update the total using a separate function
        total = updateTotal(total, num, op, minus);

        return total;
    }


};

#endif