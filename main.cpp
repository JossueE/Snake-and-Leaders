#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cctype>
#include <algorithm>
#include <string>
#include <random>

#include "myGame.h"
#include "tile.h"
int main() {
    srand(time(nullptr)); 

    MyGame game;
    game.start();

    return 0;
}

