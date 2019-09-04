//
// Created by Agata Parietti on 2019-07-06.
//

#ifndef CRYPTOROBOT_BLOCK_H
#define CRYPTOROBOT_BLOCK_H

#include <SFML/Graphics.hpp>

class Block: public sf::Sprite {
public:
    Block();
    ~Block() = default;

    bool getIsMoving() const;
    float getBlockSpeedY() const;

    void setIsMoving();
    void setBlockSpeedY(float blockSpeedY);

private:
    float blockSpeedY = 0.8;
    bool isMoving;
};


#endif //CRYPTOROBOT_BLOCK_H
