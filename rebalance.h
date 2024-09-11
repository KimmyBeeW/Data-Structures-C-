#pragma once
#include <algorithm>

struct Node {
    Node* left;
    Node* right;
    int value;
    int height;

    Node(int v) : left(nullptr), right(nullptr), value(v), height(1) {}
};

// Hint: you might find it helpful to write an update_height function that takes
// a Node* and updates its height field based on the heights of its children

void getChildHeights(Node*& node, int& lHeight, int& rHeight){
    if (node != nullptr) {
        lHeight = (node->left != nullptr) ? node->left->height : 0;
        rHeight = (node->right != nullptr) ? node->right->height : 0;
    } else {
        lHeight = 0;
        rHeight = 0;
    }
}

void updateHeight(Node*& node){
    int lHeight = 0, rHeight = 0;
    getChildHeights(node, lHeight, rHeight);
    node->height = std::max(rHeight, lHeight)+1;
}

void promote_left(Node*& root) {
    auto new_root = root->left;
    root->left = root->left->right;
    new_root->right = root;
    root = new_root;
    updateHeight(root->right);
    updateHeight(root);
}

void promote_right(Node*& root) {
    auto new_root = root->right;
    root->right = root->right->left;
    new_root->left = root;
    root = new_root;
    updateHeight(root->left);
    updateHeight(root);
}

int getBalance(Node*& node){
    int lHeight = 0, rHeight = 0;
    getChildHeights(node, lHeight, rHeight);
    return rHeight - lHeight;
}

void rebalance(Node*& root) {
    int balance = getBalance(root);
    if (balance < -1){   // left imbalance
        if (getBalance(root->left) > 0) {
            promote_right(root->left);  // Promote left's right child
        }
        promote_left(root);
    } else if (balance > 1) {  // right imbalance
        if (getBalance(root->right) < 0) {
            promote_left(root->right);  // Promote right's left child
        }
        promote_right(root);
    }
}
