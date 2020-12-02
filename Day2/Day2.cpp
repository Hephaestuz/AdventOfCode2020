// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Solution {
    struct Policy {
        int min;
        int max;
        char letter;
        std::string password;
    };
public:
    int answerPart1(const std::string& filename = "puzzle_input.txt") {
        int count = 0;
        std::ifstream f(filename);
        if (f.is_open()) {
            std::string line;
            while(getline(f, line)) {
                auto p = parse(line);
                // std::cout << p.min << " " << p.max << " " << p.letter << " " << p.password << std::endl;
                if (check1(p)) {
                    ++count;
                }
            }
        }
        f.close();
        return count;
    }
    int answerPart2(const std::string& filename = "puzzle_input.txt") {
        int count = 0;
        std::ifstream f(filename);
        if (f.is_open()) {
            std::string line;
            while (getline(f, line)) {
                auto p = parse(line);
                if (check2(p)) {
                    ++count;
                }
            }
        }
        f.close();
        return count;
    }

private:
    Policy parse(std::string& line) {
        std::stringstream ss(line);
        int min, max;
        char dash, letter, colon;
        std::string password;
        ss >> min >> dash >> max >> letter >> colon >> password;
        if (dash != '-') {
            throw std::runtime_error("Unexpected policy format: " + std::to_string(min) + dash + std::to_string(max));
        }
        if (colon != ':') {
            throw std::runtime_error("Unexpected policy format: " + letter + colon + password);
        }
        return { min, max, letter, password };
    }
    bool check1(Policy& policy) {
        int count = 0;
        for (auto c : policy.password) {
            if (c == policy.letter) {
                ++count;
            }
        }
        return (count >= policy.min) && (count <= policy.max);
    }
    bool check2(Policy& policy) {
        return (policy.password[policy.min - 1] == policy.letter) ^ (policy.password[policy.max - 1] == policy.letter);
    }
};

int main()
{
    try {
        Solution s;
        std::cout << "Answer part 1: " << s.answerPart1() << std::endl;
        std::cout << "Answer part 2: " << s.answerPart2() << std::endl;
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}
