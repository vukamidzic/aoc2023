#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

typedef enum Direction {
    LEFT, RIGHT, UP, DOWN
} Direction;

typedef struct Coord {
    Direction dir;
    int r;
    int c;
} Coord;

#define COORD(d,r,c) (Coord){(d), (r), (c)}

bool contains(std::vector<Coord> v, Coord cod) {
    for (auto i : v) {
        if (i.r == cod.r && i.c == cod.c && i.dir == cod.dir)
            return true;
    }

    return false;
}

void BFS(std::vector<std::string>& field, std::vector<std::string>& tmp) {
    int cnt = 0;
    std::vector<Coord> seen;
    std::queue<Coord> q;
    q.push((Coord) {.dir = RIGHT, .r = 0, .c = 0});

    while (!q.empty()) {
        Coord curr = q.front(); 
        q.pop();

        if (curr.r < 0 || curr.r >= (int)field.size() || curr.c < 0 || curr.c >= (int)field[0].size()) continue;
        if (contains(seen, curr)) continue;
        seen.push_back(curr);
        
        char c = field[curr.r][curr.c];
        tmp[curr.r][curr.c] = '#';
        switch (c) {
            case '-' : {
                if (curr.dir != LEFT && curr.dir != RIGHT) {
                    q.push(COORD(LEFT, curr.r, curr.c-1));
                    q.push(COORD(RIGHT, curr.r, curr.c+1));
                }
                else if (curr.dir == LEFT) {
                    q.push(COORD(LEFT, curr.r, curr.c-1));
                }
                else {
                    q.push(COORD(RIGHT, curr.r, curr.c+1));
                }
                break;
            }
            case '|' : {
                if (curr.dir != UP && curr.dir != DOWN) {
                    q.push(COORD(UP, curr.r-1, curr.c));
                    q.push(COORD(DOWN, curr.r+1, curr.c));
                }
                else if (curr.dir == UP) {
                    q.push(COORD(UP, curr.r-1, curr.c));
                }
                else {
                    q.push(COORD(DOWN, curr.r+1, curr.c));
                }
                break;
            }
            case '\\' : {
                switch (curr.dir) {
                    case LEFT : {
                        q.push(COORD(UP, curr.r-1, curr.c));
                        break;
                    }
                    case RIGHT : {
                        q.push(COORD(DOWN, curr.r+1, curr.c));
                        break;
                    }
                    case UP : {
                        q.push(COORD(LEFT, curr.r, curr.c-1));
                        break;
                    }
                    case DOWN : {
                        q.push(COORD(RIGHT, curr.r, curr.c+1));
                        break;
                    }
                }
                break;
            }
            case '/' : {
                switch (curr.dir) {
                    case LEFT : {
                        q.push(COORD(DOWN, curr.r+1, curr.c));
                        break;
                    }
                    case RIGHT : {
                        q.push(COORD(UP, curr.r-1, curr.c));
                        break;
                    }
                    case UP : {
                        q.push(COORD(RIGHT, curr.r, curr.c+1));
                        break;
                    }
                    case DOWN : {
                        q.push(COORD(LEFT, curr.r, curr.c-1));
                        break;
                    }
                }
                break;
            }
            default : {
                switch (curr.dir) {
                    case LEFT : {
                        q.push(COORD(LEFT, curr.r, curr.c-1));
                        break;
                    }
                    case RIGHT : {
                        q.push(COORD(RIGHT, curr.r, curr.c+1));
                        break;
                    }
                    case UP : {
                        q.push(COORD(UP, curr.r-1, curr.c));
                        break;
                    }
                    case DOWN : {
                        q.push(COORD(DOWN, curr.r+1, curr.c));
                        break;
                    }
                }
                break;
            }
        }
    }
}

void BFS_with_dir(Direction startdir, int r, int c, std::vector<std::string>& field, std::vector<std::string>& tmp) {
    int cnt = 0;
    std::vector<Coord> seen;
    std::queue<Coord> q;
    q.push((Coord) {.dir = startdir, .r = r, .c = c});

    while (!q.empty()) {
        Coord curr = q.front(); 
        q.pop();

        if (curr.r < 0 || curr.r >= (int)field.size() || curr.c < 0 || curr.c >= (int)field[0].size()) continue;
        if (contains(seen, curr)) continue;
        seen.push_back(curr);
        
        char c = field[curr.r][curr.c];
        tmp[curr.r][curr.c] = '#';
        switch (c) {
            case '-' : {
                if (curr.dir != LEFT && curr.dir != RIGHT) {
                    q.push(COORD(LEFT, curr.r, curr.c-1));
                    q.push(COORD(RIGHT, curr.r, curr.c+1));
                }
                else if (curr.dir == LEFT) {
                    q.push(COORD(LEFT, curr.r, curr.c-1));
                }
                else {
                    q.push(COORD(RIGHT, curr.r, curr.c+1));
                }
                break;
            }
            case '|' : {
                if (curr.dir != UP && curr.dir != DOWN) {
                    q.push(COORD(UP, curr.r-1, curr.c));
                    q.push(COORD(DOWN, curr.r+1, curr.c));
                }
                else if (curr.dir == UP) {
                    q.push(COORD(UP, curr.r-1, curr.c));
                }
                else {
                    q.push(COORD(DOWN, curr.r+1, curr.c));
                }
                break;
            }
            case '\\' : {
                switch (curr.dir) {
                    case LEFT : {
                        q.push(COORD(UP, curr.r-1, curr.c));
                        break;
                    }
                    case RIGHT : {
                        q.push(COORD(DOWN, curr.r+1, curr.c));
                        break;
                    }
                    case UP : {
                        q.push(COORD(LEFT, curr.r, curr.c-1));
                        break;
                    }
                    case DOWN : {
                        q.push(COORD(RIGHT, curr.r, curr.c+1));
                        break;
                    }
                }
                break;
            }
            case '/' : {
                switch (curr.dir) {
                    case LEFT : {
                        q.push(COORD(DOWN, curr.r+1, curr.c));
                        break;
                    }
                    case RIGHT : {
                        q.push(COORD(UP, curr.r-1, curr.c));
                        break;
                    }
                    case UP : {
                        q.push(COORD(RIGHT, curr.r, curr.c+1));
                        break;
                    }
                    case DOWN : {
                        q.push(COORD(LEFT, curr.r, curr.c-1));
                        break;
                    }
                }
                break;
            }
            default : {
                switch (curr.dir) {
                    case LEFT : {
                        q.push(COORD(LEFT, curr.r, curr.c-1));
                        break;
                    }
                    case RIGHT : {
                        q.push(COORD(RIGHT, curr.r, curr.c+1));
                        break;
                    }
                    case UP : {
                        q.push(COORD(UP, curr.r-1, curr.c));
                        break;
                    }
                    case DOWN : {
                        q.push(COORD(DOWN, curr.r+1, curr.c));
                        break;
                    }
                }
                break;
            }
        }
    }
}

int countHashes(std::vector<std::string> tmp) {
    int cnt = 0;
    for (size_t i = 0; i < tmp.size(); ++i) {
        for (size_t j = 0; j < tmp[0].size(); ++j) {
            if (tmp[i][j] == '#') cnt++;
        }
    }

    return cnt;
}

int part1(std::string filepath) {
    std::ifstream input(filepath);
    std::string line;
    std::vector<std::string> field;

    while (std::getline(input, line)) {
        field.push_back(line);
    }

    std::vector<std::string> tmp = field;

    BFS(field, tmp);
    return countHashes(tmp);
}

int part2(std::string filepath) {
    std::ifstream input(filepath);
    std::string line;
    std::vector<std::string> field;

    while (std::getline(input, line)) {
        field.push_back(line);
    }

    int max_hashes = 0;

    for (size_t i = 0; i < field.size(); ++i) {
        std::vector<std::string> tmp1 = field;

        BFS_with_dir(RIGHT, i, 0, field, tmp1);
        max_hashes = std::max(max_hashes, countHashes(tmp1));

        std::vector<std::string> tmp2 = field;
        BFS_with_dir(LEFT, i, (int)field[0].size(), field, tmp2);
        max_hashes = std::max(max_hashes, countHashes(tmp2));
    }

    for (size_t j = 0; j < field[0].size(); ++j) {
        std::vector<std::string> tmp1 = field;

        BFS_with_dir(DOWN, 0, j, field, tmp1);
        max_hashes = std::max(max_hashes, countHashes(tmp1));

        std::vector<std::string> tmp2 = field;
        BFS_with_dir(UP, (int)field.size(), j, field, tmp2);
        max_hashes = std::max(max_hashes, countHashes(tmp2));
    }

    return max_hashes;
}

int main(void) {
    std::cout << part2("input.txt") << "\n";

    return 0;
}