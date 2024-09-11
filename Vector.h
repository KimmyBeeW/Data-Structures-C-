#pragma once

#include <iostream>
#include <string>

template<class T>
class Vector {
public:
    class Iterator {   //Implement the Iterator class with
    private:   //You can keep track of the current item using a private class variable for the Iterator class.
        T* currItem;
    public:
        explicit Iterator(T* item) : currItem(item) {}

        T& operator*() {   //retrieve the value of the current item
            return *currItem;
        }

        Iterator& operator++() {   //advance to the next item
            ++currItem;
            return *this;
        }

        bool operator==(const Iterator& other) const {   //return true if the current iterator and the other iterator are equal
            return currItem == other.currItem;
        }

        bool operator!=(const Iterator& other) const {   //return the opposite of operator==()
            return currItem != other.currItem;
        }
    };
//Implement begin() and end() that return Iterator objects for the first and one past the last elements respectively
    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + vec_size);
    }

    // paste in your methods from the vector assignment
    Vector() : data(new T[2]), vec_size(0), capacity(2) {}   //The constructor for the class used for initializing private class variables

    ~Vector() {   //The destructor used to deallocate all new 'd memory
        delete[] data;
    }

    void push_back(T item) {   //Append an item to the end of the vector
        if (vec_size == capacity) { grow(); }
        data[vec_size++] = item;
    }

    void insert(T item, int position) {   //Insert an item at a given position in the vector, shifting remaining elements to the right
        if (position < 0 || position > vec_size) { throw std::out_of_range("Index out of range."); }
        if (vec_size == capacity) { grow(); }
        for (int i = vec_size; i > position; --i) {
            data[i] = data[i - 1];
        }
        data[position] = item;
        vec_size++;
    }

    void remove(int position) {   //Remove the item at the given position, shifting elements to the left. HINT: instead of trying to remove the item, think of overwriting it instead.
        if (position < 0 || position >= vec_size) { throw std::out_of_range("Index out of range."); }
        for (int i = position; i < vec_size - 1; ++i) {
            data[i] = data[i + 1];
        }
        vec_size--;
    }

    T& operator[](int index) {   //Access the item at the given index without bounds checking
        if (index < 0 || index >= vec_size) { throw std::out_of_range("Index out of range."); }
        return data[index];
    }

    [[nodiscard]] int size() const {   //Return the number of elements in the vector
        return vec_size;
    }

    void clear() {   //Clear the vector, making it empty
        vec_size = 0;
    }

    void grow() {   //automatically resize the array when necessary
        capacity *= 2;   //The capacity of the array should be doubled each time it is resized.
        T* new_data = new T[capacity];
        for (int i = 0; i < vec_size; ++i) {
            new_data[i] = data[i];   //The contents of the old array should be copied into the resized array.
        }
        delete[] data;
        data = new_data; // Update data pointer
    }

private:
    // paste in your data members from the vector assignment
    T* data;   //pointer to dynamic array
    int vec_size;   //number of elements currently present in the array
    int capacity;   //maximum possible size of the array
};
