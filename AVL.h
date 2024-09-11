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
        Node* startNode = dynamic_cast<Node *>(root);
        bool take = subtract(startNode, item);
        Balance(startNode);
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

    void updateHeight(Node*& node){
        if (node == nullptr){
            cerr << "Error: cannot update height of null node" << endl;
            node->height = 0;
        }
        int lHeight = (node->left != nullptr) ? node->left->height : 0;
        int rHeight = (node->right != nullptr) ? node->right->height : 0;
        node->height = std::max(rHeight, lHeight)+1;
    }

    int getHeight (Node*& node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getImbalanceType(Node*& node) { // Cases: 1 = LL, 2 = LR, 3 = RR, 4 = RL, 0 = balanced
        int diff = getHeight(node->left) - getHeight(node->right);
        if ( abs(diff) <= 1)
            return 0;
        else {   // imbalanced
            if (diff > 1) {   // If diff positive, heavier to the left.
                if (getHeight(node->left->left) >= getHeight(node->left->right)) return 1; // LL case
                else return 2; // LR Case
            } else {   // If diff is negative, heavier to the right.
                if (getHeight(node->right->left) <= getHeight(node->right->right)) return 3; // RR Case
                else return 4; // RL Case
            }
        }
    }

    void Balance(Node*& node) {
        if (node == nullptr) return;
        int imbal = getImbalanceType(node);
        switch(imbal) {
            case 0: break;
            case 1: rightRotate(node); break; // LL
            case 2: leftRotate(node->left); rightRotate(node); break; // LR
            case 3: leftRotate(node); break; // RR
            case 4: rightRotate(node->right); leftRotate(node); break; // RL
        }
    }

    void rightRotate(Node *&parent) {
        Node *newRoot = parent->left;
        parent->left = newRoot->right;  // Give the right grandchild of the parent to become the parent's left child.
        newRoot->right = parent;        // Put the parent to the right of the newRoot
        if (parent == root)     // if the parent is root, then update root
            root = newRoot;
        parent = newRoot;       // The newRoot is now the parent.
        updateHeight(parent);
        updateHeight(parent->right);
    }

    void leftRotate(Node *&parent) {
        Node *newRoot = parent->right;
        parent->right = newRoot->left;
        newRoot->left = parent;
        if (parent == root) root = newRoot;
        parent = newRoot;
        updateHeight(parent);
        updateHeight(parent->left);
    }

    bool add(Node*& node, T item){
        if (node == nullptr){
            node = new Node(item);
            Balance(node);
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
        Balance(node);
        updateHeight(node);
        return result;
    }

    bool subtract(Node*& node, T& item) {
        if (node == nullptr){
            return false; // item not in tree
        }
        if (node->value == item) { // Time to remove!
            // Variables used check if root is equal to the node we are removing
            Node *checkRoot = dynamic_cast<Node *>(root);
            Node *checkNode = node;

            // Check for 3 cases.

            //case 1, node to delete has no children
            if (node->right == nullptr && node->left == nullptr) {
                delete node;
                node = nullptr;
                // If this is the root node, take care of it properly
                if (checkRoot == checkNode) root = nullptr;
                return true;    // I specify the true here, so it doesn't call the balance function on NULL.
            }

                // case 2, node has right child only
            else if (node->left == nullptr) {
                Node *tempNode = node->right;

                delete node;
                node = tempNode;

                // If this is the root node, take care of it properly
                if (checkRoot == checkNode) root = tempNode;
            }
                // case 2, node has left child only
            else if (node->right == nullptr) {
                Node *tempNode = node->left;
                delete node;
                node = tempNode;

                if (checkRoot == checkNode) root = tempNode;
            }

                // case 3, node has 2 children
            else if (node->right != nullptr && node->left != nullptr) {
                // Get the item to replace the node being deleted
                Node *iOP = getInorderPred(node->left);
                // set the value of the node we are deleting with its replacement
                node->value = iOP->value;
                // Delete the node that we brought in as a replacement
                subtract(node->left, iOP->value);
            } else {
                cout << "Remove: No case matched somehow" << endl;
                return false;
            }

            // Balance after removing, before returning
            Balance(node);
            updateHeight(node);

            return true;
        }

        // recursive call
        if (node->value > item) {
            bool retVal = subtract(node->left, item);

            updateHeight(node);
            Balance(node->left);
            Balance(node);
            updateHeight(node);  // Probably not needed

            return retVal;
        }
        else {
            bool retVal = subtract(node->right, item);

            updateHeight(node);
            Balance(node->right);
            Balance(node);
            updateHeight(node);  // Probably not needed

            return retVal;
        }
    }

    Node* getInorderPred(Node*& node) {
        if (node->right == nullptr) return node;
        else return getInorderPred(node->right);
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
        }else{ // Only reaches this if item == node->value
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
