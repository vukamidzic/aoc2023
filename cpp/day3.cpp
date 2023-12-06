#include <ctype.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

typedef std::pair<int, int> Coord;

void get_numbers(std::string line, int i, std::vector<std::pair<int, std::vector<Coord>>>& numbers) {
    std::string buffer = "";
    std::vector<Coord> coords;

    for (int j = 0; j < line.size(); ++j) {
        if (isdigit(line[j])) {
            buffer += line[j];
            coords.push_back({i, j});
        }
        else {
            if (buffer.length() > 0) {
                numbers.push_back({std::stoi(buffer), coords});
                buffer = "";
                coords.clear();
            }
        }
    }

    if (buffer.length() > 0) numbers.push_back({std::stoi(buffer), coords});
}

bool check_coords(std::vector<Coord>& coords, std::vector<std::string>& gears) {
    std::vector<Coord> dirs = {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1},
        {1,1},
        {1,-1},
        {-1,1},
        {-1,-1}
    };

    for (Coord coord : coords) {
        for (Coord tmp : dirs) {
            Coord new_coord = {coord.first + tmp.first, coord.second + tmp.second};

            if (std::find(coords.begin(), coords.end(), new_coord) == coords.end()) {
                if (new_coord.first >= 0 && new_coord.first < gears.size() && 
                    new_coord.second >= 0 && new_coord.second < gears.size()) {
                    if (gears[new_coord.first][new_coord.second] != '.' && 
                        !isdigit(gears[new_coord.first][new_coord.second])) 
                        return true;
                }
            }     
        }
    }

    return false;
}

bool next_to_sym(std::pair<int, std::vector<Coord>>& number, std::vector<std::string>& gears) {
    return (check_coords(number.second, gears))? true : false;
}

int part1(std::string file_path) {
    std::ifstream input("input.txt");
    std::string line;
    std::vector<std::string> gears;

    std::vector<std::pair<int, std::vector<Coord>>> numbers;
    std::vector<std::vector<Coord>> stars_neighs;

    while (std::getline(input, line)) {
        gears.push_back(line);
    }

    for (int i = 0; i < gears.size(); ++i) {
        get_numbers(gears[i], i, numbers);
    }

    int result = 0;
    for (int i = 0; i < numbers.size(); ++i) {
        if (next_to_sym(numbers[i], gears)) {
            result += numbers[i].first;
        }
    }

    return result;
}

void get_stars(std::string line, int i, std::vector<Coord>& stars) {
    for (int j = 0; j < line.size(); ++j) {
        if (line[j] == '*') stars.push_back({i, j});
    }
}

bool contains_coord(std::pair<int, std::vector<Coord>> number, Coord coord) {
    return std::find(number.second.begin(), number.second.end(), coord) != number.second.end();
}

std::vector<int> count_num_neighs(Coord star, 
                    std::vector<std::pair<int, std::vector<Coord>>> numbers,
                    std::vector<std::string>& gears) {
    std::set<int> found_nums;

    std::vector<Coord> dirs = {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1},
        {1,1},
        {1,-1},
        {-1,1},
        {-1,-1}
    };

    for (Coord tmp : dirs) {
        Coord new_coord = {star.first + tmp.first, star.second + tmp.second};

        if (new_coord.first >= 0 && new_coord.first < gears.size() && 
            new_coord.second >= 0 && new_coord.second < gears.size()) {
            for (std::pair<int, std::vector<Coord>> number : numbers) {
                if (contains_coord(number, new_coord)) found_nums.insert(number.first);
            }
        }
    }

    std::vector<int> result(found_nums.begin(), found_nums.end());
    return result;
}

int part2(std::string file_path) {
    std::ifstream input(file_path);
    std::string line;
    std::vector<std::string> gears;

    std::vector<std::pair<int, std::vector<Coord>>> numbers;
    std::vector<Coord> stars;

    while (std::getline(input, line)) {
        gears.push_back(line);
    }

    for (int i = 0; i < gears.size(); ++i) {
        get_numbers(gears[i], i, numbers);
        get_stars(gears[i], i, stars);
    }

    int result = 0;
    for (int i = 0; i < stars.size(); ++i) {
        std::vector<int> nums = count_num_neighs(stars[i], numbers, gears);
        if (nums.size() == 2) result += nums[0]*nums[1];
    }

    return result;
}