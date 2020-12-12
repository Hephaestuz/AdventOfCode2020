// Day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class SolutionPart1 {
    enum class Direction { N, W, S, E };
    std::vector<Direction> directions_{ Direction::N, Direction::W, Direction::S, Direction::E }; // anti-clockwise ordering
    std::string to_string(Direction d) {
        switch (d) {
        case Direction::N:
            return "North";
            break;
        case Direction::W:
            return "West";
            break;
        case Direction::S:
            return "South";
            break;
        case Direction::E:
            return "East";
            break;
        default:
            throw std::runtime_error("to_string: Unknown direction.");
        }
    }
public:
    int run(const std::string& filename = "puzzle_input.txt") {
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        Direction d = Direction::E;
        int pos_N = 0;
        int pos_E = 0;

        char action;
        int value;

        while (f >> action >> value) {
            if (action == 'L' || action == 'R') {
                d = changeDirection(d, action, value);
                continue;
            }
            switch (action) {
            case 'N':
                pos_N += value;
                break;
            case 'S':
                pos_N -= value;
                break;
            case 'E':
                pos_E += value;
                break;
            case 'W':
                pos_E -= value;
                break;
            case 'F':
                switch (d) {
                case Direction::N:
                    pos_N += value;
                    break;
                case Direction::S:
                    pos_N -= value;
                    break;
                case Direction::E:
                    pos_E += value;
                    break;
                case Direction::W:
                    pos_E -= value;
                    break;
                default:
                    throw std::runtime_error("part1: Unknown direction.");
                }
                break;
            default:
                throw std::runtime_error("Unknown action: " + action);
            }
        }
        return abs(pos_N) + abs(pos_E);
    }
private: 
    Direction changeDirection(Direction current, char action, int value) {
        int i = value / 90;
        int c = 0;
        switch (current) {
        case Direction::N:
            c = 0;
            break;
        case Direction::W:
            c = 1;
            break;
        case Direction::S:
            c = 2;
            break;
        case Direction::E:
            c = 3;
            break;
        default:
            throw std::runtime_error("changeDirection: Unknown direction.");
        }
        if (action == 'L') { 
            return directions_[(c + i) % directions_.size()]; // rotate anti-clockwise
        }
        return directions_[(4 + c - i) % directions_.size()];     // rotate clockwise
    }
};

class SolutionPart2 {
    enum class Direction { N, W, S, E };
    std::vector<Direction> directions_{ Direction::N, Direction::W, Direction::S, Direction::E }; // anti-clockwise ordering
    std::string to_string(Direction d) {
        switch (d) {
        case Direction::N:
            return "North";
            break;
        case Direction::W:
            return "West";
            break;
        case Direction::S:
            return "South";
            break;
        case Direction::E:
            return "East";
            break;
        default:
            throw std::runtime_error("to_string: Unknown direction.");
        }
    }
public:
    int run(const std::string& filename = "puzzle_input.txt") {        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        int pos_N = 0;
        int pos_E = 0;

        int wp_N = 1;
        int wp_E = 10;

        char action;
        int value;

        while (f >> action >> value) {
            if (action == 'L' || action == 'R') {
                rotateWaypoint(wp_N, wp_E, action, value);
                continue;
            }
            switch (action) {
            case 'N':
                wp_N += value;
                break;
            case 'S':
                wp_N -= value;
                break;
            case 'E':
                wp_E += value;
                break;
            case 'W':
                wp_E -= value;
                break;
            case 'F':
                pos_N += wp_N * value;
                pos_E += wp_E * value;
                break;
            default:
                throw std::runtime_error("Unknown action: " + action);
            }
        }
        return abs(pos_N) + abs(pos_E);
    }
private:
    void rotateWaypoint(int& wp_N, int& wp_E, char action, int value) {
        int c = 0;

        if (value == 180) {
            wp_N *= -1;
            wp_E *= -1;
            return;
        }
        if ((value == 90 && action == 'L') || (value == 270 && action == 'R')) {
            auto tmp = wp_N;
            wp_N = wp_E ;
            wp_E = -1 * tmp;
            return;
        }
        if ((value == 90 && action == 'R') || (value == 270 && action == 'L')) {
            auto tmp = wp_N;
            wp_N = -1 * wp_E;
            wp_E = tmp;
            return;
        }

        throw std::runtime_error("rotateWaypoint: Unknown action/value: " + action + std::string("/") + std::to_string(value) );
    }
};

int main()
{
    try {
        SolutionPart1 s1;
        std::cout << "Answer to part 1: " << s1.run() << std::endl;

        SolutionPart2 s2;
        std::cout << "Answer to part 2: " << s2.run() << std::endl;
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
    
}
