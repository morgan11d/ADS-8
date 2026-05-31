#include "../include/bst.h"
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

void insertBalanced(BST<std::string>& tree, const std::vector<std::pair<std::string, int>>& items, int start, int end) {
    if (start > end) return;
    int mid = (start + end) / 2;
    tree.insert(items[mid].first, items[mid].second);
    insertBalanced(tree, items, start, mid - 1);
    insertBalanced(tree, items, mid + 1, end);
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::map<std::string, int> freq;
    std::string word;
    while (!file.eof()) {
        int ch = file.get();
        if (ch == EOF) break;
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!word.empty()) {
                freq[word]++;
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        freq[word]++;
    }
    file.close();
    
    std::vector<std::pair<std::string, int>> items(freq.begin(), freq.end());
    insertBalanced(tree, items, 0, items.size() - 1);
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
