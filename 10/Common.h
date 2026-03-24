#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

using namespace std;


const int MAP_HEIGHT = 30;
const int MAP_WIDTH = 80;


const int WIN_COIN_BASE = 1000;


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

enum Direction { UP, DOWN, LEFT, RIGHT, NONE };

struct Point {
    int r, c;
    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }
};

#endif