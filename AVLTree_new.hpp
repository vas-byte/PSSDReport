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

class AVLTreeNew{

    private:    

    NodeNew* root;

    NodeNew* minValueNode(NodeNew*& node) {
        
        NodeNew* current = node;

        // loop down to find the rightmost leaf
        while (current->right != nullptr)
            current = current->right;

        return current;
    }

    void right_rotation(NodeNew*& parent) {

        // Store the left subtree
        NodeNew* leftsubtree = parent->left;

        // Store the right child of the left subtree (T2)
        NodeNew* T2 = leftsubtree->right;

        // Perform rotation
        leftsubtree->right = parent;
        parent->left = T2;

        // Update heights
        parent->height = 1 + max((parent->left ? parent->left->height : 0), 
                                (parent->right ? parent->right->height : 0));
        
        leftsubtree->height = 1 + max((leftsubtree->left ? leftsubtree->left->height : 0), 
                                    (leftsubtree->right ? leftsubtree->right->height : 0));

        // Update parent to point to new root (leftsubtree)
        parent = leftsubtree;

    }


    void left_rotation(NodeNew*& parent) {

        // Store the right subtree
        NodeNew* rightsubtree = parent->right;

        // Store the left child of the right subtree (T2)
        NodeNew* T2 = rightsubtree->left;

        // Perform rotation
        rightsubtree->left = parent;
        parent->right = T2;

        // Update heights
        parent->height = 1 + max((parent->left ? parent->left->height : 0), 
                                (parent->right ? parent->right->height : 0));
        
        rightsubtree->height = 1 + max((rightsubtree->left ? rightsubtree->left->height : 0), 
                                    (rightsubtree->right ? rightsubtree->right->height : 0));

        // Update parent to point to new root (rightsubtree)
        parent = rightsubtree;

    }

    void insert_node(NodeNew*& node, int val){
        
        // Change 3: If root is null, create new node
        // Delete unnecessary insert() void
        if(node == nullptr){
            node = new NodeNew(val);
            return;
        }

        // If value to be inserted is less than current node
        if(val < node->val){
            
            // If left child free, add new node
            if(node->left == nullptr){

                node->left = new NodeNew(val);

            } else {

                // Else traverse left child
                insert_node(node->left, val);
            }

            

        } 
        
        // If value to be inserted is more than current node
        else if (val > node->val){

             // If right child free, add new node
            if(node->right == nullptr){
                node->right = new NodeNew(val);
            } else {

                // Else traverse right side
                insert_node(node->right, val);

            }

        }

        // Equal keys not permitted
        else if(node->val == val){
            return;
        }

        // Update height
        int left_height = 0;
        int right_height = 0;

        if(node->left == nullptr){
            left_height = 0;
        } else {
            left_height = node->left->height;
        }

        if(node->right == nullptr){
            right_height = 0;
        } else {
            right_height = node->right->height;
        }

        node->height = 1 + max(left_height,right_height);

        // Calculate balance factor
        int bf = left_height - right_height;

        // Determine which rotation and perform it if need be
        if(bf > 1){
            
            // Right rotation
            if(val < node->left->val){
                right_rotation(node);
            } 

            // LR rotation
            else {
                left_rotation(node->left);
                right_rotation(node);
            }

        } 
        
        else if (bf < -1){

            // Left Rotation
            if(val > node->right->val){
                left_rotation(node);
            }
            
            // RL rotation
            else {
                right_rotation(node->right);
                left_rotation(node);
            }
        }

        return;

    }


    void remove_node(NodeNew*& node, int val) {
        
        // Change 3: Check if root is null
        // Delete unneccssary remove() void
        if(root == nullptr){
            return;
        }

        // Base case
        if (node == nullptr) {
            return;
        }

        // If value to be removed is smaller, go to the left subtree
        if (val < node->val) {
            remove_node(node->left, val);
        }
        // If value to be removed is larger, go to the right subtree
        else if (val > node->val) {
            remove_node(node->right, val);
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
                    delete node;  // delete the node first
                    node = temp;  // assign temp (one of the children) to node
                }
            } 
            // NodeNew with two children
            else {
                
                // Find the inorder successor (largest in left subtree)
                NodeNew* temp = minValueNode(node->left);
                
                // Copy the inorder successor's data to this node
                node->val = temp->val;
                
                // Delete the inorder successor
                remove_node(node->left, temp->val);
            }
        }

        // If the tree had only one node, return
        if (node == nullptr) {
            return;
        }

        // Update height of current node
        int left_height = (node->left) ? node->left->height : 0;
        int right_height = (node->right) ? node->right->height : 0;
        node->height = 1 + max(left_height, right_height);

        // Calculate balance factor
        int bf = left_height - right_height;

        // Left-heavy case
        if (bf > 1) {

            int left_left_height = (node->left->left) ? node->left->left->height : 0;
            int left_right_height = (node->left->right) ? node->left->right->height : 0;

            if (left_left_height - left_right_height >= 0) {
                right_rotation(node);
            } else {
                left_rotation(node->left);
                right_rotation(node);
            }
        } 
        // Right-heavy case
        else if (bf < -1) {

            int right_left_height = (node->right->left) ? node->right->left->height : 0;
            int right_right_height = (node->right->right) ? node->right->right->height : 0;

            if (right_left_height - right_right_height <= 0) {
                left_rotation(node);
            } else {
                right_rotation(node->right);
                left_rotation(node);
            }
        }

        return;
    }

    string preorder(NodeNew* node){

        if(node == nullptr){
            return "";
        }

        string result = to_string(node->val) + " ";
        result += preorder(node->left);
        result += preorder(node->right);

        return result;
    }

    string postorder(NodeNew* node){

        if(node == nullptr){
            return "";
        }

        string result = "";

        result += postorder(node->left);
        result += postorder(node->right);
        result += to_string(node->val) + " ";

        return result;
    }

    string inorder(NodeNew* node){

        if(node == nullptr){
            return "";
        }

        string result = "";

        result += inorder(node->left);
        result += to_string(node->val) + " ";
        result += inorder(node->right);

        return result;
    }

    public:

    AVLTreeNew(){
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
                    insert_node(root, val);

                } else if (operation == 'D') {

                    // Change 3: Call remove_node() instead of remove()
                    remove_node(root,val);

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
            return preorder(root);
        }

        //Post-order traversal
        if(d == 'T'){
            return postorder(root);
        }

        //In-order traversal
        if(d == 'N'){
            return inorder(root);
        }

        return "INVALID";
    }

    
};

#endif