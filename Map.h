//
// Created by Agata Parietti on 2019-07-10.
//

#ifndef CRYPTOROBOT_MAP_H
#define CRYPTOROBOT_MAP_H

#include <SFML/Graphics.hpp>

class Map {
public:
    Map();
    Map(const std::string &Title, const sf::Vector2u &Size);
    ~Map() { map.close(); }

    void update();
    void clear();
    void draw(sf::Drawable &Drawable);
    void display();

    sf::RenderWindow *getRenderMap();
    bool isClosed() const { return closed; }
    const sf::Vector2u getMapSize() const;
    const std::string &getMapTitle() const;

private:
    sf::RenderWindow map;
    sf::Vector2u mapSize;
    std::string mapTitle;
    bool closed = false;
};

#endif //CRYPTOROBOT_MAP_H