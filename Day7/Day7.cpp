// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

class Bag {
public:
    Bag (const std::string& colour)
        : colour_(colour)
    {}
    std::string colour_;
    std::map<std::string, int> contains_;
};

class Solution {
public:
    void loadRules(const std::string& filename = "puzzle_input.txt") {
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::string line;
        while (getline(f, line)) {
            std::smatch m;

            std::regex_search(line, m, std::regex("([a-z]+ [a-z]+)"));
            if (m.size() < 1) {
                throw std::runtime_error("Failed to parse rule: " + line);
            }
            Bag rule(m[1].str());
            std::map<std::string, int> contains;
            while (std::regex_search(line, m, std::regex("([0-9]) ([a-z]+ [a-z]+)"))) {
                contains.insert(std::pair<std::string, int>(m[2].str(), stoi(m[1].str())));
                line = m.suffix().str();
            }
            rule.contains_ = contains;
            rules_.push_back(rule);
        }
    }
    void printRules() {
        for (auto b : rules_) {
            std::cout << b.colour_ << std::endl;
            for (auto r : b.contains_) {
                std::cout << "\t" << r.first << " " << r.second << std::endl;
            }
        }
    }
    std::set<std::string> getCarryOptions(const std::string& bag_colour) {
        std::set<std::string> set;
        for (const auto& r : rules_) {
            for (const auto& c : r.contains_) {
                if (0 == bag_colour.compare(c.first)) {
                    auto rec_set = getCarryOptions(r.colour_);
                    set.insert(rec_set.begin(), rec_set.end());
                    set.insert(r.colour_);
                }
            }
        }
        return set;
    }
    int countBagContents(const std::string& bag_colour) {
        int count = 1;
        for (const auto& r : rules_) {
            if (0 == bag_colour.compare(r.colour_)) {
                for (const auto& c : r.contains_) {
                    count += c.second * countBagContents(c.first);
                }
            }
        }
        return count;
    }
private:
    std::vector<Bag> rules_;
};

int main()
{
    try {
        Solution s;
        s.loadRules();
        //s.printRules();
        auto outer_bag_options = s.getCarryOptions("shiny gold");
        std::cout << "Number of outmost bag options: " << outer_bag_options.size() << std::endl;
        std::cout << "Total number of bags (inclusive of outer bag - which is not required for answer): " << s.countBagContents("shiny gold") << std::endl;
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}
