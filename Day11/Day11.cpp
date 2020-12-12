// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    void load(const std::string& filename = "puzzle_input.txt") {
        layout_.clear();
        // example input:
        //
        //      L.LL.L
        //      ..LL..
        //      .L.LL.
        //
        // target data structure: (add border)
        //
        //     BBBBBBBB
        //     BL.LL.LB
        //     B..LL..B
        //     B.L.LL.B
        //     BBBBBBBB
        //
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::string line;
        // read in first line
        std::vector<char> row;
        if (getline(f, line)) {
            // dd top border
            for (int i = 0; i < line.size() + 2; ++i) {
                row.push_back('B');
            }
            layout_.push_back(row);
            // add first row
            row.clear();
            row.push_back('B');
            for (auto c : line) {
                row.push_back(c);
            }
            row.push_back('B');
            layout_.push_back(row);
        }
        // add middle rows
        while (getline(f, line)) {
            row.clear();
            row.push_back('B');
            for (auto c : line) {
                row.push_back(c);
            }
            row.push_back('B');
            layout_.push_back(row);
        }
        // add bottom boarder
        row.clear();
        int row_length = layout_.size() > 0 ? layout_[0].size() : 0;
        for (int i = 0; i < row_length; ++i) {
            row.push_back('B');
        }
        layout_.push_back(row);
    }
    void print() {
        for (const auto& row : layout_) {
            for (auto c : row) {
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }
    int part1() {
        int row_c = layout_.size();
        int col_c = layout_[0].size();
        auto tmp = layout_;
        bool changed = true;
        while (changed) {
            changed = false;
            for (int r = 1; r < row_c - 1; ++r) {
                for (int c = 1; c < col_c - 1; ++c) {
                    char ch = getNext(r, c);
                    tmp[r][c] = ch;
                    if (ch != layout_[r][c]) {
                        changed = true;
                    }
                }
            }
            layout_ = tmp;
        }
        return countOccupied();
    }
    int part2() {
        int row_c = layout_.size();
        int col_c = layout_[0].size();
        auto tmp = layout_;
        bool changed = true;
        while (changed) {
            changed = false;
            for (int r = 1; r < row_c - 1; ++r) {
                for (int c = 1; c < col_c - 1; ++c) {
                    char ch = getNextPart2(r, c);
                    tmp[r][c] = ch;
                    if (ch != layout_[r][c]) {
                        changed = true;
                    }
                }
            }
            layout_ = tmp;
        }
        return countOccupied();
    }
private:
    char getNext(int row, int col) {
        if (layout_[row][col] == '.') {
            return '.';
        }
        int occupied_c = 0;
        for (int r = row - 1; r < row + 2; ++r) {
            for (int c = col - 1; c < col + 2; ++c) {
                if (r == row && c == col) {
                    continue;
                }
                if (layout_[r][c] == '#') {
                    ++occupied_c;
                }
            }
        }
        if (layout_[row][col] == '#' && occupied_c > 3) {
            return 'L';
        }
        if (layout_[row][col] == 'L' && occupied_c  == 0) {
            return '#';
        }
        return layout_[row][col];
    }
    char getNextPart2(int row, int col) {
        if (layout_[row][col] == '.') {
            return '.';
        }
        int occupied_c = 0;
        for (auto d : directions) {
            if (lineOfSiteIsOccupied(row, col, d)) {
                ++occupied_c;
            }
        }
        if (layout_[row][col] == '#' && occupied_c > 4) {
            return 'L';
        }
        if (layout_[row][col] == 'L' && occupied_c == 0) {
            return '#';
        }
        return layout_[row][col];
    }
    enum class Direction {
        N,
        NE,
        E,
        SE,
        S,
        SW,
        W,
        NW
    };
    bool lineOfSiteIsOccupied(int row, int col, Direction d) { 
        int r_delta = 0;
        int c_delta = 0;
        switch (d) {
        case Direction::N:
            r_delta = -1;
            break;
        case Direction::NE:
            r_delta = -1;
            c_delta = 1;
            break;
        case Direction::E:
            c_delta = 1;
            break;
        case Direction::SE:
            r_delta = 1;
            c_delta = 1;
            break;
        case Direction::S:
            r_delta = 1;
            break;
        case Direction::SW:
            r_delta = 1;
            c_delta = -1;
            break;
        case Direction::W:
            c_delta = -1;
            break;
        case Direction::NW:
            c_delta = -1;
            r_delta = -1;
            break;
        default:
            throw std::runtime_error("Unknown direction");
        }
        row += r_delta;
        col += c_delta;
        while (layout_[row][col] != 'B') {
            if (layout_[row][col] == 'L') {
                return false;
            }
            if (layout_[row][col] == '#') {
                return true;
            }
            row += r_delta;
            col += c_delta;
        }
        return false;
    }
    int countOccupied() {
        int count = 0;
        for (auto row : layout_) {
            for (auto c : row) {
                if (c == '#') {
                    ++count;
                }
            }
        }
        return count;
    }
private:
    std::vector<Direction> directions{ Direction::N, Direction::NE, Direction::E, Direction::SE, Direction::S, Direction::SW, Direction::W, Direction::NW };
    std::vector<std::vector<char>> layout_;
};

int main()
{
    Solution s;
    s.load();
    std::cout << "Answer to part 1: " << s.part1() << std::endl;
    s.load();
    std::cout << "Answer to part 2: " << s.part2() << std::endl;
}


