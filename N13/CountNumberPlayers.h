#pragma once
#include <string>
#include "word2.h"
class CountNumberPlayers
{
public:
	void screen();
	void import();
	int Count();
	void word(word2& t, std::string, float, float);
private:
	sf::RenderWindow Window;
	sf::Texture image;
	sf::Sprite visual;
	int n = 4;
	word2 p2, p3, p4, p5, p6;
	//word2 t;
};

