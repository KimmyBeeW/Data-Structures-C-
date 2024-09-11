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
            if (!node->left && !node->right) {  //node to delete has no children
                if (root == node) {
                    delete node;
                    node = nullptr;
                    root = nullptr;
                } else {
                    delete node;
                    node = nullptr;
                }
            } else if (!node->left || !node->right){ //node to delete has one child
                Node* temp;
                if (!node->left) {
                    temp = node->right;
                } else { // if (!node->right)
                    temp = node->left;
                }
                if (root == node){
                    delete node;
                    node = temp;
                    root = temp;
                } else {
                    delete node;
                    node = temp;
                }
            } else {  // node to delete has two children
                Node* next = getPred(node->left);
                node->value = next->value;
                subtract(node->left, next->value);
            }

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

    Node* getPred(Node*& node) {
        if (node->right == nullptr) return node;
        else return getPred(node->right);
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
