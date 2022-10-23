#include <vector>
#include <map>
#include <random>
#include <list>

#pragma once

using namespace std;

namespace grid {
    enum DIRECTION {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };
    // Snake Grid
    int grid[32][64];
    int head_start[2] = {31, 15};
    int score = 0;
    map<int, char> vals;

    int& getP(int x, int y) {
        return (grid[y][x]);
    }
    bool isEmpty(int x, int y) {
        if (grid[y][x] == -1) {
            return true;
        } else {
            return false;
        }
    }
    class snake {
    public:
        static std::vector<vector<int>> all;
        static int head_pos_x; static int head_pos_y;
        static DIRECTION facing;
        static void move(DIRECTION dir, DIRECTION newdir, int x, int y);
        static void runNorth() {move(SOUTH, NORTH, snake::head_pos_x, snake::head_pos_y - 1);}
        static void runSouth() {move(NORTH, SOUTH, snake::head_pos_x, snake::head_pos_y + 1);}
        static void runEast() {move(WEST, EAST, snake::head_pos_x + 1, snake::head_pos_y);}
        static void runWest() {move(EAST, WEST, snake::head_pos_x - 1, snake::head_pos_y);}
        static void addPart(int t);
    };
    std::vector<vector<int>> snake::all = {};
    DIRECTION snake::facing = NORTH;
    int snake::head_pos_x = head_start[0]; int snake::head_pos_y = head_start[1];
    bool alive = true;
    auto nextAction = &(snake::runNorth);
    random_device tg; // Random Numbers
    uniform_int_distribution<int> rng_x(0,63);
    uniform_int_distribution<int> rng_y(0,31); // Explanation: auto rng_y = uniform_int_distribution<int>(0,63);
    int random_x() {return (rng_x(tg));} int random_y() {return (rng_y(tg));}

    void newHead(int x, int y) {
        getP(snake::all[0][0], snake::all[0][1]) = 0; // Head is now a snake part
        int& new_head = getP(x, y); // new head of snake
        getP(x, y) = 1; // sets new head to be head (1)
        vector<int> new_head_point = {x, y}; // new head point to be added into snake vector
        snake::all.insert(snake::all.begin(), new_head_point); // inserts new head point into snake vector
        vector<int> tail = snake::all[snake::all.size() - 1]; // tail of snake vector
        int& tail_map = getP(tail[0], tail[1]); // tail point on actual map
        tail_map = -1; // sets tail as empty point
        snake::all.pop_back(); // chops off tail from snake vector
        snake::head_pos_x = snake::all[0][0]; // new head x pos
        snake::head_pos_y = snake::all[0][1]; // new head y pos
    }
    bool isAvailable(int x, int y) {
        return (grid[y][x] == -1);
    }
    vector<int> lastPSnake() {
        return (snake::all[snake::all.size() - 1]);
    }
    // add directional checking for adding snake part
    void snake::addPart(int t = 1) {
        int modify_x = 0; int modify_y = 0;
        switch(snake::facing) {
            case NORTH: modify_y = 1; break;
            case SOUTH: modify_y = -1; break;
            case EAST: modify_x = -1; break;
            case WEST: modify_x = 1; break;
        }
        for (int i = 0; i < t; i++) {
            if (isAvailable(lastPSnake()[0] + modify_x, lastPSnake()[1] + modify_y)) {
                int& newPart = getP(lastPSnake()[0] + modify_x, lastPSnake()[1] + modify_y);
                newPart = 0; // sets it to be body part of snake
                snake::all.push_back(vector<int>{lastPSnake()[0] + modify_x, lastPSnake()[1] + modify_y});
            }
        }
    }
    void newApple() {
        int x = random_x(); int y = random_y();
        int& apple = getP(x, y);
        if (apple != -1) {
            newApple();
        } else {
            apple = 2;
        }
    }
    void eatApple(int x, int y) {
        newHead(x, y);
        snake::addPart(1);
        newApple();
        score++;
    }
    bool isApple(int x, int y) {
        return (grid[y][x] == 2);
    }
    void snake::move(DIRECTION dir, DIRECTION newdir, int x, int y) {
        if (snake::facing != dir) {
            if (isAvailable(x, y)) {
                newHead(x, y); // Add new head in appropriate direction
                snake::facing = newdir;
            } else if (isApple(x, y)) {
                eatApple(x, y);
            } else alive = false;
        }
    }
    void printGrid() { // prints out the grid
        int y;
        for (y = 0; y < 32; y++) {
            int x;
            for (x = 0; x < 64; x++) {
                printw("%c", vals[grid[y][x]]);
            }
            printw("\n");
        }
    }
    void initGrid() { // sets borders on the grid to dashes
        int y;
        for (y = 0; y < 32; y++) {
            int x;
            for (x = 0; x < 64; x++) {
                grid[y][x] = -1; grid[y][x] = -1;
                if (y == 0 || y == 31 || x == 0 || x == 63) {
                    grid[y][x] = -2;
                }
            }
        }
    }
}