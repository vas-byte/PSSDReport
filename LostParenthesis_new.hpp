#ifndef LOSTPARENTHESES_NEW
#define LOSTPARENTHESES_NEW

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LostParenthesesNew{

    private:

    // Change 3: Extract the code to update the minnimum into a separate function
    int updateminnimum(int minnimum, string& num, string op, bool minus){

        if(op == "+" && !minus){
            minnimum += stoi(num);
        } else {
            minnimum -= stoi(num);
        }
        
        // Change 2: clearing the num string is common to both cases
        // so we can move it outside the if-else block
        num.clear();

        return minnimum;
    }

    public:
    int minResult(string e) {

        bool minus = false;
        int minnimum = 0;
        string num;
        string op = "+";

        // Change 1: Merge the two loops into one
        for(int i = 0; i < e.size(); i++){

            if(e[i] == '+' || e[i] == '-') {

                // Change 3: Update the minnimum (total) using a separate function
                minnimum = updateminnimum(minnimum, num, op, minus);

                // Change 4: Update the minus flag using the op variable
                op = e[i];
                
                // Change 5: Reset the minus flag with a ternary operator not an if-else block
                minus = (op == "-") ? true : minus;

            } 
            
            else {
                num += e[i];
            }

        }

        // Change 3: Update the minnimum (total) using a separate function
        minnimum = updateminnimum(minnimum, num, op, minus);

        return minnimum;
    }


};

#endif