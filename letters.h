#pragma once

#include <cstdint>
#include <vector>
#include <string>

/**
 * Class which solves the Countdown maths questions
 **/
class Numbers{
    public:
        /**
         * Constructor for this class
         * 
         * @param numbers The input numbers (As many as you like)
         * @param target The target to hit
         **/
        Numbers(const std::vector<int64_t>& numbers,
                  const int64_t target);

    private:
        /**
         * Recursive method to solve the problem
         * 
         * @param numbers The current collection of numbers
         * @param target The target to hit
         * @return Returns true if solved of false if this path has no solution
         **/
        bool iterate(const std::vector<int64_t>& numbers,
                     const int64_t target);

        /**
         * Place to store result steps
         **/
        std::vector<std::string> results;
};