#pragma once

#include <cstdint>
#include <vector>
#include <string>

class Countdown{
    public:
        Countdown(const std::vector<int64_t>& numbers,
                  const int64_t target);

    private:
        bool iterate(const std::vector<int64_t>& numbers,
                     const int64_t target);

        std::vector<std::string> results;
};