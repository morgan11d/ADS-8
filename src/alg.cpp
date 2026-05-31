#include "../include/bst.h"
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>

bool isLatinAlpha(int ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::string word;
    int ch;
    while ((ch = file.get()) != EOF) {
        if (isLatinAlpha(ch)) {
            word += std::tolower(ch);
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        tree.insert(word);
    }
    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cout << "Cannot create output file!" << std::endl;
        return;
    }
    tree.printByFrequency(std::cout);
    tree.printByFrequency(outFile);
    outFile.close();
}
