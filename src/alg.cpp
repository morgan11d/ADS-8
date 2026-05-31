// Copyright 2024 <Copyright Owner>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

namespace {

bool isLatinLetter(int ch) {
  return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char toLowerLetter(int ch) {
  if (ch >= 'A' && ch <= 'Z') {
    return static_cast<char>(ch - 'A' + 'a');
  }

  return static_cast<char>(ch);
}

bool compareByFrequency(const BST<std::string>::Item& left,
                        const BST<std::string>::Item& right) {
  if (left.count != right.count) {
    return left.count > right.count;
  }

  return left.value < right.value;
}

}  // namespace

void makeTree(BST<std::string>& tree, const char* filename) {  // NOLINT
  std::ifstream file(filename, std::ios::binary);

  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word;
  char ch = 0;

  while (file.get(ch)) {
    int code = static_cast<unsigned char>(ch);

    if (isLatinLetter(code)) {
      word.push_back(toLowerLetter(code));
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {  // NOLINT
  std::vector<BST<std::string>::Item> values = tree.items();
  std::sort(values.begin(), values.end(), compareByFrequency);

  std::ofstream result("result/freq.txt");

  for (const BST<std::string>::Item& item : values) {
    std::cout << item.value << " " << item.count << std::endl;

    if (result) {
      result << item.value << " " << item.count << std::endl;
    }
  }

  result.close();
}
