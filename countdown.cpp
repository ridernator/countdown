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

    if (iterate(numbers, target)) {        
        for (auto iterator = results.rbegin(); iterator != results.rend(); ++iterator) {
            std::cout << *iterator << std::endl;
        }
    } else {
        std::cout << "Solution not found" << std::endl;
    }
}

bool Countdown::iterate(const std::vector<int64_t>& numbers,
                        const int64_t target) {
    if (std::find(numbers.begin(), numbers.end(), target) != numbers.end()) {
        return true;
    }

    if (numbers.size() == 1) {
        return false;
    }

    for(size_t index1 = 0; index1 < numbers.size(); ++index1) {
        int64_t number1 = numbers[index1];

        for(size_t index2 = index1 + 1; index2 < numbers.size(); ++index2) {
            int64_t number2 = numbers[index2];
            std::vector<int64_t> numbersCopy = numbers;
            std::vector<int64_t>::iterator it = numbersCopy.begin();
            std::advance(it, index2);
            numbersCopy.erase(it);

            it = numbersCopy.begin();
            std::advance(it, index1);
            numbersCopy.erase(it);

            numbersCopy.push_back(number1 + number2);
            if (iterate(numbersCopy, target)) {
                std::ostringstream stream;
                stream << number1 << " + " << number2 << " = " << (number1 + number2);
                results.push_back(stream.str());

                return true;
            }
            numbersCopy.pop_back();

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