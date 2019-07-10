//
// Created by Agata Parietti on 2019-07-10.
//

#ifndef CRYPTOROBOT_MAP_H
#define CRYPTOROBOT_MAP_H

#include <SFML/Graphics.hpp>

class Map: public sf::Window {
public:
    Map(const std::string &Title, const sf::Vector2u &Size);
    ~Map() override { map.close(); }
    void setup(const std::string &title, const sf::Vector2u &size);
    void update();

    const sf::RenderWindow &getMap() const;
    const sf::Vector2u getMapSize() const;

private:
    sf::RenderWindow map;
    sf:: Vector2u mapSize;
    std::string mapTitle;
    sf::Sprite background;
};

#endif //CRYPTOROBOT_MAP_H