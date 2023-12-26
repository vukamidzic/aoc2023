#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

typedef std::pair<int, int> Pos;

bool in(char c, std::vector<char> v) {
    return std::find(v.begin(), v.end(), c) != v.end();
}

bool contains(std::vector<Pos> v, Pos p) {
    for (auto i : v) {
        if (i.first == p.first && i.second == p.second) return true;
    }

    return false;
}

int visit(Pos start, std::vector<std::string>& maze) {
    std::vector<Pos> visited;
    std::queue<Pos> q;
    visited.push_back(start);
    q.push(start);

    while (!q.empty()) {
        Pos curr = q.front(); 
        q.pop();

        int r = curr.first, c = curr.second;

        if (r > 0 && in(maze[r][c], {'S', '|', 'J', 'L'}) && in(maze[r-1][c], {'|', 'F', '7'})
            && !contains(visited, {r-1,c})) {
            visited.push_back({r-1,c});
            q.push({r-1,c});
        }
        if (r < (int)maze.size()-1 && in(maze[r][c], {'S', '|', 'F', '7'}) && in(maze[r+1][c], {'|', 'J', 'L'})
            && !contains(visited, {r+1,c})) {
            visited.push_back({r+1,c});
            q.push({r+1,c});
        }
        if (c > 0 && in(maze[r][c], {'S', '-', '7', 'J'}) && in(maze[r][c-1], {'-', 'F', 'L'})
            && !contains(visited, {r,c-1})) {
            visited.push_back({r,c-1});
            q.push({r,c-1});
        }
        if (c < (int)maze[0].size()-1 && in(maze[r][c], {'S', '-', 'F', 'L'}) && in(maze[r][c+1], {'-', 'J', '7'})
            && !contains(visited, {r,c+1})) {
            visited.push_back({r,c+1});
            q.push({r,c+1});
        }
    }

    return visited.size()/2;
}

int part1(std::string filepath) {
    std::ifstream input(filepath);
    std::string line;
    std::vector<std::string> maze;

    while (std::getline(input, line)) {
        maze.push_back(line);
    }

    Pos start;
    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[0].size(); ++j) {
            if (maze[i][j] == 'S') {
                start = {i, j};
                break;
            }
        }
    }

    return visit(start, maze);
}