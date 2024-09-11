//Do not use any existing C++ data structures (e.g., std::list , std::vector )
#pragma once

template <class T> //Store elements of any data type using a template
class SLList {
public:
    struct Node {     //Define a struct named Node inside the SLList class with two members:
        Node* next;   //next - a pointer to the next Node in the list
        T value;      //value - an object of the data type to store the value of the node

        Node(T v) : next(nullptr), value(v) {}
    };

private:
    Node* head;    // Pointer to the head node of the list
    Node* tail;    // Pointer to the tail node of the list
    int list_size; // Current size of the list

public:
    //Provide the following member functions:
    SLList() : head(nullptr), tail(nullptr), list_size(0) {}        //a default constructor that initializes an empty list

    ~SLList() {       //a destructor that clears the list
        clear();
    }

    const Node* get_head() const {   //returns a pointer to the head node
        return head;
    }

    void push_back(T item) {       //adds a new node with the given item to the end of the list
        Node* new_node = new Node(item);
        if (tail) {
            tail->next = new_node;
        } else {
            head = new_node;
        }
        tail = new_node;
        list_size++;
    }

    void pop_back() {              //removes the last node in the list  (assume list is not empty)
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        list_size--;
    }

    const T& front() const {       //returns a const reference to the value of the head node (assume list is not empty)
        return head->value;
    }

    [[nodiscard]] int size() const {             //returns the current size of the list (i.e., the number of elements/nodes)
        return list_size;
    }

    void clear() {                 //removes all nodes from the list
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        list_size = 0;
    }
};
