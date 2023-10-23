#include "letters.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>

Element::Element(const char letter) : letter(letter) {
    for (char index = 'a'; index <= 'z'; ++index) {
        next[index] = nullptr;
    }
}

Element::~Element() {
    for (const auto& [key, value] : next) {
        delete value;
    }
}

Letters::Letters(const std::string& letters,
                 const std::string& wordlist) {
    std::string lettersCopy = letters;

    // Needs sorting before permuting
    std::sort(lettersCopy.begin(), lettersCopy.end());

    // Read from worldist into tree
    populateTree(wordlist);

    std::string longestWord = "";
    uint32_t longestWordLength = 0;

    std::cout << "Searching for words" << std::endl;

    // For eeach permutation find the longest word in it starting from the beginning
    do {
        uint32_t length = findMaxLength(lettersCopy);

        if (length > longestWordLength) {
            longestWordLength = length;
            longestWord = lettersCopy.substr(0, length);
        }
    } while (std::next_permutation(lettersCopy.begin(), lettersCopy.end()));

    std::cout << "Best word is " << longestWordLength << " letters: " << longestWord << std::endl;
}

uint32_t Letters::findMaxLength(const std::string& word) {
    uint32_t length = 0;
    Element* treeCopy = &tree;

    // Navigate down the tree until we reach a leaf or run out of road or run out of letters
    for (const char& letter : word) {
        if (isLeaf(treeCopy)) {
            // If we get to a leaf then return the lenght of the string
            return length;
        } else {
            // No leaft so move on to next letter
            ++length;

            // If the next letter in not availible then we have found nothing
            if (treeCopy->next[letter] == nullptr) {
                return 0;
            } else {
                // Move down the branch of the tree
                treeCopy = treeCopy->next[letter];
            }
        }
    }

    return length;
}

bool Letters::isLeaf(const Element* element) {
    bool returnVal = true;

    // If the element has no next letters then it is a leaf
    for (const auto& [key, value] : element->next) {
        if (value != nullptr) {
            returnVal = false;

            break;
        }
    }

    return returnVal;
}

void Letters::populateTree(const std::string& wordlist) {
    std::cout << "Populating letter tree" << std::endl;

    std::ifstream fileStream;

    fileStream.open(wordlist, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "wordlist \"" << wordlist << "\" cannot be opened" << std::endl;

        return;
    }

    std::string word;
    // Read in the next word from the list
    while (std::getline(fileStream, word)) {
        Element* treeCopy = &tree;

        // For each letter in this word
        for (const char& letter : word) {
            char lowLetter = std::tolower(letter);

            // Of the element has no next letter of this type then create one
            if (treeCopy->next[lowLetter] == nullptr) {
                treeCopy->next[lowLetter] = new Element(lowLetter);
            }

            // Move to next letter
            treeCopy = treeCopy->next[lowLetter];
        }
    }

    fileStream.close();
}

int main(const int argc,
         const char** argv) {
    if (argc != 3) {
        std::cerr << "Usage letters wordlist letters" << std::endl;

        std::exit(EXIT_FAILURE);
    }

    std::string wordlist = *(argv + 1);
    std::string letters = *(argv + 2);

    Letters program(letters, wordlist);
}   