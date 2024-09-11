#pragma once
#include <iostream>

template<class T>
class BST {
public:
    struct Node {   //The Node struct with members left , right , and value is provided for you.
        Node* left;
        Node* right;
        T value;

        Node(T v) : left(nullptr), right(nullptr), value(v) {}
    };

    BST() : root(nullptr), treeSize(0) {}   // Should properly allocate an empty tree.

    ~BST() {   // Should properly clear the tree.
        clear();
    }

    const Node* getRootNode() const {   // Returns the root of the tree (set to nullptr for an empty tree).
        return root;
    }

    bool insert(T item) {   //Inserts a new node with the given value. Returns true if insertion is successful, false if the item already exists in the tree.
        Node** target = search(item);  // current is a pointer to the root pointer so *current is the root pointer itself.
        if (*target != nullptr){
            return false; // item already exists in the tree, insertion failed.
        }
        *target = new Node(item);
        ++treeSize;   // increase node number by 1
        return true;  // insertion was successful
    }

    bool remove(T item) {   //Removes a node containing the given value. Returns true if removal is successful, false if the item does not exist in the tree.
        Node** target = search(item);  // current is a pointer to the root pointer so *current is the root pointer itself.
        if (*target == nullptr) {
            return false;   // item wasn't in tree, or search unsuccessful
        } else {  // found the right node, need to update everything underneath it
            Node* nodeToDelete = *target;
            if (nodeToDelete->left == nullptr) {
                *target = nodeToDelete->right;
            } else if (nodeToDelete->right == nullptr) {
                *target = nodeToDelete->left;
            } else {   // Find the minimum node in the right subtree
                Node** next = &nodeToDelete->right;
                while ((*next)->left != nullptr) {
                    next = &(*next)->left;
                }
                nodeToDelete->value = (*next)->value;
                Node* successorNode = *next;
                *next = (*next)->right;
                delete successorNode;
            }
            delete nodeToDelete;
            --treeSize;  // update tree size
            return true;  // item found and removed
        }
    }

    bool contains(T item) const {   //Returns true if the item is found in the tree, false otherwise.
        return *search(item) != nullptr; // Use search and check if result is not nullptr
    }

    void clear() {   //Removes all nodes from the tree.
        clear_helper(root);
        root = nullptr;
        treeSize = 0;
    }

    int size() const {   //Returns the number of nodes in the tree.
        return treeSize;
    }
private:
    Node* root;
    int treeSize;

    Node** search(T item) const {
        Node** current = const_cast<Node**>(&root);
        while (*current != nullptr) {
            if (item < (*current)->value) {  //check left
                current = &(*current)->left;
            } else if (item > (*current)->value) {  //check right
                current = &(*current)->right;
            } else {
                return current;   //item found
            }
        }
        return current;   //item not found or position for insert
    }

    void clear_helper(Node* node) {
        if (node != nullptr) {
            clear_helper(node->left);
            clear_helper(node->right);
            delete node;
        }
    }
};
