// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Solution {
    struct Slope {
        int horizontal;
        int vertical;
    };
public:
    Solution(const std::string& filename = "puzzle_input.txt") {
        load(filename);
        print();
    }
    int answerPart1(int right = 3, int down = 1) {
        int v = 0;
        int h = 0;
        int v_endstate = geology_.size();
        int count = 0;
        while (v < v_endstate) {
            count += geology_[v][h];
            v += down;
            h += right;
            if (h >= geology_[0].size()) {
                h -= geology_[0].size();
            }
        }
        return count;
    }
    int answerPart2(std::vector<Slope> slopes = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} }) {
        int product = 1;
        for (auto s : slopes) {
            product *= answerPart1(s.horizontal, s.vertical);
        }
        return product;
    }
private:
    void load(const std::string& filename) {
        if (!geology_.empty()) {
            geology_.clear();
        }
        std::ifstream f(filename);
        if (f.is_open()) {
            std::string line;
            while (getline(f, line)) {
                std::vector<int> row;
                for (auto c : line) {
                    switch (c) {
                        case '.':
                            row.push_back(0);
                            break;
                        case '#':
                            row.push_back(1);
                            break;
                        default:
                            throw std::runtime_error("Invalid input character: " + c);
                    }
                }
                geology_.push_back(row);
            }
        }
    }
    void print() {
        for (auto row : geology_) {
            for (auto square : row) {
                std::cout << square << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::vector<int>> geology_;
};

int main()
{
    try {
        Solution s;
        std::cout << "Answer to part 1: " << s.answerPart1() << std::endl;
        std::cout << "Answer to part 2: " << s.answerPart2() << std::endl;
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}

