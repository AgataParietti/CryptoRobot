#include <SFML/Graphics.hpp>
#include <iostream>

//Prova per vedere se funziona la libreria SFML appena installata

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Font font;
    font.loadFromFile("Arial.ttf");
    if (!font.loadFromFile("Arial.ttf")) {
        std::cout<<"ERROR!"<<std::endl;
    }


    sf::Text text;
    text.setString("HELLO");
    text.setCharacterSize(30);
    text.setFont(font);
    text.setFillColor(sf::Color::Black);



    while (window.isOpen())
    {
        sf::Event event;
        while( window.pollEvent(event)) {
            if(event.type==sf::Event::Closed)
                window.close();

            window.clear(sf::Color::Yellow);
            window.draw(text);
            window.display();
        }
    }

    //return 0;
}
