#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
class BST {
public:
    struct Node {   //The Node struct with members left , right , and value is provided for you.
        Node* left;
        Node* right;
        T value;

        explicit Node(T v) : left(nullptr), right(nullptr), value(v){}
    };

    BST() : root(nullptr), treeSize(0) {}   // Should properly allocate an empty tree.

    ~BST() {   // Should properly clear the tree.
        clear();
    }

    const Node* getRootNode() const {   // Returns the root of the tree (set to nullptr for an empty tree).
        return root;
    }

    bool insert(T item) {   //Inserts a new node with the given value. Returns true if insertion is successful, false if the item already exists in the tree.
        return add(root, item);
    }

    bool remove(T item) {   //Removes a node containing the given value. Returns true if removal is successful, false if the item does not exist in the tree.
        return subtract(root, item);
    }

    bool contains(T item) const {   //Returns true if the item is found in the tree, false otherwise.
        return find(root, item);
    }

    void clear() {   //Removes all nodes from the tree.
        clear_helper(root);
        root = nullptr;
        treeSize = 0;
    }

    [[nodiscard]] int size() const {   //Returns the number of nodes in the tree.
        return treeSize;
    }
private:
    Node* root;
    int treeSize;

    void rebalance(Node*& node){
        int balance = getBalance(node);
        if (balance < -1){   // left imbalance
            rebalanceNegative(node);
        } else if (balance > 1) {  // right imbalance
            rebalancePositive(node);
        }
    }

    void promoteLeftChild(Node*& node) {
        auto new_root = node->left;
        node->left = node->left->right;
        new_root->right = node;
        node = new_root;
    }

    void promoteRightChild(Node*& node) {
        auto new_root = node->right;
        node->right = node->right->left;
        new_root->left = node;
        node = new_root;
    }

    void rebalanceNegative(Node*& node) {
        if (getBalance(node->left) > 0) {
            promoteRightChild(node->left);  // Promote left's right child
        }
        promoteLeftChild(node);  // Now rotate left
    }

    void rebalancePositive(Node*& node) {
        if (getBalance(node->right) < 0) {
            promoteLeftChild(node->right);  // Promote right's left child
        }
        promoteRightChild(node);  // Now rotate right
    }


    bool add(Node*& node, T item){
        if (node == nullptr){   // found the place where it's supposed to be
            node = new Node(item);  // create new node with item
            treeSize++;   // update tree size
            return true;   // insert completed successfully
        } else if (node -> value == item){
            return false;  // item already in tree, insert failed
        } else if (item < node->value) {
            return add(node->left, item); // look left
        } else {
            return add(node->right, item);  // look right
        }
    }

    bool subtract(Node*& node, T& item){
        if (node == nullptr){ // item not in tree
            return false;  // removal failed
        } else if (node->value == item){  // found the node to delete
            Node* toDelete = node;
            if (!node->left && !node->right) {
                node = nullptr;
            } else if (!node->left) {
                node = node->right;
            } else if (!node->right) {
                node = node->left;
            } else {
                Node* successor = getMin(node->right);
                node->value = successor->value;
                subtract(node->right, successor->value);
            }
            delete toDelete;

            treeSize--;  // update tree size
            return true; // removal successful
        } else if (item < node->value){
            return subtract(node->left, item); // look left
        } else if (item > node->value){
            return subtract(node->right, item); // look right
        } else {
            cerr << "Error: Something went wrong with subtract." << endl;
            return false;
        }
    }

    Node* getMin(Node* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    bool find(Node* base, const T item) const {
        if (base == nullptr){
            return false; // Not in tree
        }else if (item < base->value){
            return find(base->left, item); // Look left
        }else if (item > base->value){
            return find(base->right, item); // Look right
        }else{ // Only reaches this if item == node->data
            return true; // We found the node with the value!
        }
    }

    void clear_helper(Node* node) {
        if (node != nullptr) {
            clear_helper(node->left);
            clear_helper(node->right);
            delete node;
        }
    }
};
