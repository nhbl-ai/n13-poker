#include "Register.h"
#include "Database.h"
#include "table.h"
#include <iostream>
#include "Icongame.h"
#include <SFML/Audio.hpp>
#include "CountNumberPlayers.h"
#include <fstream>
#include "LoginWindow.h"
#include "word2.h"
#include "pokerChooseGame.h"

extern sf::Sound click;
//extern word2 goback;   

Register::Register() :Window(sf::VideoMode::getDesktopMode(), "Register" , sf::Style::Fullscreen),
isUsernameActive(false), isPasswordActive(false), isConfirmPasswordActive(false) {
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

confirmPasswordLabel.setFont(font);
confirmPasswordLabel.setString("Confirm Password:");
confirmPasswordLabel.setCharacterSize(50);
confirmPasswordLabel.setPosition(350, 550);
confirmPasswordLabel.setFillColor(sf::Color::White);

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

confirmPasswordBox.setSize(sf::Vector2f(350, 50));
confirmPasswordBox.setPosition(350, 650);
confirmPasswordBox.setFillColor(sf::Color::White);
confirmPasswordBox.setOutlineColor(sf::Color::Black);
confirmPasswordBox.setOutlineThickness(2);

registerButton.setSize(sf::Vector2f(350, 60));
registerButton.setPosition(350, 800);
registerButton.setFillColor(sf::Color::Blue);

registerButtonText.setFont(font);
registerButtonText.setString("Register");
registerButtonText.setCharacterSize(40);
registerButtonText.setPosition(460, 805);
registerButtonText.setFillColor(sf::Color::White);

errorMessage.setFont(font);
errorMessage.setCharacterSize(20);
errorMessage.setFillColor(sf::Color::Red);
errorMessage.setPosition(350, 900);
errorMessage.setString("");

showPasswordBox.setSize(sf::Vector2f(20, 20));
showPasswordBox.setPosition(350, 720);
showPasswordBox.setFillColor(sf::Color::White);

showPasswordText.setFont(font);
showPasswordText.setString("Show Password");
showPasswordText.setCharacterSize(25);
showPasswordText.setPosition(380, 710);
showPasswordText.setFillColor(sf::Color::White);

//goback.play("Go back", 100, 60);

users = loadUsers("users.txt");
}

void Register::run(){
    import();  // Load resources
    while (Window.isOpen()) {
        render();
        update();  // Update logic
        processEvents();  // Process events
        Window.display();  // Display content
    }
}

void Register::processEvents(){
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
			if (usernameBox.getGlobalBounds().contains(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)))) {
				isUsernameActive = true;
				isPasswordActive = false;
				isConfirmPasswordActive = false;
			}
			else if (passwordBox.getGlobalBounds().contains(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)))) {
				isUsernameActive = false;
				isPasswordActive = true;
				isConfirmPasswordActive = false;
			}
			else if (confirmPasswordBox.getGlobalBounds().contains(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)))) {
				isUsernameActive = false;
				isPasswordActive = false;
				isConfirmPasswordActive = true;
			}
			else if (showPasswordBox.getGlobalBounds().contains(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)))) {
				showPassword = !showPassword;
				showPasswordBox.setFillColor(showPassword ? sf::Color::Green : sf::Color::White);
			}
			else if (registerButton.getGlobalBounds().contains(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)))) {
				if (usernameInput.empty() || passwordInput.empty()) {
					errorMessage.setString("Please sign in again!");
				}
				else if (passwordInput.length() < 8) {
					errorMessage.setString("Password must have at least 8 characters");
				}
				else if (passwordInput != confirmPasswordInput) {
					errorMessage.setString("Password errors!");
				}
				else {
					if (registerUser(usernameInput, passwordInput)) {
						std::cout << "Registration successful!" << std::endl;
						Window.close();
						pokerChooseGame menu;
						menu.showMenu();
						// TableWindow menu;
						// GameState currentState = MENU;
						// CountNumberPlayers x;
						// menu.showMenu(currentState);
						// if (currentState == GAME_VS_PLAYER) {
						// 	int n = x.Count();
						// 	menu.showGameTablePVP(n);
						// }
						// else if (currentState == GAME_VS_BOT) {
						// 	int n = x.Count();
						// 	menu.showGameTablePVE(n);
						// }
					}
					else {
						errorMessage.setString("Failed to sign in!");
					}
				}
			}
			else {
				isUsernameActive = false;
				isPasswordActive = false;
				isConfirmPasswordActive = false;
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
				else if (isConfirmPasswordActive && !confirmPasswordInput.empty()) {
					confirmPasswordInput.pop_back();
				}
			}
			else if (event.text.unicode < 128) {
				if (isUsernameActive) {
					usernameInput += static_cast<char>(event.text.unicode);
				}
				else if (isPasswordActive) {
					passwordInput += static_cast<char>(event.text.unicode);
				}
				else if (isConfirmPasswordActive) {
					confirmPasswordInput += static_cast<char>(event.text.unicode);
				}
			}
		}
	}
}

void Register::update(){
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

	std::string hiddenConfirmPassword = showPassword ? confirmPasswordInput : std::string(confirmPasswordInput.length(), '*');
	confirmPasswordString.setFont(font);
	confirmPasswordString.setString(hiddenConfirmPassword);
	confirmPasswordString.setCharacterSize(30);
	confirmPasswordString.setPosition(350, 650);
	confirmPasswordString.setFillColor(sf::Color::Black);
	Window.draw(confirmPasswordString);

	if (isUsernameActive || isPasswordActive || isConfirmPasswordActive) {
		sf::RectangleShape cursor(sf::Vector2f(2, 30));
		cursor.setFillColor(sf::Color::Black);
		if (isUsernameActive) {
			cursor.setPosition(350 + usernameString.getGlobalBounds().width, 250);
		}
		else if (isPasswordActive) {
			cursor.setPosition(350 + passwordString.getGlobalBounds().width, 450);
		}
		else if (isConfirmPasswordActive) {
			cursor.setPosition(350 + confirmPasswordString.getGlobalBounds().width, 650);
		}
		if (cursorClock.getElapsedTime().asSeconds() >= 0.5f) {
			cursorClock.restart();
		}
		if (cursorClock.getElapsedTime().asSeconds() < 0.25f) {
			Window.draw(cursor);
		}
	}
}

void Register::render(){
	Window.clear();
	Window.draw(visual);
	Window.draw(usernameLabel);
	Window.draw(passwordLabel);
	Window.draw(usernameBox);
	Window.draw(passwordBox);	
	Window.draw(showPasswordBox);
	Window.draw(showPasswordText);
	Window.draw(confirmPasswordLabel);
	Window.draw(confirmPasswordBox);
	Window.draw(registerButton);
	Window.draw(registerButtonText);
	Window.draw(showPasswordBox);
	Window.draw(showPasswordText);
    //Window.draw(goback.getText());
	Window.draw(errorMessage);
}

void Register::import(){
	image.loadFromFile("background.jpg");
	visual.setTexture(image);
	visual.setScale(
		Window.getSize().x / visual.getGlobalBounds().width,
		Window.getSize().y / visual.getGlobalBounds().height
	);
}

//bool Register::verifyUser(const std::string& username, const std::string& password) {
//	auto it = users.find(username);
//	return it != users.end() && it->second == password;
//}

bool Register::registerUser(const std::string& username, const std::string& password) {
    if (users.find(username) == users.end()) {
        users[username] = password;
        saveUsers(users, "users.txt");
        saveUsername(username, "player.txt");
        std::ofstream leaderboardFile("Leaderboard.txt", std::ios::app); // Open in append mode
        if (leaderboardFile.is_open()) {
            leaderboardFile << username << " 0" << " 0" << std::endl;
            leaderboardFile.close();
            std::cout << "Leaderboard entry created for: " << username << std::endl;
        }
        return true;
    }
    return false;
}