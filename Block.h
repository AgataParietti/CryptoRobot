//
// Created by Agata Parietti on 2019-07-06.
//

#ifndef CRYPTOROBOT_BLOCK_H
#define CRYPTOROBOT_BLOCK_H

#include <SFML/Graphics.hpp>

class Block: public sf::Sprite {
public:
    Block();
    ~Block();

    bool getIsMoving() const;
    void setIsMoving();

    float getBlockSpeedY() const;

    void setBlockSpeedY(float blockSpeedY);

private:
    float blockSpeedY;
    bool isMoving;
};


#endif //CRYPTOROBOT_BLOCK_H
