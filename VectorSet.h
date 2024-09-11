#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using std::vector, std::find, std::cout, std::endl;

template<class T>
class VectorSet {
    std::vector<T> items;
public:
    bool contains(T item) const {
        auto it = find(items.begin(), items.end(), item);
        return it != items.end();
        // return true if item is in the set and false if not
    }

    bool insert(T item) {
        // implement insert here
        if (contains(item)){
            return false;
        } else {
            items.push_back(item); // inserts
            return true;
        }
        // return true if item is inserted and false if item is already in the
        // set
    }

    bool remove(T item) {
        if (!contains(item)){
            return false;
        }
        if (contains(item)){
            for (auto iter = items.begin(); iter != items.end(); iter++) {
                if (*iter == item) {
                    items.erase(iter);
                    return true;
                }
            }
        }

        // return true if item is removed and false if item wasn't in the set
    }

    [[nodiscard]] int size() const {
        int count = 0;
        for (const auto& item : items){
            count++;
        }
        return count;
        // return the number of items in the set
    }

    [[nodiscard]] bool empty() const {
        if (items.size() == 0) {
            return true;
        }
        return false;
        // return true if the set is empty and return false otherwise
    }

    void clear() {
        while (!empty()){
            items.pop_back();
        }
        // remove all items from the set
    }
};
