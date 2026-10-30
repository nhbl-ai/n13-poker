#pragma once
#include <SFML/Graphics.hpp> 
#include <string>
class word2
{
public:
	void play(std::string , float , float );
	void set(std::string, int size, float, float);

	sf::Text& getText() { return text; }
private:
	sf::Font font;
	sf::Text text;
};

