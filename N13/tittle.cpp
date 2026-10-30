#include "tittle.h"
#include "word2.h"

void title::play() {
    font.loadFromFile("Tajawal-ExtraLight.ttf");
    text.setFont(font); 
    text.setString("POKER");
    text.setCharacterSize(200);  
    text.setFillColor(sf::Color::White); 
    text.setStyle(sf::Text::Bold);
    text.setPosition(150.f, 150.f);
}


