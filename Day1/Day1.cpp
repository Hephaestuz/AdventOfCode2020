// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    Solution(const std::string& filename = "puzzle_input.txt") {
        loadData(filename);
        if (expense_report_.size() < 2) {
            throw std::runtime_error("Not enough expense data");
        }
        sort();
    }
    void printData() {
        for (const auto& d : expense_report_) {
            std::cout << d << " ";
        }
        std::cout << std::endl;
    }
    int answerPart1() {
        for (int i = 0; i < expense_report_.size() - 1; ++i) {
            for (int j = i + 1; j < expense_report_.size(); ++j) {
                if (expense_report_[i] + expense_report_[j] > 2020) {
                    break;
                }
                if (expense_report_[i] + expense_report_[j] == 2020) {
                    return expense_report_[i] * expense_report_[j];
                }
            }
        }
        return -1;
    }
    int answerPart2() {
        for (int i = 0; i < expense_report_.size() - 2; ++i) {
            for (int j = i + 1; j < expense_report_.size(); ++j) {
                for (int k = j + 1; k < expense_report_.size(); ++k) {
                    if (expense_report_[i] + expense_report_[j] + expense_report_[k] > 2020) {
                        break;
                    }
                    if (expense_report_[i] + expense_report_[j] + expense_report_[k] == 2020) {
                        return expense_report_[i] * expense_report_[j] * expense_report_[k];
                    }
                }
            }
        }
        return -1;
    }
private:
    void loadData(const std::string& filename = "puzzle_input.txt") {
        std::ifstream f(filename);
        if (f.is_open()) {
            int num;
            while (f >> num) {
                expense_report_.push_back(num);
            }
        }
        f.close();
    }
    void sort() {
        if (!sorted_) {
        std::sort(expense_report_.begin(), expense_report_.end());
        }
    }
private:
    std::vector<int> expense_report_;
    bool sorted_ = false;
};

int main()
{
    try {
        Solution s;
        s.printData();
        std::cout << "Answer part 1: " << s.answerPart1() << std::endl;
        std::cout << "Answer part 2: " << s.answerPart2() << std::endl;
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}
