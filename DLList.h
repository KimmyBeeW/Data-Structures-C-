//Implement appropriate error handling
//front , back , pop_front , and pop_back should throw a std::length_error if the list is empty
//insert , remove , and at should throw a std::out_of_range if the index is out of range
#pragma once

#include <iostream>
#include <string>

template<class T> //The class should be templated on the type of objects it can store.
class DLList {
public:
    /* **Important**
     * Normally you would make the Node struct PRIVATE
     * but for this assignment it is important to keep it
     * PUBLIC
     * Also, the declaration of Node needs to come
     * before everything else in the class, so leave it here
     * at the beginning. */
    struct Node {      //Implement a struct for Node , with members:
        Node* prev;    //prev (a pointer to the previous node)
        Node* next;    //next (a pointer to the next node)
        T value;       //value (the object to store in the node)

        Node(T v) : prev(nullptr), next(nullptr), value(v) {}
    };

private:
    Node* head;    // Pointer to the head node of the list
    Node* tail;    // Pointer to the tail node of the list
    int list_size; // Current size of the list

public: //Implement a class for the Double Linked List (DLList), with the following methods:
    DLList() : head(nullptr), tail(nullptr), list_size(0) {} //a default constructor that initializes an empty list

    ~DLList() {   //~DLList() : destructor that clears the dllist
        clear();
    }

    const Node* get_head() const {   //returns the head of the list
        return head;
    }

    void push_front(T item) {   //inserts a node at the front (beginning) of the list
        Node* new_node = new Node(item);
        if (head) {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        } else {
            head = tail = new_node;
        }
        list_size++;
    }
    void push_back(T item) {   //inserts a node at the back (end) of the list
        Node* new_node = new Node(item);
        if (tail) {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        } else {
            head = tail = new_node;
        }
        list_size++;
    }
    void insert(T item, int position) {   //inserts a node at the index of position
        if (position < 0 || position > list_size) { throw std::out_of_range("Index out of range.");
        } else if (position == 0) {
            push_front(item); return;
        } else if (position == list_size) {
            push_back(item); return;
        } else {
            Node* new_node = new Node(item);
            Node* current = head;
            for (int i = 0; i < position; ++i) {
                current = current->next;
            }
            new_node->next = current;
            new_node->prev = current->prev;
            current->prev->next = new_node;
            current->prev = new_node;
            list_size++;
        }
    }

    void pop_front() {   //remove a node at the front (beginning) of the list
        if (list_size==0){throw std::length_error("Can't remove an item from an empty list.");}
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        list_size--;
    }
    void pop_back() {   //remove a node at the back (end) of the list
        if (list_size==0){throw std::length_error("Can't remove an item from an empty list.");}
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        list_size--;
    }
    void remove(int position) {   //remove the node at the index of position
        if (list_size==0){throw std::length_error("Can't remove an item from an empty list.");
        } else if (position < 0 || position >= list_size) { throw std::out_of_range("Index out of range.");
        } else if (position == 0) {
            pop_front(); return;
        } else if (position == list_size-1) {
            pop_back(); return;
        } else {
            Node* current = head;
            for (int i = 0; i < position; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            list_size--;
        }
    }

    const T& front() const {   //returns the value of the node at the front of the list
        if (list_size==0){throw std::length_error("Can't return value from empty list.");}
        return head->value;
    }
    const T& back() const {   //returns the value of the node at the back of the list
        if (list_size==0){throw std::length_error("Can't return value from an empty list.");}
        return tail->value;
    }
    const T& at(int index) const {   //returns the value of the node at the given index
        if (index < 0 || index >= list_size) {
            throw std::out_of_range("Index out of range.");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    bool contains(const T& item) const {   //checks of the list contains a node with the given value ( item )
        Node* current = head;
        while (current) {
            if (current->value == item) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int size() const {   // returns the current size of the list
        return list_size;
    }

    void clear() {      // deletes every node in the list
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        list_size = 0;
    }
};
