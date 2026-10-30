#pragma once
#include <SFML/Graphics.hpp>
#include "word2.h"
#include <string>
class Choiceboard
{
public:
	void import(int x, int y, std::string str1, std::string str2, std::string str3);
	bool Call(sf::RenderWindow& Window, sf::Event& event);
	bool Raise(sf::RenderWindow& Window, sf::Event& event);
	bool Foldthishand(sf::RenderWindow& Window, sf::Event& event);
	void draw(sf::RenderWindow& Window);
	void update(int x, int y, std::string str1, std::string str2, std::string str3);
	sf::RectangleShape& getinputbox() { return inputbox; }
	word2& getTime() { return FOLDTHISHAND; }
	word2& getCALL() { return CALL; }
	word2& getRAISE() { return RAISE; }
	word2& getFOLDTHISHAND() { return FOLDTHISHAND; }
	/*void updateForPlayer();*/
private:
	sf::Sprite blackboard;
	word2 CALL;
	word2 RAISE;
	word2 FOLDTHISHAND;
	sf::Texture item;
	std::string text;
	sf::Text Textprint;
	sf::Font font;
	sf::RectangleShape inputbox;
};

