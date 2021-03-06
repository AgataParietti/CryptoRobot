//
// Created by Agata Parietti on 2019-07-10.
//

#include "Map.h"

Map::Map() {
    map.create({1600, 1000}, "CryptoRobot");
    closed= false;
    mapSize = sf::Vector2u (1600, 1000);
    mapTitle = "CryptoRobot";
}

Map::Map(const std::string &Title, const sf::Vector2u &Size) {
    map.create({Size.x, Size.y}, Title);
    closed= false;
    mapSize = Size;
    mapTitle = Title;
}

void Map::update() {
    sf::Event event;
    while (map.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            closed = true;
    }
}

const sf::Vector2u Map::getMapSize() const {
    return mapSize;
}

void Map::clear() {
    map.clear(sf::Color::White);
}

void Map::draw(sf::Drawable &Drawable) {
    map.draw(Drawable);
}

void Map::display() {
    map.display();
}

sf::RenderWindow *Map::getRenderMap(){
    return &map;
}







