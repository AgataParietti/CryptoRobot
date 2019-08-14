//
// Created by Agata Parietti on 2019-07-11.
//

#include "Game.h"
#include <chrono>
#include <thread>
#include <time.h>

int main() {
    Game game;

    int FPS = 30;
    int MS_PER_FRAME = 1 / FPS;

    while (!game.getMap()->isClosed()) {
        double start = clock() / CLOCKS_PER_SEC;
        game.update();
        game.render();
        std::this_thread::sleep_for(std::chrono::milliseconds((int) start + MS_PER_FRAME - (clock() / CLOCKS_PER_SEC)));
    }
}