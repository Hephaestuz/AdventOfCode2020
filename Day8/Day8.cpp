// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

struct Instruction {
    std::string operation;
    int argument;
};

class Solution {
public:
    void loadProgram(const std::string& filename = "puzzle_input.txt") {
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::string instruction;
        int argument;
        while (f >> instruction) {
            f >> argument;
            program_.push_back({ instruction, argument });
        }
    }
    void printProgram() {
        for (const auto& i : program_) {
            std::cout << i.operation << " " << i.argument << std::endl;
        }
    }
    int run() {
        success_ = false;
        int sum = 0;
        std::set<int> set;
        int i = 0; // index
        while (true) {
            if (i == program_.size()) {
                success_ = true;
                return sum;
            }
            auto it = set.find(i);
            if (it != set.end()) {
                return sum;
            }
            else {
                set.insert(i);
            }
            if (0 == program_[i].operation.compare("acc")) {
                sum += program_[i].argument;
                ++i;
            }
            else if (0 == program_[i].operation.compare("jmp")) {
                i += program_[i].argument;
            }
            else {
                ++i;
            }
        }
    }
    int fixProgram() {
        for (int i = 0; i < program_.size(); ++i) {
            flipOperation(i);
            auto accumulator = run();
            if (success_) {
                return accumulator;
            }
            flipOperation(i); // change operation back
        }
    }
private: 
    void flipOperation(int i) {
        if (0 == program_[i].operation.compare("jmp")) {
            program_[i].operation = "nop";
        }
        else if (0 == program_[i].operation.compare("nop")) {
            program_[i].operation = "jmp";
        }
    }
private:
    std::vector<Instruction> program_;
    bool success_ = false;
};

int main()
{
    try {
        Solution s;
        s.loadProgram();
        //s.printProgram();
        std::cout << "Accumulator value at start of infinite loop: " << s.run() << std::endl;
        std::cout << "Accumulator value at of corrected program: " << s.fixProgram() << std::endl;
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}
