#pragma once
#include <string>
#include "word2.h"
#include "Choiceboard.h"
class Player
{
public:
	Choiceboard& getPlayerinformation() { return playerinformation; }
	/*void Money_loc(sf::RenderWindow& Window, int x, int y);
	void Name_loc(sf::RenderWindow& Window, int x, int y);*/
	void run(sf::RenderWindow& Window, int x, int y, int money_input, std::string name_input, int& time);
	void draw(sf::RenderWindow& Window);
	void update(int x, int y, std::string name, int money, int& time);
private:
	int money;
	std::string name;
	word2 tien;
	word2 ten;
	Choiceboard playerinformation;
};

