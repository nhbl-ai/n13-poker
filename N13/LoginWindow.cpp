#include "LoginWindow.h"
#include <iostream>
#include "table.h"
#include "Login.h"
#include "Register.h"
#include "Database.h" 
#include "Icongame.h"
#include <SFML/Audio.hpp>
#include "word2.h"
#include "window.h"

extern sf::Sound click;
void LoginWindow::showMenu() {
	sf::RenderWindow account(sf::VideoMode::getDesktopMode(), "Account" , sf::Style::Fullscreen);
	Icongame x;
	x.windowseticon(account);
	font.loadFromFile("Tajawal-ExtraLight.ttf");
	image.loadFromFile("background.jpg");
	visual.setTexture(image);
	visual.setScale(
		account.getSize().x / visual.getGlobalBounds().width,
		account.getSize().y / visual.getGlobalBounds().height
	);

	
	mainLoginButton.setSize(sf::Vector2f(270, 70));
	mainLoginButton.setPosition(170, 445);
	mainLoginButton.setFillColor(sf::Color::White);

	mainLoginButtonText.setFont(font);
	mainLoginButtonText.setString("Login");
	mainLoginButtonText.setCharacterSize(70);
	mainLoginButtonText.setPosition(170, 430);
	mainLoginButtonText.setFillColor(sf::Color::Black);

	mainRegisterButton.setSize(sf::Vector2f(270, 70));
	mainRegisterButton.setPosition(170, 545);
	mainRegisterButton.setFillColor(sf::Color::White);

	mainRegisterButtonText.setFont(font);
	mainRegisterButtonText.setString("Register");
	mainRegisterButtonText.setCharacterSize(70);
	mainRegisterButtonText.setPosition(170, 530);
	mainRegisterButtonText.setFillColor(sf::Color::Black);

	word2 goback;  
	goback.play("Go back", 100, 60);

	while (account.isOpen()) {
		sf::Event event;
		sf::Vector2i mousepos = sf::Mouse::getPosition(account);

		while (account.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				account.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				click.play();
				if (goback.getText().getGlobalBounds().contains(mousepos.x, mousepos.y)) {
					account.close();
					window newwindow;
					newwindow;
				}

				if (mainLoginButton.getGlobalBounds().contains(account.mapPixelToCoords(sf::Mouse::getPosition(account)))) {
					account.close();
					Login login;
					login.run();  

				}
			
				else if (mainRegisterButton.getGlobalBounds().contains(account.mapPixelToCoords(sf::Mouse::getPosition(account)))) {
					account.close();
					Register regis; 
					regis.run();  

				}
			}
		}

		
		account.clear();
		account.draw(visual);
		account.draw(goback.getText());
		account.draw(mainLoginButton);
		account.draw(mainLoginButtonText);
		account.draw(mainRegisterButton);
		account.draw(mainRegisterButtonText);
		account.display();
	}
}