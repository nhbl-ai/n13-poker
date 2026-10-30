#include "Player.h"
//void Player::Money_loc(sf::RenderWindow& Window, int x, int y)
//{
//	tien.play("Money: " + std::to_string(money), x, y);
//	tien.getText().setCharacterSize(30);
//	tien.getText().setFillColor(sf::Color::Yellow);
//	//Window.draw(tien.getText());
//}
//void Player::Name_loc(sf::RenderWindow& Window, int x, int y)
//{
//	ten.play("Name: " + name, x, y);
//	ten.getText().setCharacterSize(30);
//	ten.getText().setFillColor(sf::Color::Green);
//	//Window.draw(ten.getText());
//}
void Player::run(sf::RenderWindow& Window, int x, int y, int money_input, std::string name_input, int& time)
{
	money = money_input;
	name = name_input;
	playerinformation.import(x, y, "Name: " + name, "Money: " + std::to_string(money), "Time: " + std::to_string(time));
}
void Player::draw(sf::RenderWindow& Window)
{
	playerinformation.draw(Window);
}
void Player::update(int x, int y, std::string name, int money, int& time)
{
	playerinformation.update(x, y, "Name: " + name, "Money: " + std::to_string(money), "Time: " + std::to_string(time));
	//playerinformation.getCALL().getText().setString(name);
	//playerinformation.getRAISE().getText().setString(std::to_string(money));
}