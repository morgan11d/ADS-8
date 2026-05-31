// Copyright 2024 <Copyright Owner>

#include <iostream>
#include <string>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);  // NOLINT
void printFreq(BST<std::string>& tree);  // NOLINT

int main() {
  BST<std::string> tree;

  makeTree(tree, "src/war_peace.txt");
  std::cout << "depth: " << tree.depth() << std::endl;
  std::cout << "pierre: " << tree.search("pierre") << std::endl;
  std::cout << "natasha: " << tree.search("natasha") << std::endl;
  std::cout << "andrew: " << tree.search("andrew") << std::endl;
  printFreq(tree);

  return 0;
}
