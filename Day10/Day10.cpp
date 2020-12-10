// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>


class Solution {
public:
    void load(const std::string& filename = "puzzle_input.txt") {
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        int a;
        while (f >> a) {
            adapters_.push_back(a);
        }
        adapters_.push_back(*std::max_element(adapters_.begin(), adapters_.end()) + 3); // my device is modelled as the final adapter 
    }
    int part1() {
        std::sort(adapters_.begin(), adapters_.end());
        
        int previous = 0;
        int count_3 = 0;
        int count_1 = 0;
        for (auto& a : adapters_) {
            if (a - previous == 3) {
                ++count_3;
            }
            else if (a - previous == 1) {
                ++count_1;
            }
            else {
                throw std::runtime_error("Unexpected gap between adapter values. Current: " + std::to_string(a) + " Previous: " + std::to_string(previous));
            }
            previous = a;
        }
        return count_1 * count_3;
    }
    int part2() {
        std::sort(adapters_.begin(), adapters_.end());
        result_ = 0; // avoid repeat runs chaning result
        rec(0, 0);
        return result_;
    }
    void rec(int previous, int index) {
        if (index == adapters_.size()) {
            ++result_;
        }
        for (int i = index; i < adapters_.size(); ++i) {
            for (int j = i; j < adapters_.size(); ++j) {
                if (adapters_[j] - previous < 4) {
                    rec(adapters_[j], j + 1);
                }
                break;
            }
        }
    }
    unsigned long long part2Optimized() {
        std::sort(adapters_.begin(), adapters_.end());
        std::map<int, unsigned long long> routes_to;
        routes_to.insert(std::pair<int, int>(0, 1));
        for (auto a : adapters_) {
            routes_to.insert(std::pair<int, int>(a, 0));
        }
        int previous = 0;
        unsigned long long path_to_previous = 1;
        for (int i = 0; i < adapters_.size(); ++i) {
            auto it = routes_to.find(previous);
            path_to_previous = it->second;
            for (int j = i; j < adapters_.size(); ++j) {
                if (adapters_[j] - previous < 4) {
                    auto jt = routes_to.find(adapters_[j]);
                    jt->second += path_to_previous;
                }
                else {
                    break;
                }
            }
            previous = adapters_[i];
        }
        return routes_to.find(adapters_.back())->second;
    }
private:
    std::vector<int> adapters_;
    size_t result_;
};

int main()
{
    Solution s;
    s.load();
    std::cout << "Answer to part 1: " << s.part1() << std::endl;
    //std::cout << "Answer to part 2: " << s.part2() << std::endl;
    std::cout << "Answer to part 2: " << s.part2Optimized() << std::endl;
}

