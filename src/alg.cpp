#include "../include/bst.h"
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

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
    
    std::vector<std::string> keys;
    for (const auto& p : freq) {
        keys.push_back(p.first);
    }
    std::sort(keys.begin(), keys.end());
    
    for (const auto& k : keys) {
        for (int i = 0; i < freq[k]; i++) {
            tree.insert(k);
        }
    }
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
