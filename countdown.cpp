#include "countdown.h"

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <sstream>

Countdown::Countdown(const std::vector<int64_t>& numbers,
                     const int64_t target) {
    std::cout << "Numbers are : ";
    for (const auto number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    std::cout << "Target is   : " << target << std::endl;

    if (iterate(numbers, target)) { // Solution found
        // Print out steps in reverse order
        for (auto iterator = results.rbegin(); iterator != results.rend(); ++iterator) {
            std::cout << *iterator << std::endl;
        }
    } else { // Solution not found
        std::cout << "Solution not found. Trying to find nearest target" << std::endl;

        for (int64_t offset = 1; offset < target; ++offset) {
            if (iterate(numbers, target + offset)) { // Solution found
                std::cout << "Best found was " << (target + offset) << ":" << std::endl;

                // Print out steps in reverse order
                for (auto iterator = results.rbegin(); iterator != results.rend(); ++iterator) {
                    std::cout << *iterator << std::endl;
                }

                break;
            }

            if (iterate(numbers, target - offset)) { // Solution found
                std::cout << "Best found was " << (target - offset) << ":" << std::endl;
                
                // Print out steps in reverse order
                for (auto iterator = results.rbegin(); iterator != results.rend(); ++iterator) {
                    std::cout << *iterator << std::endl;
                }

                break;
            }
        }
    }
}

bool Countdown::iterate(const std::vector<int64_t>& numbers,
                        const int64_t target) {
    // If number is not in collection
    if (std::find(numbers.begin(), numbers.end(), target) != numbers.end()) {
        return true;
    }

    // If there is only 1 number in the collection then we can't continue
    if (numbers.size() == 1) {
        return false;
    }

    // Loop through all possible pairs
    for(size_t index1 = 0; index1 < numbers.size(); ++index1) {
        // Store first number in pair
        int64_t number1 = numbers[index1];

        for(size_t index2 = index1 + 1; index2 < numbers.size(); ++index2) {
            // Store second number in pair
            int64_t number2 = numbers[index2];

            // Take a copy of the collection of numbers
            std::vector<int64_t> numbersCopy = numbers;

            // Remove number 2 from collection
            std::vector<int64_t>::iterator it = numbersCopy.begin();
            std::advance(it, index2);
            numbersCopy.erase(it);

            // Remove number 1 from collection
            it = numbersCopy.begin();
            std::advance(it, index1);
            numbersCopy.erase(it);

            // Test if adding the 2 numbers together helps
            // Push the number into the collection and pop it off if it doesn't help
            numbersCopy.push_back(number1 + number2);
            if (iterate(numbersCopy, target)) {
                std::ostringstream stream;
                stream << number1 << " + " << number2 << " = " << (number1 + number2);
                results.push_back(stream.str());

                return true;
            }
            numbersCopy.pop_back();

            // Test if subtracting number 2 from number 1 helps
            if (number1 - number2 > 0) {
                numbersCopy.push_back(number1 - number2);
                if (iterate(numbersCopy, target)) {
                    std::ostringstream stream;
                    stream << number1 << " - " << number2 << " = " << (number1 - number2);
                    results.push_back(stream.str());

                    return true;
                }
                numbersCopy.pop_back();
            }

            // Test if subtracting number 1 from number 2 helps
            if (number2 - number1 > 0) {
                numbersCopy.push_back(number2 - number1);
                if (iterate(numbersCopy, target)) {
                    std::ostringstream stream;
                    stream << number2 << " - " << number1 << " = " << (number2 - number1);
                    results.push_back(stream.str());

                    return true;
                }
                numbersCopy.pop_back();
            }

            // Test if multiplying both numbers together helps
            // Skip if one of the numbers is 1
            if ((number1 != 1) && (number2 != 1)) {
                numbersCopy.push_back(number1 * number2);
                if (iterate(numbersCopy, target)) {
                    std::ostringstream stream;
                    stream << number1 << " X " << number2 << " = " << (number1 * number2);
                    results.push_back(stream.str());

                    return true;
                }
                numbersCopy.pop_back();
            }

            // Test if dividing number 2 by number 1 helps
            // Skip if number 2 is not divisible by number 1
            // Skip if number 1 is 1
            if ((number2 % number1 == 0) && (number1 != 1)) {
                numbersCopy.push_back(number2 / number1);
                if (iterate(numbersCopy, target)) {
                    std::ostringstream stream;
                    stream << number2 << " / " << number1 << " = " << (number2 / number1);
                    results.push_back(stream.str());

                    return true;
                }
                numbersCopy.pop_back();
            }

            // Test if dividing number 1 by number 2 helps
            // Skip if number 1 is not divisible by number 2
            // Skip if number 2 is 1
            if ((number1 % number2 == 0) && (number2 != 1)) {
                numbersCopy.push_back(number1 / number2);
                if (iterate(numbersCopy, target)) {
                    std::ostringstream stream;
                    stream << number1 << " / " << number2 << " = " << (number1 / number2);
                    results.push_back(stream.str());

                    return true;
                }
                numbersCopy.pop_back();
            }
        }
    }

    return false;
}

int main(const int argc,
         const char** argv) {

    std::vector<int64_t> numbers;
    int64_t target;

    for (int index = 0; index < argc - 2; ++index) {
        numbers.push_back(std::strtoull(*(argv + index + 1), nullptr, 0));
    }

    target = std::strtoull(*(argv + argc - 1), NULL, 0);

    Countdown countdown(numbers, target);
}   