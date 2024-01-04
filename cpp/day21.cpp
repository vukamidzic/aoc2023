#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>

typedef std::pair<int, int> Position;

// const int MAX_STEPS = 6; for "test.txt"
const int MAX_STEPS = 64;

Position getStart(std::vector<std::string> maze) {
    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[0].size(); ++j) {
            if (maze[i][j] == 'S') return {j, i};
        }
    }

    return {};
}

bool canStep(Position next, std::vector<std::string>& maze) {
    return (
        next.first >= 0 && 
        next.first < (int)maze[0].size() && 
        next.second >= 0 && 
        next.second < (int)maze.size() &&
        maze[next.second][next.first] != '#'
    );
}

bool contains(std::set<std::pair<Position, int>>& visited, Position to_find) {
    for (auto it : visited) {
        if (it.first == to_find) 
            return true;
    }

    return false;
}

int BFS(std::vector<std::string>& maze) {
    std::queue<std::pair<Position, int>> q;
    std::set<std::pair<Position, int>> visited; 

    Position start = getStart(maze);
    q.push({start, 0});
    visited.insert({start, 0});

    std::vector<Position> neighs = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };

    while (!q.empty()) {
        Position curr = q.front().first;
        int curr_steps = q.front().second;
        q.pop();

        if (curr_steps > MAX_STEPS) continue;

        for (Position neigh : neighs) {
            Position next = {curr.first + neigh.first, curr.second + neigh.second};

            if (canStep(next, maze) && !contains(visited, next)) {
                q.push({next, curr_steps + 1});
                visited.insert({next, curr_steps + 1});
            }
        }
    }

    return std::count_if(visited.begin(), visited.end(), 
        [](auto a) {return a.second % 2 == MAX_STEPS % 2;}
    );
}

int part1(std::string filepath) {
    std::ifstream input(filepath);
    std::string line;
    std::vector<std::string> maze;

    while (std::getline(input, line)) {
        maze.push_back(line);
    }

    return BFS(maze);
}

int main(void) {
    std::cout << part1("input.txt") << std::endl;

    return 0;
}