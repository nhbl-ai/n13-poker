#include "OptionWindow.h"
#include "tittle.h"
#include <iostream>
#include "word2.h"
#include "window.h"
#include "Icongame.h"
//void OptionWindow::import()
//{
//	!giaodienoption.loadFromFile("background.jpg");
//	backgroundoption.setTexture(giaodienoption);
//	backgroundoption.setScale(
//		Window.getSize().x / backgroundoption.getGlobalBounds().width,
//		Window.getSize().y / backgroundoption.getGlobalBounds().height
//	);
//}
//OptionWindow::OptionWindow() :Window(sf::VideoMode::getDesktopMode(), "Option")
//{
//	//import();
//	while (Window.isOpen())
//	{
//		sf::Event event;
//		while (Window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed) Window.close();
//		}
//	}
//	Window.clear();
//	Window.draw(backgroundoption);
//	Window.display();
//}
extern sf::Music music;
extern sf::Sound click;
void OptionWindow::create()
{
	box.setSize(sf::Vector2f(50.f, 50.f));
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::White);
	box.setOutlineThickness(5);
	box.setPosition(sf::Vector2f(170.f, 430.f));

}
void OptionWindow::run() {
	sf::RenderWindow optionwindow(sf::VideoMode::getDesktopMode(), "Option Window" , sf::Style::Fullscreen);
	Icongame x;
	x.windowseticon(optionwindow);
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.jpg")) {
		std::cerr << "Error loading background image!" << std::endl;
		return;
	}
	title poker;
	poker.play();
	sf::Sprite background;
	background.setTexture(backgroundTexture);
	background.setScale(
		optionwindow.getSize().x / background.getGlobalBounds().width,
		optionwindow.getSize().y / background.getGlobalBounds().height
	);
	//-------------------------- Load anh
	create();
	word2 turnon,turnoff,goback;
	goback.play("Go back!", 250, 640 + 15);
	turnon.play("Turn on", 250, 400 + 15);
	turnoff.play("Turn off", 250, 520 + 15);
	sf::Texture volumeon,volumeoff;
	volumeon.loadFromFile("volumeon.jpg");
	volumeoff.loadFromFile("volumeoff.jpg");
	sf::Sprite volon, voloff;
	volon.setTexture(volumeon);
	volon.setPosition(520, 430 + 10);
	volon.setScale(0.125f,0.125f);
	voloff.setTexture(volumeoff);
	voloff.setPosition(520, 550 + 10);
	voloff.setScale(0.125f,0.125f);
	
	sf::RectangleShape box2 = box;
	box2.setPosition(sf::Vector2f(170.f, 550.f));
	//----------------------------------------
	while (optionwindow.isOpen()) {
		sf::Event event;
		while (optionwindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				optionwindow.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				click.play();
				sf::Vector2i mousepos = sf::Mouse::getPosition(optionwindow);
				if (box.getGlobalBounds().contains(mousepos.x, mousepos.y))
				{
					box.setFillColor(sf::Color::White);
					box2.setFillColor(sf::Color::Transparent);
					music.setVolume(50.f);
					click.setVolume(50.f);
				}
				if (box2.getGlobalBounds().contains(mousepos.x, mousepos.y))
				{
					box2.setFillColor(sf::Color::White);
					box.setFillColor(sf::Color::Transparent);
					music.setVolume(0.f);
					click.setVolume(0.f);
				}
				if (goback.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
				{
					optionwindow.close();
					window newwindow;
					newwindow;
				}
			}
				
			/*if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mouse = sf::Mouse::getPosition(window);
				std::cout << mouse.x << " " << mouse.y << "\n";
			}*/ 
			//170 430
		}

		optionwindow.clear();
		optionwindow.draw(background);
		optionwindow.draw(poker.getText());
		optionwindow.draw(box);
		optionwindow.draw(box2);
		optionwindow.draw(turnon.getText());
		optionwindow.draw(volon);
		optionwindow.draw(turnoff.getText());
		optionwindow.draw(voloff);
		optionwindow.draw(box2);
		optionwindow.draw(goback.getText());
		optionwindow.display();
	}
}
