// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

class Solution {
public:
    static int processFormsPart1(const std::string& filename = "puzzle_input.txt") {
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }
        std::string line;
        std::set<char> group_answers;
        int sum = 0;
        while (getline(f, line)) {
            if (line.empty()) {
                sum += group_answers.size();
                group_answers.clear();
            }
            else {
                for (char c : line) {
                    group_answers.insert(c);
                }
            } 
        }
        sum += group_answers.size();
        return sum;
    }
    static int processFormsPart2(const std::string& filename = "puzzle_input.txt") {
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }
        std::string line;
        std::map<char, int> group_answers;
        int group_size = 0;
        int sum = 0;
        while (getline(f, line)) {
            if (line.empty()) {
                for (auto it = group_answers.begin(); it != group_answers.end(); ++it) {
                    if (it->second == group_size) {
                        ++sum;
                    }
                }
                group_answers.clear();
                group_size = 0;
            }
            else {
                ++group_size;
                for (char c : line) {
                    auto it = group_answers.find(c);
                    if (it != group_answers.end()) {
                        it->second++;
                    }
                    else {
                        group_answers.insert(std::pair<char, int>(c, 1));
                    }
                }
            }
        }
        for (auto it = group_answers.begin(); it != group_answers.end(); ++it) {
            if (it->second == group_size) {
                ++sum;
            }
        }
        return sum;
    }
};

int main()
{
    try {
        std::cout << "Part 1: " << Solution::processFormsPart1() << std::endl;
        std::cout << "Part 2: " << Solution::processFormsPart2() << std::endl;
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}
