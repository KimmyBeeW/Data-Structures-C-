#pragma once
#include <iostream>
#include <list>
using std::list;
#include <functional>
#include <algorithm>
#include <ostream>
#include <sstream>
using std::pair;

const int INITIAL_CAPACITY = 3;
const double MAX_LOAD = 2;

template<class K, class V>
class HashMap {   // NOT FINISHED, do not use
public:
    HashMap() : n_size(0), n_capacity(INITIAL_CAPACITY), n_data(new list<pair<K,V>>[INITIAL_CAPACITY]) {}

    ~HashMap() {
        clear();
    }

    bool insert(K item) { // return true if item was inserted, false if item was already in the set
        double loadFactor = static_cast<double>(n_size)/n_capacity;
        // std::cout << "Inserting " << item << ". Current load factor = " << loadFactor << std::endl;
        if (loadFactor > MAX_LOAD){
            // std::cout << "Calling grow() with load factor = " << loadFactor << std::endl;
            grow();
        }

        int index = getIndex(item);
        // auto & bucket = n_data[index];
        if (std::find(n_data[index].begin(), n_data[index].end(), item) != n_data[index].end()){
            return false; // we found it
        } else {
            n_data[index].push_front(item);
            n_size++;
            return true;
        }

    }

    bool remove(K item) {   // return true if item was removed, false if item wasn't in the set
        if (contains(item)){   // found
            int index = getIndex(item);
            n_data[index].remove(item);
            n_size--;
            return true;
        } else {   // not found
            return false;
        }
    }

    bool contains(K item) const {   // return true if item is in the set, false otherwise
        int index = getIndex(item);
        if (std::find(n_data[index].begin(), n_data[index].end(), item) != n_data[index].end()){
            return true; // we found it
        } else {   // not there
            return false;
        }
    }

    void clear() {   // remove all elements from the set
        delete [] n_data;
        n_size = 0;
        n_data = new list<K>[INITIAL_CAPACITY];
        n_capacity = INITIAL_CAPACITY;
    }

    [[nodiscard]] int size() const {   // return the number of elements in the set
        return n_size;
    }

    std::string toString(){
        std::ostringstream os;
        for (int i=0; i < n_capacity; i++){
            std::cout << "bucket " << i << ": ";
            for(auto const & item: n_data[i]){
                std::cout << " " << item;
            }
            std::cout << std::endl;
        }
        return os.str();
    }

private:
    int n_size;
    int n_capacity;
    list<pair<K,V>>* n_data;

    int getIndex(K const& item) const{
        return std::hash<K>{}(item) % n_capacity;  // hashcode % capacity = index
    }

    void grow(){
        list<K>* oldArray = n_data;
        n_data = new list<K>[n_capacity*2];
        n_capacity *= 2;
        n_size = 0;
        for (int i=0; i < n_capacity/2; i++){
            for(auto const & item: oldArray[i]){
                insert(item);
            }
        }
        delete [] oldArray;
    }
};
