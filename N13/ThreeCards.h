#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
//#include "CardDeck.h"
#include <string>
#include "word2.h"
#include <string>
#include <map>
#include <cmath>
#include "table.h"
class ThreeCards
{
public:
	void showMenu(GameState& currentState);
	void showGameTablePVP(int n);
	//void showGameTablePVE(int n);
	//void move(sf::Vector2f position, sf::Vector2f destination);
	//void Player(int n,int x, int y,std::string str);
	/*void setupCenterCards(sf::RenderWindow& gameWindow);
	void setupPlayerCards(sf::RenderWindow& gameWindow, int playerCount);
	void draw(sf::RenderWindow& gameWindow);*/
private:
	sf::RenderWindow Window;
	sf::Texture texture;
	sf::Sprite sprite;
	word2 player;
	/*std::vector<sf::RectangleShape> centerCards;
	std::vector<std::vector<sf::RectangleShape>> playerCardSlots; */
	/*std::vector<Card> playerCards;
	std::vector<Card> botCards;*/
};

