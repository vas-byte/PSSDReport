#ifndef AVLTREE_OLD
#define AVLTREE_OLD

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Node{
    public:
    int val;
    int height;
    Node* left;
    Node* right;

    Node(int val){
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};  

class AVLTree{

    private:    

    void right_rotation(Node*& parent) {

        // Store the left subtree
        Node* leftsubtree = parent->left;

        // Store the right child of the left subtree (T2)
        Node* T2 = leftsubtree->right;

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


    void left_rotation(Node*& parent) {

        // Store the right subtree
        Node* rightsubtree = parent->right;

        // Store the left child of the right subtree (T2)
        Node* T2 = rightsubtree->left;

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

    void insert_node(Node*& node, int val){

        // If value to be inserted is less than current node
        if(val < node->val){
            
            // If left child free, add new node
            if(node->left == nullptr){

                node->left = new Node(val);

            } else {

                // Else traverse left child
                insert_node(node->left, val);
            }

            

        } 
        
        // If value to be inserted is more than current node
        else if (val > node->val){

             // If right child free, add new node
            if(node->right == nullptr){
                node->right = new Node(val);
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

    Node * minValueNode(Node*& node) {
        Node* current = node;

        // loop down to find the rightmost leaf
        while (current->right != nullptr)
            current = current->right;

        return current;
    }


    void removeNode(Node*& node, int val) {

        if (node == nullptr) {
            return;
        }

        // If value to be removed is smaller, go to the left subtree
        if (val < node->val) {
            removeNode(node->left, val);
        }
        // If value to be removed is larger, go to the right subtree
        else if (val > node->val) {
            removeNode(node->right, val);
        }
        // Node to be deleted is found
        else {
            // If node has one or no children
            if (node->left == nullptr || node->right == nullptr) {
                Node *temp = node->left ? node->left : node->right;
                
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
            // Node with two children
            else {
                // Find the inorder successor (largest in left subtree)
                Node* temp = minValueNode(node->left);
                
                // Copy the inorder successor's data to this node
                node->val = temp->val;
                
                // Delete the inorder successor
                removeNode(node->left, temp->val);
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

    Node* root;

    void insert(int val){
        if(root == nullptr){
            this->root = new Node(val);
        } else {
            insert_node(root,val);
        }

        return;
    }

    void remove(int val){

        if(root ==  nullptr){
            return;
        }

        removeNode(root, val);
    }

    string preorder(Node* node){

        if(root == nullptr){
            return "EMPTY";
        }

        if(node == nullptr){
            return "";
        }

        string result = to_string(node->val) + " ";

        result += preorder(node->left);
        result += preorder(node->right);

        return result;
    }

    string postorder(Node* node){

        if(root == nullptr){
            return "EMPTY";
        }

        if(node == nullptr){
            return "";
        }

        string result = "";

        result += postorder(node->left);
        result += postorder(node->right);
    
        result += to_string(node->val) + " ";

        return result;
    }

    string inorder(Node* node){

        if(root == nullptr){
            return "EMPTY";
        }

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

    AVLTree(){
        root = nullptr;
    }

    string processInput(string input){
        //Parse input to build tree
        for(int i = 0; i < input.length(); i++){

            if(input[i] == 'A'){

                string num;

                while(true){
                    i++;

                    if(input[i] != ' '){
                        num.push_back(input[i]);
                    } else {
                        break;
                    }
                }

                int val = stoi(num);
                insert(val);
            
            }

            if(input[i] == 'D'){

                string num;

                while(true){
                    i++;

                    if(input[i] != ' '){
                        num.push_back(input[i]);
                    } else {
                        break;
                    }

                }

                int val = stoi(num);
                
                remove(val);
            }
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

        return "";
    }

    
};

#endif