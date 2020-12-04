// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <regex>

class Solution {
public:
    Solution(const std::string& filename = "puzzle_input.txt") {
        validate(filename);
    }
private:
    void validate(const std::string& filename) {
        std::ifstream f(filename);
        if (f.is_open()) {
            int basic = 0;
            int extensive = 0;
            std::string line;
            std::string passport;
            while (getline(f, line, '\n')) {
                if (line.empty()) {
                    if (isValidBasic(passport)) {
                        ++basic;
                        if (isValidExtensive(passport)) {
                            ++extensive;
                        }
                    }
                    passport.clear();
                }
                else {
                    passport += line + " ";
                }
            }
            if (line.empty()) {
                if (isValidBasic(passport)) {
                    ++basic;
                    if (isValidExtensive(passport)) {
                        ++extensive;
                    }
                }
                passport.clear();
            }
            std::cout << "Basic check: " << basic << std::endl;
            std::cout << "Extensive check: " << extensive << std::endl;
        }
        else {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }
    bool isValidBasic(const std::string& passport) {
        std::smatch m;
        
        std::regex_search(passport, m, std::regex("byr:"));
        if (m.size() < 1) return false;
        std::regex_search(passport, m, std::regex("iyr:"));
        if (m.size() < 1) return false;
        std::regex_search(passport, m, std::regex("eyr:"));
        if (m.size() < 1) return false;
        std::regex_search(passport, m, std::regex("hgt:"));
        if (m.size() < 1) return false;
        std::regex_search(passport, m, std::regex("hcl:"));
        if (m.size() < 1) return false;
        std::regex_search(passport, m, std::regex("ecl:"));
        if (m.size() < 1) return false;
        std::regex_search(passport, m, std::regex("pid:"));
        if (m.size() < 1) return false;

        return true;
    }
    bool isValidExtensive(const std::string& passport) {
        std::smatch m;

        std::regex_search(passport, m, std::regex("byr:([0-9]+)"));
        if (m.size() < 1) return false;
        if (std::stoi(m[1]) < 1920 || std::stoi(m[1]) > 2002) {
            return false;
        }
        
        std::regex_search(passport, m, std::regex("iyr:([0-9]+)"));
        if (m.size() < 1) return false;
        if (std::stoi(m[1]) < 2010 || std::stoi(m[1]) > 2020) {
            return false;
        }

        std::regex_search(passport, m, std::regex("eyr:([0-9]+)"));
        if (m.size() < 1) return false;
        if (std::stoi(m[1]) < 2020 || std::stoi(m[1]) > 2030) {
            return false;
        }

        std::regex_search(passport, m, std::regex("hgt:([0-9]+)cm"));
        if (m.size() < 1) {
            std::regex_search(passport, m, std::regex("hgt:([0-9]+)in"));
            if (m.size() < 1) return false;
            if (std::stoi(m[1]) < 59 || std::stoi(m[1]) > 76) {
                return false;
            }
        }
        else {
            if (std::stoi(m[1]) < 150 || std::stoi(m[1]) > 193) {
                return false;
            }
        }
        
        std::regex_search(passport, m, std::regex("hcl:(#[0-9|a-f]*)"));
        if (m.size() < 1) {
            return false;
        }
        if (m[1].str().size() != 7) {
            return false;
        }

        std::regex_search(passport, m, std::regex("ecl:(amb|blu|brn|gry|grn|hzl|oth){1}"));
        //if (m.size() < 1) return false;
        //if (m.size() > 2) return false;
        std::set<std::string> valid_colours{ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
        //auto it = valid_colours.find(m[1].str());
        //if (valid_colours.count(m[1].str()) != 1) {
        //    return false;
        //}
        
        int count = 0;
        for (auto c : valid_colours) {
            int index;
            int pos = 0;
            while ((index = passport.find("ecl:" + c, pos)) != std::string::npos) {
                count++;
                pos = index + 1; //new position is from next element of index
            }
        }
        if (count != 1) {
            return false;
        }
       
        std::regex_search(passport, m, std::regex("pid:([0-9]*)"));
        if (m.size() < 1) {
            return false;
        }
        if (m[1].str().size() != 9) {
            return false;
        }

        return true;
    }
};

int main()
{
    try {
        Solution s;
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}
