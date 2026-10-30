#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Audio.hpp>
class window
{
public:
	void screen();
	void import();
	window();
	//------------------ Gia
	void option( sf::Event , float , float  );
	void leaderboard(sf::Event, float, float); 
	//-------------------
	void word(std::string , float , float );
    void credits(sf::Event, float, float);
	void quit(sf::Event event, float, float);


private:
	sf::RenderWindow Window; 
	sf::Texture image; 
	sf::Sprite visual;  
	int n = 4;
	//word2 t;
};

