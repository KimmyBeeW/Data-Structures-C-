#pragma once
#include <algorithm>
#include <iostream>
using namespace std;

template<class T>
class AVL {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;
        int height;

        explicit Node(T v) : left(nullptr), right(nullptr), value(v), height(1) {}
    };

    AVL() : root(nullptr), treeSize(0) {
        // implement the constructor here
    }

    ~AVL() {
        clear();
    }

    const Node* getRootNode() const {
        return root;
    }

    bool insert(T item) {
        bool give = add(root, item);
        if (give) treeSize++;
        return give;
        // return true if item was inserted, false if item was already in the tree
    }

    bool remove(T item) {
        bool take = sub(root, item);
        if (take) treeSize--;
        if (treeSize < 0) { cerr << "Error: treeSize is less than 0" << endl; }
        return take;
        // return true if item was removed, false if item wasn't in the tree
    }

    bool contains(T item) const {
        return find(root, item);
        // return true if item is in the tree, false otherwise
    }

    void clear() {
        clear_helper(root);
        root = nullptr;
        treeSize = 0;
    }

    [[nodiscard]] int size() const {
        return treeSize;
        // return the number of nodes in the tree
    }
private:
    Node* root;
    int treeSize;

    void getChildHeights(const Node* node, int& lHeight, int& rHeight) const{
        lHeight = (node->left != nullptr) ? node->left->height : 0;
        rHeight = (node->right != nullptr) ? node->right->height : 0;
    }

    void updateHeight(Node*& node){
        int lHeight = 0, rHeight = 0;
        getChildHeights(node, lHeight, rHeight);
        node->height = std::max(rHeight, lHeight)+1;
    }

    void promote_left(Node*& node) {
        auto new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        updateHeight(node);
        node = new_root;
        updateHeight(node);
    }

    void promote_right(Node*& node) {
        auto new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        updateHeight(node);
        node = new_root;
        updateHeight(node);
    }

    int getBalance(Node*& node){
        int lHeight = 0, rHeight = 0;
        getChildHeights(node, lHeight, rHeight);
        return rHeight - lHeight;
    }

    void rebalance(Node*& node) {
        if (node == nullptr) return;
        updateHeight(node);  // Ensure heights are updated beforehand
        int balance = getBalance(node);
        if (balance < -1) {   // left imbalance
            if (getBalance(node->left) > 0) {
                promote_right(node->left);  // Promote left's right child
            }
            promote_left(node);
        } else if (balance > 1) {  // right imbalance
            if (getBalance(node->right) < 0) {
                promote_left(node->right);  // Promote right's left child
            }
            promote_right(node);
        }
    }

    bool add(Node*& node, T item){
        if (node == nullptr){
            node = new Node(item);
            return true;
        }
        if (node -> value == item){
            return false;
        }
        bool result;
        if (item < node->value){
            result = add(node->left, item);
        } else {
            result = add(node->right, item);
        }
        if (result) updateHeight(node);
        rebalance(node);
        return result;
    }

    bool sub(Node*& node, T item) {
        if (node == nullptr){
            return false; // item not in tree
        }
        bool result;
        if (item < node->value){
            result = sub(node->left, item);
        } else if (item > node->value){
            result = sub(node->right, item);
        } else{ // correct node found. If node is a leaf, get rid of it, else replace node and rebalance the tree
            if (node->left == nullptr && node->right == nullptr) {  //node is a leaf
                delete node;
                node = nullptr;
                rebalance(node);
                return true;
            } else if (node->left == nullptr) {  //node has only right child
                Node* temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {  //node has only left child
                Node* temp = node;
                node = node->left;
                delete temp;
            } else { //node has two children
                Node* successor = getMin(node->right);
                node->value = successor->value;
                sub(node->right, successor->value);
            }
            // Node has been successfully removed
            result = true;
        }
        if (result) updateHeight(node);
        rebalance(node);
        return result;
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
