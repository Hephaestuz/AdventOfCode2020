// Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    int getMaxSeatId(const std::string& filename = "puzzle_input.txt") {
        int max = -1;
        std::ifstream f(filename);
        if (f.is_open()) {
            std::string line;
            while (getline(f, line)) {
                max = std::max(max, seatId(line));
            }
        }
        else {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        return max;
    }
    int getEmtpySeat(const std::string& filename = "puzzle_input.txt") {
        std::vector<std::string> seats;
        std::ifstream f(filename);
        if (f.is_open()) {
            std::string line;
            while (getline(f, line)) {
                seats.push_back(line);
            }
        }
        std::sort(seats.begin(), seats.end(),
            [](const std::string& a, const std::string& b) {
                return seatId(a) < seatId(b);
            });
        for (int i = 0; i < seats.size() - 1; ++i) {
            if (seatId(seats[i]) + 1 != seatId(seats[i + 1])) {
                return seatId(seats[i]) + 1;
            }
        }
        return -1;
    }
private:
    static int seatId(const std::string& seat_code) {
        if (seat_code.size() != 10) {
            throw std::runtime_error("Seat code invalid length: " + seat_code);
        }
        int index = 0;
        int factor = 64;
        int row = 0;
        for (; index < 7; ++index) {
            if (seat_code[index] == 'B') {
                row += factor;
            }
            else if (seat_code[index] != 'F') {
                throw std::runtime_error("Unexpected character in seat code: " + seat_code[index]);
            }
            factor /= 2;
        }
        factor = 4;
        int seat = 0;
        for (; index < 10; ++index) {
            if (seat_code[index] == 'R') {
                seat += factor;
            }
            else if (seat_code[index] != 'L') {
                throw std::runtime_error("Unexpected character in seat code: " + seat_code[index]);
            }
            factor /= 2;
        }
        return row  * 8 + seat;
    }
};

int main()
{
    try {
        Solution s;
        std::cout << "Max seat id: " << s.getMaxSeatId() << std::endl;
        std::cout << "Empty seat id: " << s.getEmtpySeat() << std::endl;
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}
