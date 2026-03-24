#include "GameEngine.h"
#include <iostream>

using namespace std;

int main() {
 
    cout << "\033[?25l";
    
    GameEngine game;
    game.run();

 
    cout << "\033[?25h";
    return 0;
}