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

    void getChildHeights(const Node* node, int& lHeight, int& rHeight) const {
        lHeight = (node->left != nullptr) ? node->left->height : -1;
        rHeight = (node->right != nullptr) ? node->right->height : -1;
    }

    void updateHeight(Node*& node) {
        if (node == nullptr) return;
        int lHeight = (node->left != nullptr) ? node->left->height : -1;
        int rHeight = (node->right != nullptr) ? node->right->height : -1;
        node->height = std::max(lHeight, rHeight) + 1;
        // std::cout << "UpdateHeight: Node " << node->value << " Height " << node->height << "\n";
    }

    void promote_left(Node*& node) {
        Node* new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        updateHeight(node);
        updateHeight(new_root);
        node = new_root;
        // std::cout << "Promote Left: New Root: " << node->value << "\n";
    }

    void promote_right(Node*& node) {
        Node* new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        updateHeight(node);
        updateHeight(new_root);
        node = new_root;
        // std::cout << "Promote Right: New Root: " << node->value << "\n";
    }

    int getBalance(Node*& node) {
        if (node == nullptr) return 0;
        int lHeight = (node->left != nullptr) ? node->left->height : -1;
        int rHeight = (node->right != nullptr) ? node->right->height : -1;
        return rHeight - lHeight;
    }

    void rebalance(Node*& node) {
        if (node == nullptr) return;
        updateHeight(node);
        int balance = getBalance(node);
        // std::cout << "Rebalance: Node " << node->value << " Balance " << balance << "\n";
        if (balance < -1) {   // Left imbalance
            if (getBalance(node->left) > 0) {
                promote_right(node->left);  // Promote left's right child
            }
            promote_left(node);
        } else if (balance > 1) {  // Right imbalance
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
        if (node == nullptr) {
            return false; // Item not in tree
        }

        bool result = false;
        if (item < node->value) {
            result = sub(node->left, item);
        } else if (item > node->value) {
            result = sub(node->right, item);
        } else {
            // Node found, process deletion
            if (node->left == nullptr || node->right == nullptr) { // Node with zero or one child
                Node* temp = (node->left) ? node->left : node->right;
                if (temp == nullptr) { // No children
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp; // Copy child to node
                }
                delete temp;
                result = true;
            } else {
                // Node with two children
                Node* successor = getMin(node->right);
                node->value = successor->value; // Copy successor's value to node
                result = sub(node->right, successor->value); // Remove successor
            }
        }

        // If the tree had only one node then return
        if (!node)
            return true;

        // Update height of the current node
        updateHeight(node);

        // Get the balance factor of this node
        int balance = getBalance(node);

        // Balance the tree
        if (balance > 1 && getBalance(node->right) >= 0) {
            promote_right(node);
        }
        if (balance > 1 && getBalance(node->right) < 0) {
            promote_left(node->right);
            promote_right(node);
        }
        if (balance < -1 && getBalance(node->left) <= 0) {
            promote_left(node);
        }
        if (balance < -1 && getBalance(node->left) > 0) {
            promote_right(node->left);
            promote_left(node);
        }

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
