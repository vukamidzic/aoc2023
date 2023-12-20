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

void toSouth(std::vector<std::string>& rocks) {
    int n = (int)rocks.size();
    for (int i = n-2; i >= 0; --i) {
        for (int j = 0; j < (int)rocks[0].size(); ++j) {
            if (rocks[i][j] == 'O') {
                int y = i+1;
                while (y < n) {
                    if (rocks[y][j] == 'O' || rocks[y][j] == '#') break; 
                    y++;
                }
                if (y >= n) y = n-1;
                else y--;
                char tmp = rocks[y][j];
                rocks[y][j] = rocks[i][j];
                rocks[i][j] = tmp;
            }
        }
    }
}

void toEast(std::vector<std::string>& rocks) {
    int n = (int)rocks[0].size();
    for (int j = n-2; j >= 0; --j) {
        for (int i = 0; i < (int)rocks.size(); ++i) {
            if (rocks[i][j] == 'O') {
                int y = j+1;
                while (y < n) {
                    if (rocks[i][y] == 'O' || rocks[i][y] == '#') break; 
                    y++;
                }
                if (y >= n) y = n-1;
                else y--;
                char tmp = rocks[i][y];
                rocks[i][y] = rocks[i][j];
                rocks[i][j] = tmp;
            }
        }
    }
}

void toWest(std::vector<std::string>& rocks) {
    int n = (int)rocks[0].size();
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < (int)rocks.size(); ++i) {
            if (rocks[i][j] == 'O') {
                int y = j-1;
                while (y >= 0) {
                    if (rocks[i][y] == 'O' || rocks[i][y] == '#') break; 
                    y--;
                }
                if (y < 0) y = 0;
                else y++;
                char tmp = rocks[i][y];
                rocks[i][y] = rocks[i][j];
                rocks[i][j] = tmp;
            }
        }
    }
}

void cycle(std::vector<std::string>& rocks) {
    toNorth(rocks);
    toWest(rocks);
    toSouth(rocks); 
    toEast(rocks);
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

int part2(std::string filepath) {
    std::ifstream input(filepath);
    std::string line;
    std::vector<std::string> rocks;

    while (std::getline(input, line)) {
        rocks.push_back(line);
    }

    std::vector<std::string> seen = rocks;
    for (int i = 0; i < 1000000000; ++i) {
        cycle(rocks);
        if (seen == rocks) break;
        else seen = rocks;
    }

    int factor = (int)rocks.size(), result = 0;
    for (std::string line : rocks) {
        result += std::count(line.begin(), line.end(), 'O')*factor;
        factor--;
    }

    return result;
}

int main(void) {
    std::cout << part2("input.txt") << std::endl;

    return 0;
}