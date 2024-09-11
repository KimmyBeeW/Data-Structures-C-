#include <cstring>
#include <iostream>
#include <string>

#include "AVL.h"
#include "printing.h"

// --------- HELPER FUNCTIONS ---------

void noisy_insert(AVL<int>& tree, int item) {
    std::cout << "tree.insert(" << item << ") = " << std::boolalpha << tree.insert(item) << std::endl;
}

void noisy_remove(AVL<int>& tree, int item) {
    std::cout << "tree.remove(" << item << ") = " << std::boolalpha << tree.remove(item) << std::endl;
}

void check_and_remove_head(AVL<int>& tree) {
    std::cout << std::endl;
    std::cout << "root->value = " << tree.getRootNode()->value << std::endl;
    noisy_remove(tree, tree.getRootNode()->value);
}

void noisy_contains(const AVL<int>& tree, int item) {
    std::cout << "tree.contains(" << item << ") = " << std::boolalpha << tree.contains(item) << std::endl;
}

void noisy_clear(AVL<int>& tree) {
    tree.clear();
    std::cout << "tree.clear()" << std::endl;
}

void noisy_size(const AVL<int>& tree) {
    std::cout << "tree.size() = " << tree.size() << std::endl;
}

// --------- END HELPER FUNCTIONS ---------

void test16() {
    std::cout << "--- Test 16 output ---\n" << std::endl;

    AVL<int> tree;

    tree.insert(10);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(8);
    tree.insert(12);
    tree.insert(16);
    tree.insert(2);
    tree.insert(5);
    tree.insert(7);
    tree.insert(11);
    tree.insert(13);
    tree.insert(15);
    tree.insert(17);
    tree.insert(1);
    tree.insert(3);
    pretty_print_tree(tree);

    std::cout << "\ntest 1: remove 17 \n" << std::endl;
    tree.remove(17);
    pretty_print_tree(tree);
    //noisy_remove(tree, 10);
    std::cout << "\ntest 2: remove 15 \n" << std::endl;
    tree.remove(15);
    pretty_print_tree(tree);

    std::cout << "\ntest 3: remove 6 \n" << std::endl;
    tree.remove(6);
    pretty_print_tree(tree);

    std::cout << "\ntest 4: remove 10 \n" << std::endl;
    tree.remove(10);
    pretty_print_tree(tree);

//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);
//    check_and_remove_head(tree);

    std::cout << std::endl;
    noisy_size(tree);
}

int main(){
    test16();
    return 0;
}
