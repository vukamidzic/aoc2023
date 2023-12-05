#include <ctype.h>

#include <iostream>
#include <fstream>
#include <vector>
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

int main(void) {
    std::cout << part1("input.txt") << std::endl;

    return 0;
}