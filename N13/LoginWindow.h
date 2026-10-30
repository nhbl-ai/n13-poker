#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Database.h" 

class LoginWindow {
public:
	/*LoginWindow();
	void run();*/
	void showMenu();
	 
private:
	

	sf::RenderWindow Window;
	sf::Font font;
	sf::Texture image;
	sf::Sprite visual;

	sf::RectangleShape mainLoginButton;
	sf::RectangleShape mainRegisterButton;
	sf::Text mainRegisterButtonText;
	sf::Text mainLoginButtonText; 

	/*bool isUsernameActive;
	bool isPasswordActive;
	bool isConfirmPasswordActive;
	bool isRegisterMode;
	bool isMainScreen;*/

	sf::Clock cursorClock;
};
