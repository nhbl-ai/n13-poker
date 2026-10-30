#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class title
{
public:
    void play();
    sf::Text& getText() { return text; }
private:
    sf::Text text;
    sf::Font font;
    std::string title_;
};
