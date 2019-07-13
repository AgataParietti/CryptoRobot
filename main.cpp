//
// Created by Agata Parietti on 2019-07-11.
//

#include "Game.h"

int main() {
    Game game;

    while (!game.getMap()->isClosed()) {
        game.update();
        game.render();
    }
}