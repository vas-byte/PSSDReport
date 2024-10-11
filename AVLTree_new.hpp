#ifndef AVLTREE_NEW
#define AVLTREE_NEW

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Note this change is to prevent conflicts with the old AVLTree class
class NodeNew{
    public:
    int val;
    int height;
    NodeNew* left;
    NodeNew* right;

    NodeNew(int val){
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};  

// Change 5: Separate AVLTreeNew class
// Reason: Single Responsibility Principle
// The AVLTreeNew class is responsible for both the AVL tree operations
// and parsing the input string. This violates the Single Responsibility Principle.
// The AVLTreeNew class should only be responsible for the AVL tree operations.
// The parsing of the input string should be handled by a separate class.
// This will make the code more modular and easier to maintain.
// AVLTreeNew class will be renamed to AVLTreeOperations
// AVLTreeOperations class will be static and will only contain the AVL tree operations
// AVLTreeOperations will also return the node after each operation 
// AVLTreeParser class will be created to handle the parsing of the input string
class AVLTreeOperations{

    private:

    // Change 4: Remove redundant code by creating a function to calculate height
    static int get_height(NodeNew* node){
       return (node == nullptr) ? 0 : node->height;
    }

    // Change 4: Remove redundant code by creating a function to calculate balance factor
    static int get_balance_factor(NodeNew* node){
        return (node == nullptr) ? 0 : get_height(node->left) - get_height(node->right);
    }

    static NodeNew* minValueNode(NodeNew* node) {
        
        NodeNew* current = node;

        // loop down to find the rightmost leaf
        while (current->right != nullptr)
            current = current->right;

        return current;
    }

    static NodeNew* right_rotation(NodeNew* parent) {

        // Store the left subtree
        NodeNew* leftsubtree = parent->left;

        // Store the right child of the left subtree (T2)
        NodeNew* T2 = leftsubtree->right;

        // Perform rotation
        leftsubtree->right = parent;
        parent->left = T2;

        // Update heights (Change 4: Use get_height() function)
        parent->height = 1 + max(get_height(parent->left), get_height(parent->right));
        leftsubtree->height = 1 + max(get_height(leftsubtree->left), get_height(leftsubtree->right));

        // Update parent to point to new root (leftsubtree)
        parent = leftsubtree;

        // Return the new root (change 6)
        return parent;
    }

    static NodeNew* left_rotation(NodeNew* parent) {

        // Store the right subtree
        NodeNew* rightsubtree = parent->right;

        // Store the left child of the right subtree (T2)
        NodeNew* T2 = rightsubtree->left;

        // Perform rotation
        rightsubtree->left = parent;
        parent->right = T2;

        // Update heights (Change 4: Use get_height() function)
        parent->height = 1 + max(get_height(parent->left), get_height(parent->right));
        rightsubtree->height = 1 + max(get_height(rightsubtree->left), get_height(rightsubtree->right));

        // Update parent to point to new root (rightsubtree)
        parent = rightsubtree;


        // Return the new root (change 6)
        return parent;
    }

    public:

    static NodeNew* insert_node(NodeNew* node, int val){
        
        // Base case
        // Delete unnecessary insert() void - change 3
        if(node == nullptr){

            // Change 6: return the new root
            node = new NodeNew(val);
            return node;
        }

        // If value to be inserted is less than current node
        if(val < node->val){
            
            // If left child free, add new node
            if(node->left == nullptr){
                
                // Change 6: return the new root
                node->left = new NodeNew(val);

            } else {

                // Else traverse left child
                // Change 6: return the new root
                node->left = insert_node(node->left, val);
            }

            

        } 
        
        // If value to be inserted is more than current node
        else if (val > node->val){

             // If right child free, add new node
            if(node->right == nullptr){

                // Change 6: return the new root
                node->right = new NodeNew(val);

            } else {

                // Else traverse right side
                // Change 6: return the new root
                node->right = insert_node(node->right, val);

            }

        }

        // Equal keys not permitted
        else if(node->val == val){

            // Change 6: return the new root
            return node;
        }

        // Update height (Change 4: Use get_height() function - remove redundant code)
        node->height = 1 + max(get_height(node->left), get_height(node->right));

        // Calculate balance factor (Change 4: Use get_balance_factor() function)
        int bf = get_balance_factor(node);

        // Determine which rotation and perform it if need be
        if(bf > 1){
            
            // Right rotation
            if(val < node->left->val){
                
                // Change 6: return the new root after the rotation
                return right_rotation(node);
            } 

            // LR rotation
            else {

                // Change 6: return the new root after the rotation
                node->left = left_rotation(node->left);
                return right_rotation(node);
            }

        } 
        
        else if (bf < -1){

            // Left Rotation
            if(val > node->right->val){

                // Change 6: return the new root after the rotation
                return left_rotation(node);
            }
            
            // RL rotation
            else {

                // Change 6: return the new root after the rotation
                node->right = right_rotation(node->right);
                return left_rotation(node);
            }
        }


        // Return the unchanged node (change 6)
        return node;

    }


    static NodeNew* remove_node(NodeNew* node, int val) {
        
        // Base case
        // Delete unnecessary remove() void - change 3
        if (node == nullptr) {
            return node;
        }

        // If value to be removed is smaller, go to the left subtree
        if (val < node->val) {

            // Change 6: return the new root
            node->left = remove_node(node->left, val);

        }
        // If value to be removed is larger, go to the right subtree
        else if (val > node->val) {

            // Change 6: return the new root
            node->right = remove_node(node->right, val);

        }

        // NodeNew to be deleted is found
        else {

            // If node has one or no children
            if (node->left == nullptr || node->right == nullptr) {
                NodeNew *temp = node->left ? node->left : node->right;
                
                // No child case
                if (temp == nullptr) {
                    delete node;
                    node = nullptr;
                } 

                // One child case
                else {

                    // delete the node first
                    delete node;

                    // assign temp (one of the children) to node  
                    node = temp;  
                }
            } 

            // NodeNew with two children
            else {
                
                // Find the inorder successor (largest in left subtree)
                NodeNew* temp = minValueNode(node->left);

                // Copy the inorder successor's data to this node
                node->val = temp->val;
                
                // Delete the inorder successor
                // Change 6: return the new root
                node->left = remove_node(node->left, temp->val);
            }

        }

        // If the tree had only one node, return
        if (node == nullptr) {

            // Change 6: return the new root
            return node;
        }

        // Update height of current node (Change 4: Use get_height() function)
        node->height = 1 + max(get_height(node->left), get_height(node->right));

        // Calculate balance factor (Change 4: Use get_balance_factor() function)
        int bf = get_balance_factor(node);

        // Left-heavy case
        if (bf > 1) {

            // Change 4: Remove redundant code by creating a function to calculate balance factor
            if (get_balance_factor(node->left) >= 0) {

                // Change 6: return the new root after the rotation
                return right_rotation(node);
            } else {

                // Change 6: return the new root after the rotation
                node->left = left_rotation(node->left);
                return right_rotation(node);
            }
        } 

        // Right-heavy case
        else if (bf < -1) {

            // Change 4: Remove redundant code by creating a function to calculate balance factor
            if (get_balance_factor(node->right) <= 0) {

                // Change 6: return the new root after the rotation
                return left_rotation(node);

            } else {

                // Change 6: return the new root after the rotation
                node->right = right_rotation(node->right);
                return left_rotation(node);
            }
        }

        // Return the unchanged node (change 6)
        return node;
    }

    static string preorder(NodeNew* node){

        if(node == nullptr){
            return "";
        }

        string result = to_string(node->val) + " ";
        result += preorder(node->left);
        result += preorder(node->right);

        return result;
    }

    static string postorder(NodeNew* node){

        if(node == nullptr){
            return "";
        }

        string result = "";

        result += postorder(node->left);
        result += postorder(node->right);
        result += to_string(node->val) + " ";

        return result;
    }

    static string inorder(NodeNew* node){

        if(node == nullptr){
            return "";
        }

        string result = "";

        result += inorder(node->left);
        result += to_string(node->val) + " ";
        result += inorder(node->right);

        return result;
    }

    
};

// Change 5: Separate AVLTreeParser class
class AVLTreeParser{
    private:
    NodeNew *root;

    public:

    AVLTreeParser(){
        root = nullptr;
    }

    string processInput(string input){
    
    // Change 1: removal of rundundant code when encountering 'A' or 'D'
    // Parse input to build tree
    for (int i = 0; i < input.length(); i++) {

        if (input[i] == 'A' || input[i] == 'D') {
            
            char operation = input[i];

            // Move to the next character to find the number
            i++;  

            string num;
            while (i < input.length() && input[i] != ' ') {
                num.push_back(input[i]);
                i++;
            }

            // Convert string to integer
            int val = stoi(num);  

            if (operation == 'A') {

                // Change 3: Call insert_node() instead of insert()
                root = AVLTreeOperations::insert_node(root, val);

            } else if (operation == 'D') {

                // Change 3: Call remove_node() instead of remove()
                root = AVLTreeOperations::remove_node(root,val);

            }
        }
    }

    // Change 2: check if root is null before traversing the tree
    // Saves on redundant checks in the traversal functions
    if(root == nullptr){
        return "EMPTY";
    }

    //Used to determine which tree traversal
    char d = input[input.length() - 1];

    //Pre-order traversal
    if(d == 'E'){
        return AVLTreeOperations::preorder(root);
    }

    //Post-order traversal
    if(d == 'T'){
        return AVLTreeOperations::postorder(root);
    }

    //In-order traversal
    if(d == 'N'){
        return AVLTreeOperations::inorder(root);
    }

    return "INVALID";
}


};

#endif