#pragma once

#include <vector>
#include <functional>
#include <string>
using std::string;

template<class T>
int medianOfThree(std::vector<T>& array, int left, int right) {
    int middle = (left + right) / 2;
    if (array[left] > array[middle]){
        T tmp = array[left]; array[left] = array[middle]; array[middle] = tmp;
    } // exchanges left and middle
    if (array[right] < array[middle]){
        T tmp = array[right]; array[right] = array[middle]; array[middle] = tmp;
    }// exchanges right and middle
    if (array[middle] < array[left]){
        T tmp = array[left]; array[left] = array[middle]; array[middle] = tmp;
    }// exchanges middle and left
    return middle;
}

template<class T>
int partition(std::vector<T>& array, int left, int right) {
    int pivot = medianOfThree(array, left, right);
    T tmp=array[pivot]; array[pivot] = array[left]; array[left] = tmp;
    int up = left + 1; int down = right;
    do {
        while ((array[up] <= array[left]) && (up <= right)){up++;}
        while ((array[down] > array[left]) && (down > left)){down--;}
        if (up < down) {
            tmp=array[up]; array[up] = array[down]; array[down] = tmp;
        }
    } while(up < down);
    tmp=array[left]; array[left] = array[down]; array[down] = tmp;
    return down;
}

template<class T>
void quicksort(std::vector<T> &array, int first, int last){
    if (first < last) {
        int pivot = partition(array, first, last);
        quicksort(array, first, (pivot - 1));
        quicksort(array, (pivot + 1), last);
    }
}

template<class T>
void sort(std::vector<T>& array) {
    int first = 0, last = int(array.size()) - 1;
    quicksort(array, first, last);
}


