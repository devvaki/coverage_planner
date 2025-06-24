#include "planner.h"
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <iostream>

//vertical slice of free space cell
struct Cell {
    std::vector<cv::Point> points;
};

// Comparator for sorting point in maps and sets
struct PointCompare {
    bool operator()(const cv::Point& a, const cv::Point& b) const {
        return (a.y < b.y) || (a.y == b.y && a.x < b.x);
    }
};

//Priority queue comparator
struct PQCompare {
    bool operator()(const std::pair<int, cv::Point>& a, const std::pair<int, cv::Point>& b) const {
        return a.first > b.first; // min-heap by cost
    }
};

// Check if a cell is inside the map and free
static bool isFree(const cv::Mat& map, int x, int y) {
    return x >= 0 && x < map.cols && y >= 0 && y < map.rows && map.at<uchar>(y, x) < 100;
}

// Boustrophedon decomposition: slice the map vertically into Cells
static std::vector<Cell> decompose(const cv::Mat& map) {
    int rows = map.rows, cols = map.cols;
    std::vector<Cell> cells;
    std::vector<std::pair<int,int>> prev;

    for (int x = 0; x < cols; ++x) {
        std::vector<std::pair<int,int>> curr;
        bool inFree = false; int sy = 0;
        
// Identify vertical free intervals in this column
        for (int y = 0; y < rows; ++y) {
            if (!inFree && map.at<uchar>(y,x) < 100) { inFree = true; sy = y; }
            else if (inFree && map.at<uchar>(y,x) >= 100) {
                inFree = false; curr.emplace_back(sy, y-1);
            }
        }
        if (inFree) curr.emplace_back(sy, rows-1);

// If structure changed, create new cells
        if (curr != prev) {
            for (auto& iv : curr) {
                Cell c;
                for (int y = iv.first; y <= iv.second; ++y)
                    c.points.emplace_back(x, y);
                cells.push_back(c);
            }
        } else { //Else, extend existing cells horizontally
            int idx = cells.size() - curr.size();
            for (size_t i = 0; i < curr.size(); ++i) {
                for (int y = curr[i].first; y <= curr[i].second; ++y)
                    cells[idx + i].points.emplace_back(x, y);
            }
        }
        prev = curr;
    }
    return cells;
}

// Standard 4-directional A* search to connect two points
static std::vector<cv::Point> astar(const cv::Mat& map, cv::Point s, cv::Point g) {
    using PQElem = std::pair<int, cv::Point>;
    std::priority_queue<PQElem, std::vector<PQElem>, PQCompare> open;
    std::map<cv::Point, cv::Point, PointCompare> came_from;
    std::set<cv::Point, PointCompare> closed;

// Manhattan distance heuristic
    auto heuristic = [](cv::Point a, cv::Point b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    };

    open.emplace(0, s);
    came_from[s] = s;

    std::vector<cv::Point> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

    while (!open.empty()) {
        auto [cost, curr] = open.top(); open.pop();
        if (curr == g) {
            std::vector<cv::Point> path;
            while (!(curr == s)) {
                path.push_back(curr);
                curr = came_from[curr];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        if (!closed.insert(curr).second) continue;

        for (auto& d : dirs) {
            cv::Point nb = curr + d;
            if (!isFree(map, nb.x, nb.y) || closed.count(nb)) continue;
            if (!came_from.count(nb)) {
                came_from[nb] = curr;
                open.emplace(heuristic(nb, g), nb);
            }
        }
    }
    return {};
}

// Sweep a cell in boustrophedon pattern, alternating row wise or column wise
static std::vector<cv::Point> sweepCell(const Cell& c) {
    std::map<int,std::vector<int>> colmap;
    for (auto& p : c.points) colmap[p.x].push_back(p.y);

    std::vector<cv::Point> path;
    bool rev = false;
    for (auto& [x, ys] : colmap) {
        std::sort(ys.begin(), ys.end());
        if (rev) std::reverse(ys.begin(), ys.end());
        for (int y : ys) path.emplace_back(x,y);
        rev = !rev;
    }
    return path;
}

// Main function: Plan full coverage path across all decomposed cells
std::vector<cv::Point> planCoverage(const cv::Mat& map) {
    
    auto cells = decompose(map);
    std::vector<cv::Point> path;
    if (cells.empty()) return path;

// Starting point
    cv::Point last = cells[0].points[0];
    for (auto& c : cells) {
        auto sweep = sweepCell(c);
        if (!path.empty()) {
            auto jump = astar(map, last, sweep.front()); //Connect last cell to current cell
            path.insert(path.end(), jump.begin(), jump.end());

        }
        path.insert(path.end(), sweep.begin(), sweep.end());

        last = sweep.back();
    }
    return path;
}
