#include "../include/bst.h"
#include "alg.cpp"

int main() {
    BST<std::string> tree;
    makeTree(tree, "src/war_peace.txt");
    printFreq(tree);
    return 0;
}
