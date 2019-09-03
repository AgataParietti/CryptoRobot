//
// Created by Agata Parietti on 2019-09-03.
//

#ifndef CRYPTOROBOT_SCORE_H
#define CRYPTOROBOT_SCORE_H

#include <fstream>
#include <iostream>

#include "Game.h"
#include "Observer.h"

class Score: public Observer {
public:
    Score (Game* game);
    virtual ~Score() {detach();}

    virtual void update() override;
    virtual void attach() override;
    virtual void detach() override;

protected:
    unsigned int point, lives;
    Game* game;
};

#endif //CRYPTOROBOT_SCORE_H
