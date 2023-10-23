#pragma once

#include <cstdint>
#include <string>
#include <map>

/**
 * Class which models an element in the word tree
 **/
class Element{
    public:
        /**
         * Constructor for this class
         * 
         * @param letter The letter this element relates to or space if it is the head of the tree
         **/
        Element(const char letter = ' ');

        /**
         * Destructor for this class
         **/
        ~Element();

        /**
         * The letter this element relates to or space if it is the head of the tree
         **/
        char letter;

        /**
         * Map of the next letters
         **/
        std::map<char, Element*> next;
};

/**
 * Class which solves the Countdown letters questions
 **/
class Letters{
    public:
        /**
         * Constructor for this class
         * 
         * @param numbers The input letters
         * @param target The wordlist to use
         **/
        Letters(const std::string& letters,
                const std::string& wordlist);

    private:
        /**
         * Read from a wordlist into the letter tree
         * 
         * @param wordlist The world list to parse
         **/
        void populateTree(const std::string& wordlist);

        /**
         * Find the longest word in a string starting from the beginning
         * 
         * @param word The string to test
         * @return The length of the longest word in it, starting from the beginning
         **/
        uint32_t findMaxLength(const std::string& word);

        /**
         * Test if an element in the tree is a leaf or not
         * 
         * @param element The element to test
         * @return True if it is a leaf or false if not
         **/
        bool isLeaf(const Element* element);

        /**
         * The data structure modelling the letter tree
         **/
        Element tree;
};