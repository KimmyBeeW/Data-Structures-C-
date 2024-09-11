#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
class BST {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;

        explicit Node(T v) : left(nullptr), right(nullptr), value(v) {}
    };

    BST() : root(nullptr), treeSize(0) {}

    ~BST() {
        clear();
    }

    const Node* getRootNode() const {
        return root;
    }

    bool insert(T item) {
        add(root, item);
        // return true if item was inserted, false if item was already in the tree
    }

    bool remove(T item) {
        subtract(root, item);
        // return true if item was removed, false if item wasn't in the tree
    }

    bool contains(T item) const {
        return find(root, item);
    }

    void clear() {
        clear_helper(root);
        root = nullptr;
        treeSize = 0;
    }

    [[nodiscard]] int size() const {
        return treeSize;
    }
private:
    Node* root;
    int treeSize;

    bool add(Node*& node, T& item){
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
            // implement subtract
            /* this is the part I'm stuck on.
             * need to figure this out*/

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

    bool find(Node* node, int& item) {
        if (node == nullptr){
            return false; // Not in tree
        }else if (item < node->value){
            return find(node->left, item); // Look left
        }else if (item > node->value){
            return find(node->right, item); // Look right
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
