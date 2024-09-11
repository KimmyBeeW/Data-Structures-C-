#pragma once

struct Node {
    Node* left;
    Node* right;
    int value;

    explicit Node(int v) : left(nullptr), right(nullptr), value(v) {}
};

bool find(Node* root, int item) {
    //Implement the function bool find(Node* root, int item) for searching a value in the tree
    //The function takes a pointer to the root of the subtree, and an integer item to search for
    //The function returns true if the item is found, or false otherwise
    //Assume the tree is a valid binary search tree
    // return true if item is in the subtree, false otherwise
    if (root == nullptr){
        return false; // Not in tree
    }else if (item < root->value){
        return find(root->left, item); // Look left
    }else if (item > root->value){
        return find(root->right, item); // Look right
    }else{ // Only reaches this if item == node->data
        return true; // We found the node with the value!
    }
}
