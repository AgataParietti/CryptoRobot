//
// Created by Agata Parietti on 2019-07-10.
//

#include "Map.h"


Map::Map(const std::string &Title, const sf::Vector2u &Size) {
    setup(Title, Size);
    //TODO background.setTexture();
}

void Map::setup(const std::string &title, const sf::Vector2u &size) {
    mapTitle = title;
    mapSize = size;
    map.setFramerateLimit(40);
    map.create({mapSize.x, mapSize.y}, mapTitle);
    map.clear(sf::Color::White);
    map.draw(background);
    map.display();
    closed = false;
}

void Map::update() {
    sf::Event event;
    while (map.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            map.close();
    }
}

const sf::RenderWindow &Map::getMap() const {
    return map;
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





