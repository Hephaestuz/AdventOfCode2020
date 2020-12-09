// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    int part1(int preamble_length, const std::string& filename = "puzzle_input.txt") {
        
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        int num;
        
        // load initial preamble
        for (int i = 0; i < preamble_length; ++i) {
            
            f >> num;
            previous_nums_.push_back(num);
        }

        // find first invalid num
        while (f >> num) {
            if (!validate(num)) {
                return num;
            }
            previous_nums_.pop_front();
            previous_nums_.push_back(num);
        }
    }
    int part2(int target, const std::string& filename = "puzzle_input.txt") {
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        // load data
        int num;
        while (f >> num) {
            nums_.push_back(num);
        }

        // find contiguous sum
        for (int i = 0; i < nums_.size(); ++i) {
            int sum = 0;
            for (int j = i; j < nums_.size(); ++j) {
                sum += nums_[j];
                if (sum > target) {
                    break;
                }
                if (sum == target) {
                    int min = INT_MAX;
                    int max = INT_MIN;
                    while (target != 0) {
                        min = std::min(min, nums_[j]);
                        max = std::max(max, nums_[j]);
                        target -= nums_[j];
                        --j;
                    }
                    return min + max;
                }
            }
        }
    }
private:
    bool validate(int num) {
        for (int i = 0; i < previous_nums_.size(); ++i) {
            for (int j = i+1; j < previous_nums_.size(); ++j) {
                int sum = previous_nums_[i] + previous_nums_[j];
                if (num == sum) {
                    return true;
                }
                if (j == 0 && sum > num) {
                    break;
                }
            }
        }
        return false;
    }

private:
    std::deque<int> previous_nums_;
    std::vector<int> nums_;
};

int main()
{
    Solution s;
    std::cout << "Part 1: " << s.part1(25) << std::endl;
    std::cout << "Part 2: " << s.part2(756008079) << std::endl;
}
