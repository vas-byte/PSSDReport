#include <iostream>
#include "LostParenthesis_old.hpp"
#include "LostParenthesis_new.hpp"
#include "AVLTree_old.hpp"
#include <string>
#include <assert.h>

using namespace std;

// Compare expected output with result
template<typename T>
void compare_output(T result, T expected, int test_num, string problem = "", string refactored = ""){

    // Compare expected output with result
    if(expected == result){

        // Test passed
        cout << problem << " " << refactored << " Test " << test_num << " Passed\n";
    } else {

        // Test failed
       cout << problem << " " << refactored << " Test " << test_num << " Failed\n";
    }

}

template<typename T>
void testLostParenthesis(T lp, bool is_refactored = false){

    string refactored = is_refactored ? " Refactored" : "Old";

    // Test 1: All positive numbers
    compare_output(lp.minResult("55+66+77+88+99"), 385, 1, "Lost Parenthesis", refactored);

    // Test 2: All negative numbers
    compare_output(lp.minResult("55-66-77-88-99"), -275, 2, "Lost Parenthesis", refactored);

    // Test 3: Mix of positive and negative numbers
    compare_output(lp.minResult("55-66+77-88+99"), -275, 3, "Lost Parenthesis", refactored);

    // Test 4: Single number
    compare_output(lp.minResult("55"), 55, 4, "Lost Parenthesis", refactored);

    // Test 5 digit number
    compare_output(lp.minResult("00009-00009"), 0, 5, "Lost Parenthesis", refactored);

    // Test 6 One minus at the start
    compare_output(lp.minResult("55-66+77+88+99"), -275, 6, "Lost Parenthesis", refactored);

    // Test 7 One minus at the end
    compare_output(lp.minResult("55+66+77+88-99"), 187, 7, "Lost Parenthesis", refactored);

    // Test 8 50 character input expression
    compare_output(lp.minResult("00009+00009+00009+00009+00009+00009+00009+0009+009"), 
                    81, 8, "Lost Parenthesis", refactored);

}

template<typename T>
void testAVLTree(T tree, bool is_refactored = false){

    string refactored = is_refactored ? " Refactored" : "Old";

    // Test 1: Insert 5 elements - Display Inorder
    compare_output(tree.processInput("A1 A2 A3 A4 A5 IN"), 
                    string("1 2 3 4 5 "), 1, "AVL Tree", refactored);

    tree.processInput("D1 D2 D3 D4 D5");

    // Test 2: Insert 5 elements and delete 1 element - Display Inorder
    compare_output(tree.processInput("A1 A2 A3 A4 A5 D3 IN"), 
                    string("1 2 4 5 "), 2, "AVL Tree", refactored);

    tree.processInput("D1 D2 D4 D5");

    // Test 3: Insert Duplicate elements
    compare_output(tree.processInput("A1 A2 A3 A4 A5 A5 A5 IN"), 
                    string("1 2 3 4 5 "), 3, "AVL Tree", refactored);

    tree.processInput("D1 D2 D3 D4 D5");

    // Test 4: Delete element not in tree
    compare_output(tree.processInput("A1 A2 A3 A4 A5 D6 IN"), 
                   string("1 2 3 4 5 "), 4, "AVL Tree", refactored);

    tree.processInput("D1 D2 D3 D4 D5");

    // Test 5: Insert 5 elements and delete 5 elements
    compare_output(tree.processInput("A1 A2 A3 A4 A5 D1 D2 D3 D4 D5 IN"), 
                   string("EMPTY"), 5, "AVL Tree", refactored);

    // Test 6: Delete duplicate elements
    compare_output(tree.processInput("A1 A2 A3 A4 A5 D5 D5 D5 IN"), 
                    string("1 2 3 4 "), 6, "AVL Tree", refactored);

    tree.processInput("D1 D2 D3 D4");

    // Test 7: Delete elements from empty tree
    compare_output(tree.processInput("D1 D2 D3 D4 D5 IN"), 
                    string("EMPTY"), 7, "AVL Tree", refactored);

    // Test 8: Insert 5 elements - Display Preorder
    compare_output(tree.processInput("A1 A2 A3 A4 A5 PRE"), 
                    string("2 1 4 3 5 "), 8, "AVL Tree", refactored);

    tree.processInput("D1 D2 D3 D4 D5");

    // Test 9: Insert 5 elements - Display Postorder
    compare_output(tree.processInput("A1 A2 A3 A4 A5 POST"), 
                    string("1 3 5 4 2 "), 9, "AVL Tree", refactored);

    tree.processInput("D1 D2 D3 D4 D5");

    // Test 10: Insert 5 elements and delete 1 element - Display Preorder
    compare_output(tree.processInput("A1 A2 A3 A4 A5 D3 PRE"), 
                    string("2 1 4 5 "), 10, "AVL Tree", refactored);

    tree.processInput("D1 D2 D3 D4");

    // Test 11: Insert 5 elements and delete 1 element - Display Postorder
    compare_output(tree.processInput("A1 A2 A3 A4 A5 D3 POST"), 
                    string("1 5 4 2 "), 11, "AVL Tree", refactored);

    tree.processInput("D1 D2 D3 D4");

    // Test 12: Large input - Inorder
    string large_input = "D13 D60 D76 D12 A17 D98 A94 D70 D3 A23 A42 D45 A100 "
        "D50 A99 A22 A87 A4 A90 D88 A71 A20 D39 D83 A97 A56 D28 A9 D43 A19 D5 " 
        "A11 A54 A73 D54 A9 A24 A58 D6 D80 A72 A47 A82 A12 A75 D77 D84 D86 A60 D64 " 
        "D70 D70 A73 A71 A40 D94 D27 A63 D47 A42 A44 A27 A100 A6 D84 A19 D65 A75 A55 " 
        "A63 A39 D99 A50 D98 A98 D100 D93 A91 A81 D59 D56 D29 D11 D45 D47 D55 D85 D7 " 
        "D70 A13 A55 A25 D35 D65 A48 D55 A45 D29 A35 A15 IN";

    string expected_output = "4 6 9 12 13 15 17 19 20 22 23 24 25 27 35 39 40 42 44 45 "
        "48 50 58 60 63 71 72 73 75 81 82 87 90 91 97 98 ";

    compare_output<string>(tree.processInput(large_input), expected_output, 12, "AVL Tree", refactored);

    string clean = "D4 D6 D9 D12 D13 D15 D17 D19 D20 D22 D23 D24 D25 D27 D35 D39 D40 D42 D44 D45 "
        "D48 D50 D58 D60 D63 D71 D72 D73 D75 D81 D82 D87 D90 D91 D97 D98 ";
    
    tree.processInput(clean);

    // Test 13: Large input - Postorder
    large_input = "A88 D77 D95 A78 A71 A2 D9 A2 A60 D80 A85 A65 D11 A30 D8 A68 D87 A28"
        " A88 A96 D29 D26 D88 D47 D68 A65 A86 A100 A61 D7 D76 D21 D24 A40 D94 A84 A16 D28" 
        " A45 A60 D34 D14 A68 A64 A74 A62 D99 D2 D34 D32 D60 D52 D19 A95 A28 A91 D24 A34" 
        " D22 D77 D7 D78 A3 A100 D95 D53 D82 D64 A55 A46 A17 A70 D4 A25 A75 D71 A30 D50" 
        " D44 A11 D39 A47 D77 A71 D1 A98 D51 A63 D15 A15 D75 A4 D14 D77 A9 D84 D70 A5 D67" 
        " A22 POST";
    
    expected_output = "3 5 4 15 11 9 22 17 28 25 16 34 40 46 55 47 63 62 61" 
        " 45 30 71 68 85 74 91 98 100 96 86 65 ";

    compare_output(tree.processInput(large_input), expected_output, 13, "AVL Tree", refactored);

    clean = "D3 D5 D4 D15 D11 D9 D22 D17 D28 D25 D16 D34 D40 D46 D55 D47 D63 D62 D61"
        " D45 D30 D71 D68 D85 D74 D91 D98 D100 D96 D86 D65 ";

    tree.processInput(clean);

    // Test 14: Large input - Preorder
    large_input = "A69 D16 A31 A98 A45 A17 A50 D17 D44 A87 D100 D73 D95 D53 D75" 
        " A30 D6 A30 A46 A42 D33 D26 D78 D56 D79 D69 A87 D75 A74 D89 D89 A43 D23" 
        " A58 D82 D74 A90 A87 D98 A75 D60 D95 D35 A38 A63 D99 A3 A12 A81 D63 A83"
        " D61 D57 D17 A65 D84 A43 D82 A92 A23 A74 D28 A11 D66 D83 D47 A88 D10 D56" 
        " D100 A100 A53 A93 A82 D52 A25 D34 A90 A43 A21 D94 D73 A29 D23 A93 A92" 
        " D92 D74 D19 D3 D56 A81 A43 D28 A72 A49 A20 D98 A97 A21 PRE";
    
    expected_output = "50 30 21 12 11 20 25 29 42 31 38 45 43 46 49 81 65 58 53" 
        " 75 72 90 87 82 88 97 93 100 ";

    compare_output(tree.processInput(large_input), expected_output, 14, "AVL Tree", refactored);

}

int main(){

    LostParenthesesOld lp_old;
    testLostParenthesis(lp_old, false);

    LostParenthesesNew lp_new;
    testLostParenthesis(lp_new, true);

    // AVLTreeOld tree_old;
    // testAVLTree(tree_old, false);
    
    return 0;
}