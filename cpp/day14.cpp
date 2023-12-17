#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void toNorth(std::vector<std::string>& rocks) {
    for (int i = 1; i < (int)rocks.size(); ++i) {
        for (int j = 0; j < (int)rocks[0].size(); ++j) {
            if (rocks[i][j] == 'O') {
                int y = i-1;
                while (y >= 0) {
                    if (rocks[y][j] == 'O' || rocks[y][j] == '#') break; 
                    y--;
                }
                if (y < 0) y = 0;
                else y++;
                char tmp = rocks[y][j];
                rocks[y][j] = rocks[i][j];
                rocks[i][j] = tmp;
            }
        }
    }
}

int part1(std::string filepath) {
    std::ifstream input(filepath);
    std::string line;
    std::vector<std::string> rocks;

    while (std::getline(input, line)) {
        rocks.push_back(line);
    }

    toNorth(rocks);
    int factor = (int)rocks.size(), result = 0;

    for (std::string line : rocks) {
        result += std::count(line.begin(), line.end(), 'O')*factor;
        factor--;
    }

    return result;
}