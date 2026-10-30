#pragma once
#include <SFML/Graphics.hpp>
#include "Database.h"
#include <iostream>
#include <string>


class Login
{
public:
	Login();
	void run();
	void import();
	bool verifyUser(const std::string& username, const std::string& password);

private:
	sf::RenderWindow Window;
	sf::Font font;
	void processEvents();
	void update();
	void render();

	//Database db;
	//bool registerUser(const std::string& username, const std::string& password);

	sf::Text usernameLabel;
	sf::Text passwordLabel;
	sf::Text confirmPasswordLabel;
	sf::RectangleShape usernameBox;
	sf::RectangleShape passwordBox;
	sf::RectangleShape confirmPasswordBox;
	sf::Text usernameString;
	sf::Text passwordString;
	sf::Text confirmPasswordString;
	sf::Texture image;
	sf::Sprite visual;

	sf::RectangleShape loginButton;
	sf::Text loginButtonText;

	sf::Text errorMessage;

	std::string usernameInput;
	std::string passwordInput;
	std::unordered_map<std::string, std::string> users;

	sf::RectangleShape showPasswordBox;
	sf::Text showPasswordText;


	bool isUsernameActive;
	bool isPasswordActive;
	bool isConfirmPasswordActive;
	bool showPassword;

	sf::Clock cursorClock;
};
