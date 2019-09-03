//
// Created by Agata Parietti on 2019-09-03.
//

#include "Score.h"

Score::Score(Game *game): game(game), point(0), lives(0) {
    attach();
}

void Score::update() {
    point = game->getScore();
    lives = game->getLives();
}

void Score::attach() {
    game->subscribe(this);
}

void Score::detach() {
    game->unsubscribe(this);
}
