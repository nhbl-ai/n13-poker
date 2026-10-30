#include "table.h"
#include "Login.h"
#include "Database.h"
#include <iostream>
#include "Icongame.h"
#include <SFML/Audio.hpp>
#include "CountNumberPlayers.h"
#include "word2.h"
#include "window.h"
#include "LoginWindow.h"
#include "pokerChooseGame.h"

extern sf::Sound click;
Login::Login() : Window(sf::VideoMode::getDesktopMode(), "Login" , sf::Style::Fullscreen), isUsernameActive(false), isPasswordActive(false) {
    font.loadFromFile("Tajawal-ExtraLight.ttf");
	Icongame x;
    x.windowseticon(Window);
	usernameLabel.setFont(font);
	usernameLabel.setString("Username:");
	usernameLabel.setCharacterSize(50);
	usernameLabel.setPosition(350, 150);
	usernameLabel.setFillColor(sf::Color::White);

	passwordLabel.setFont(font);
	passwordLabel.setString("Password:");
	passwordLabel.setCharacterSize(50);
	passwordLabel.setPosition(350, 350);
	passwordLabel.setFillColor(sf::Color::White);

	usernameBox.setSize(sf::Vector2f(350, 50));
	usernameBox.setPosition(350, 250);
	usernameBox.setFillColor(sf::Color::White);
	usernameBox.setOutlineColor(sf::Color::Black);
	usernameBox.setOutlineThickness(2);

	passwordBox.setSize(sf::Vector2f(350, 50));
	passwordBox.setPosition(350, 450);
	passwordBox.setFillColor(sf::Color::White);
	passwordBox.setOutlineColor(sf::Color::Black);
	passwordBox.setOutlineThickness(2);

	loginButton.setSize(sf::Vector2f(350, 60));
	loginButton.setPosition(350, 600);
	loginButton.setFillColor(sf::Color::Blue);

	loginButtonText.setFont(font);
	loginButtonText.setString("Login");
	loginButtonText.setCharacterSize(40);
	loginButtonText.setPosition(460, 605);
	loginButtonText.setFillColor(sf::Color::White);

	errorMessage.setFont(font);
	errorMessage.setCharacterSize(20);
	errorMessage.setFillColor(sf::Color::Red);
	errorMessage.setPosition(350, 720);
	errorMessage.setString("");

	showPasswordBox.setSize(sf::Vector2f(20, 20));
	showPasswordBox.setPosition(350, 520);
	showPasswordBox.setFillColor(sf::Color::White);

	showPasswordText.setFont(font);
	showPasswordText.setString("Show Password");
	showPasswordText.setCharacterSize(25);
	showPasswordText.setPosition(380, 510);
	showPasswordText.setFillColor(sf::Color::White);

    //goback.play("Go back", 100, 60);

	showPassword = false;

	// Load users from file
	users = loadUsers("users.txt");
}

void Login::run() {
import();  // Load resources
	while (Window.isOpen()) {
		render();
		update();  // Update logic
		processEvents();  // Process events
		Window.display();  // Display content
	}
}

void Login::processEvents() {
	sf::Event event;
    sf::Vector2i mousepos = sf::Mouse::getPosition(Window); 

	while (Window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			Window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
            /*if (goback.getText().getGlobalBounds().contains(mousepos.x, mousepos.y)) {
                Window.close();
                LoginWindow window;
                window.showMenu();
            }*/
			click.play();
			if (usernameBox.getGlobalBounds().contains(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)))) {
				isUsernameActive = true;
				isPasswordActive = false;
			}
			else if (passwordBox.getGlobalBounds().contains(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)))) {
				isUsernameActive = false;
				isPasswordActive = true;
			}
			else if (showPasswordBox.getGlobalBounds().contains(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)))) {
				showPassword = !showPassword;
				showPasswordBox.setFillColor(showPassword ? sf::Color::Blue : sf::Color::White);
			}
			else if (loginButton.getGlobalBounds().contains(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)))) {
				if (verifyUser(usernameInput, passwordInput)) {
					std::cout << "Login successful!" << std::endl;
					Window.close();
					
					pokerChooseGame menu;
					menu.showMenu();
					/*TableWindow menu;
					int n = 0;
					GameState currentState = MENU;

					menu.showMenu(currentState);
					CountNumberPlayers x;
					if (currentState == GAME_VS_PLAYER) {
						n = x.Count();
						menu.showGameTablePVP(n);
					}
					else if (currentState == GAME_VS_BOT) {
						n = x.Count();
						menu.showGameTablePVE(n);
					}*/
				}
				else {
					errorMessage.setString("Invalid username or password!");
				}
			}
			else {
				isUsernameActive = false;
				isPasswordActive = false;
			}
		}
		else if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == '\b') {
				if (isUsernameActive && !usernameInput.empty()) {
					usernameInput.pop_back();
				}
				else if (isPasswordActive && !passwordInput.empty()) {
					passwordInput.pop_back();
				}
			}
			else if (event.text.unicode < 128) {
				if (isUsernameActive) {
					usernameInput += static_cast<char>(event.text.unicode);
				}
				else if (isPasswordActive) {
					passwordInput += static_cast<char>(event.text.unicode);
				}
			}
		}
	}
}


void Login::update() {
	usernameString.setFont(font);
	usernameString.setString(usernameInput);
	usernameString.setCharacterSize(30);
	usernameString.setPosition(350, 250);
	usernameString.setFillColor(sf::Color::Black);
	Window.draw(usernameString);

	std::string hiddenPassword = showPassword ? passwordInput :
	std::string(passwordInput.length(), '*');

	passwordString.setFont(font);
	passwordString.setString(hiddenPassword);
	passwordString.setCharacterSize(30);
	passwordString.setPosition(350, 450);
	passwordString.setFillColor(sf::Color::Black);
	Window.draw(passwordString);

	if (isUsernameActive || isPasswordActive || isConfirmPasswordActive) {
		sf::RectangleShape cursor(sf::Vector2f(2, 30));
		cursor.setFillColor(sf::Color::Black);
		if (isUsernameActive) {
			cursor.setPosition(350 + usernameString.getGlobalBounds().width, 250);
		}
		else if (isPasswordActive) {
			cursor.setPosition(350 + passwordString.getGlobalBounds().width, 450);
		}
		if (cursorClock.getElapsedTime().asSeconds() >= 0.5f) {
			cursorClock.restart();
		}
		if (cursorClock.getElapsedTime().asSeconds() < 0.25f) {
			Window.draw(cursor);
		}
	}
}

void Login::render() {
	Window.clear();
	Window.draw(visual);
	Window.draw(usernameLabel);
	Window.draw(passwordLabel);
	Window.draw(usernameBox);
	Window.draw(passwordBox);
	Window.draw(loginButton);
	Window.draw(loginButtonText);
	Window.draw(showPasswordBox);
	Window.draw(showPasswordText);
	Window.draw(errorMessage);
	
}

void Login::import() {
	image.loadFromFile("background.jpg");
	visual.setTexture(image);
	visual.setScale(
		Window.getSize().x / visual.getGlobalBounds().width,
		Window.getSize().y / visual.getGlobalBounds().height
	);
}

bool Login::verifyUser(const std::string& username, const std::string& password) {
	auto it = users.find(username);
	//saveUsernames(users, "player.txt");
	if (it != users.end() && it->second == password) {
		saveUsername(username, "player.txt"); // Ghi tên người dùng hiện tại
		return true;
	}
	return false;
	//return it != users.end() && it->second == password;
}

//bool Login::registerUser(const std::string& username, const std::string& password) {
//	if (users.find(username) == users.end()) {
//		users[username] = password;
//		saveUsers(users, "users.txt");
//		return true;
//	}
//	return false;
//}