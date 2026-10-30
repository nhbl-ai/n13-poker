#include "credits.h"
#include <iostream>
#include <string>
#include <fstream>
#include "word2.h"
#include "Icongame.h"
#include "window.h"
#include <SFML/Audio.hpp>
CreditsWindow::CreditsWindow() : Window(sf::VideoMode::getDesktopMode(), "Credits" , sf::Style::Fullscreen) {
	import();
	loadCredits();
}
extern sf::Sound click;
void CreditsWindow::import() {
	Icongame x;
	x.windowseticon(Window);
	giaodienCredits.loadFromFile("background credits.jpg");
	backgroundCredits.setTexture(giaodienCredits);
	backgroundCredits.setScale(
		Window.getSize().x / backgroundCredits.getGlobalBounds().width,
		Window.getSize().y / backgroundCredits.getGlobalBounds().height
	);
}

std::vector <std::string> title = { "CREDITS" };  

bool CreditsWindow::loadCredits() {
	std::ifstream files;
	files.open("credits.txt");
	std::string line;
	while (files.good()) {
		std::getline(files, line);
		content.push_back(line);

	}
	files.close();
	return true;

}

void CreditsWindow::showCredits(sf::RenderWindow& Window, float x, float y) {
	font.loadFromFile("Tajawal-ExtraLight.ttf");
	float setY = y; // Start position for the first line
	for (auto& titles : title) {
		text.setFont(font);
		text.setString(titles);
		text.setCharacterSize(80);
		text.setFillColor(sf::Color::White);
		text.setPosition(x * 3, setY);
		Window.draw(text);
		setY += 80;
	}
	for (auto& line : content) {
		text.setFont(font);
		text.setString(line);
		text.setCharacterSize(40);
		text.setFillColor(sf::Color::White);
		text.setPosition(x, setY);

		Window.draw(text);
		setY += 50;
	}

	
}

void CreditsWindow::run() {
	Icongame x;
	x.windowseticon(Window);
	word2 goback;
	goback.play("Go back", 120, 60);
	
	while (Window.isOpen()) {
		sf::Event event;
		sf::Vector2i mousepos = sf::Mouse::getPosition(Window);
		while (Window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				Window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				click.play();
				if(goback.getText().getGlobalBounds().contains(mousepos.x,mousepos.y)){
					Window.close();
					window newwindow;
					newwindow;
				}

			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				Window.close();
				
			}
		}


		Window.clear(sf::Color::Black); 
		Window.draw(backgroundCredits);
		Window.draw(goback.getText());
		showCredits(Window, 250, 50);
		Window.display();
	}
}













