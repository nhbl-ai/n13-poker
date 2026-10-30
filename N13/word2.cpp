#include "word2.h"

void word2::play(std::string chu , float x , float y )
{
	font.loadFromFile("Tajawal-ExtraLight.ttf");
	text.setFont(font);
	text.setString(chu);
	text.setCharacterSize(70); 
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(x , y);
}

void word2::set(std::string chu, int size, float x, float y) {
    font.loadFromFile("Tajawal-ExtraLight.ttf");
    text.setFont(font);
    text.setString(chu);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(x, y);
}

