// Day16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

struct Field {
    std::string name_;
    int low_min_;
    int low_max_;
    int high_min_;
    int high_max_;
    
    Field(const std::string& extract_from_string) {
        auto pos = extract_from_string.find(":");
        name_ = extract_from_string.substr(0, pos);
        std::smatch sm;
        auto ranges = extract_from_string.substr(pos, extract_from_string.size());
        std::regex_search(ranges, sm, std::regex{ "([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)" });
        if (sm.size() != 5) {
            throw std::runtime_error("Failed to pass field ranges: " + extract_from_string);
        }
        low_min_  = stoi(sm[1].str());
        low_max_  = stoi(sm[2].str());
        high_min_ = stoi(sm[3].str());
        high_max_ = stoi(sm[4].str());
    }

    bool valid(int i) {
        if (i < low_min_) {
            return false;
        }
        if (i < low_max_) {
            return true;
        }
        if (i < high_min_) {
            return false;
        }
        if (i < high_max_) {
            return true;
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Field& f) {
    return os << f.name_ << ": " << f.low_min_ << "-" << f.low_max_ << " or " << f.high_min_ << "-" << f.high_max_;
}

struct Ticket {
    std::vector<int> data_;

    Ticket() {}

    Ticket(const std::string& extract_from_string) {
        std::stringstream ss(extract_from_string);
        int i;
        char ch;
        while (true) {
            if (ss >> i) {
                data_.push_back(i);
                if (ss >> ch) {
                    if (ch == ',') continue;
                    else break;
                }
                else break;
            }
            else {
                throw std::runtime_error("Invalid ticket: " + extract_from_string);
            }
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Ticket& f) {
    for (auto v : f.data_) {
        os << v << " ";
    }
    return os;
}

class Solution {
public:
    int part1() {
        load();
        printData();

        for (const auto& t : tickets_) {

        }
        return -1;
    }
private:
    void load(const std::string& filename = "puzzle_input.txt") {
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::string line;
        // load rules
        while (getline(f, line)) {
            if (0 == line.size()) break;
            rules_.push_back(line);
        }
        // load my ticket
        getline(f, line);
        if (0 != line.compare("your ticket:")) {
            throw std::runtime_error("Invalid input data. Last line processed: " + line);
        }
        getline(f, line);
        my_ticket_ = Ticket(line);
        // load nearby tickets
        getline(f, line);
        getline(f, line);
        if (0 != line.compare("nearby tickets:")) {
            throw std::runtime_error("Invalid input data. Last line processed: " + line);
        }
        while (getline(f, line)) {
            if (0 == line.size()) break;
            tickets_.push_back( Ticket(line));
        }
    }
    void printData() {
        for (auto& r : rules_) {
            std::cout << r << std::endl;
        }
        std::cout << "My ticket: " << std::endl;
        std::cout << my_ticket_ << std::endl;
        std::cout << "Nearby tickets: " << std::endl;
        for (auto& t : tickets_) {
            std::cout << t << std::endl;
        }
    }
private:
    std::vector<Field> rules_;
    Ticket my_ticket_;
    std::vector<Ticket> tickets_;
};

int main()
{
    try {
        Solution s;
        s.part1();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
