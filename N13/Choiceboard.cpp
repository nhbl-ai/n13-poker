#include "Choiceboard.h"
#include "table.h"
#include "word2.h"	
#include <iostream>
void Choiceboard::import(int x, int y, std::string str1, std::string str2, std::string str3)
{
	inputbox.setFillColor(sf::Color::Transparent);
	item.loadFromFile("blackboard.jpg");
	blackboard.setTexture(item);
	blackboard.setPosition(x, y);
	blackboard.setScale(0.5f, 0.5f);
	font.loadFromFile("Tajawal-ExtraLight.ttf");
	sf::Vector2f position = blackboard.getPosition(); // Lấy vị trí của bảng
	sf::Vector2f size = sf::Vector2f(blackboard.getGlobalBounds().width, blackboard.getGlobalBounds().height); // Lấy kích thước của bảng
	CALL.play(str1, position.x + size.x / 2 - CALL.getText().getGlobalBounds().width / 2, position.y + size.y / 6 - 15);
	RAISE.play(str2, position.x + size.x / 2 - RAISE.getText().getGlobalBounds().width / 2, position.y + size.y / 2 - 15);
	FOLDTHISHAND.play(str3, position.x + size.x / 2 - FOLDTHISHAND.getText().getGlobalBounds().width / 2, position.y + 5 * size.y / 6 - 15);
	CALL.getText().setCharacterSize(30);
	RAISE.getText().setCharacterSize(30);
	FOLDTHISHAND.getText().setCharacterSize(30);
}
bool Choiceboard::Call(sf::RenderWindow& Window, sf::Event& event)
{
	sf::Vector2i mousepos = sf::Mouse::getPosition(Window);
	if (CALL.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
	{
		return true;
	}
	return false;
}
bool Choiceboard::Raise(sf::RenderWindow& Window, sf::Event& event)
{
	sf::Vector2i mousepos = sf::Mouse::getPosition(Window);
	if (RAISE.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
	{
		return true;
	}
	return false;
}
bool Choiceboard::Foldthishand(sf::RenderWindow& Window, sf::Event& event)
{
	sf::Vector2i mousepos = sf::Mouse::getPosition(Window);
	if (FOLDTHISHAND.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
	{
		return true;
	}
	return false;
}
void Choiceboard::draw(sf::RenderWindow& Window)
{
	Window.draw(blackboard);
	Window.draw(CALL.getText());
	Window.draw(RAISE.getText());
	Window.draw(FOLDTHISHAND.getText());
	//Window.display();
}
//void Choiceboard::update()
//{
//	sf::Vector2f position = blackboard.getPosition();
//	sf::Vector2f size = sf::Vector2f(blackboard.getGlobalBounds().width, blackboard.getGlobalBounds().height);
//
//	CALL.getText().setPosition(position.x + size.x / 2 - CALL.getText().getGlobalBounds().width / 2, position.y + size.y / 6 - 15);
//	RAISE.getText().setPosition(position.x + size.x / 2 - RAISE.getText().getGlobalBounds().width / 2, position.y + size.y / 2 - 15);
//	FOLDTHISHAND.getText().setPosition(position.x + size.x / 2 - FOLDTHISHAND.getText().getGlobalBounds().width / 2, position.y + 5 * size.y / 6 - 15);
//}
void Choiceboard::update(int x, int y, std::string s1, std::string s2, std::string s3) {
	blackboard.setPosition(x, y);
	sf::Vector2f position = blackboard.getPosition();
	sf::Vector2f size = sf::Vector2f(blackboard.getGlobalBounds().width, blackboard.getGlobalBounds().height);
	//inputbox.setFillColor(sf::Color::Transparent);
	CALL.getText().setString(s1);
	RAISE.getText().setString(s2);
	FOLDTHISHAND.getText().setString(s3);
	CALL.getText().setPosition(position.x + 10, position.y + size.y / 6 - 15);
	RAISE.getText().setPosition(position.x + 10, position.y + size.y / 2 - 15);
	FOLDTHISHAND.getText().setPosition(position.x + 10, position.y + 5 * size.y / 6 - 15);
}

