#include <iostream>
#include <ncurses.h>
#include "grid.hpp"

using namespace std;
using namespace grid;

int getKey(int *k) {
    timeout(150);
    *k = getch();
    return (*k);
}
void game() {
    initscr();
    printGrid();
    int key; int *p = &key; // keys for user input

    while (getKey(p) != 27 && alive) {
        clear();
        if (key != -1) {
            switch (key) {
                case 119:
                    if (snake::facing != SOUTH) {nextAction = &(snake::runNorth);}
                    break;
                case 115:
                    if (snake::facing != NORTH) {nextAction = &(snake::runSouth);}
                    break;
                case 97:
                    if (snake::facing != EAST) {nextAction = &(snake::runWest);}
                    break;
                case 100:
                    if (snake::facing != WEST) {nextAction = &(snake::runEast);}
                    break;
                default:
                    break;
            }
        } else {
            (*nextAction)();
            if (!alive) {endwin(); cout << "SCORE: " << score << endl; return;}
        }
        printGrid();
    }
    endwin();
}
int main() {
    initGrid();

    vals[-1] = ' '; vals[1] = '@'; vals[0] = 'o'; vals[2] = '%'; vals[-2] = '-';
    int& start = getP(head_start[0], head_start[1]);
    start = 1;
    snake::all.push_back(vector<int>{head_start[0], head_start[1]});
    snake::head_pos_x = snake::all[0][0]; snake::head_pos_y = snake::all[0][1];
    snake::addPart(2);
    newApple();

    game();

    return 0;
}
