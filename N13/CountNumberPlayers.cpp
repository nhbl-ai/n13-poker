#include "word2.h"
#include "tittle.h" 
#include "LoginWindow.h"
#include "Icongame.h"
#include "CountNumberPlayers.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//#include "sfml"
//---------------------- Gia
extern sf::Sound click;

//-----------------------------

/*LoginWindow Loginwindow;*/ // Ensure this instance is declared

int CountNumberPlayers::Count()
{
	Window.create(sf::VideoMode::getDesktopMode(), "CountNumberPlayers", sf::Style::Fullscreen);
	import();
	Icongame x;
	x.windowseticon(Window);
	/*sf::Music music;
	music.openFromFile("backgroundsong.mp3");
	music.play();*/

	//music.stop();
	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed) click.play();
			if (event.type == sf::Event::Closed) { Window.close(); return 0; }
			//-------------------
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(Window);
					if (p2.getText().getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						Window.close();
						return 2;
					}
					else if (p3.getText().getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						Window.close();
						return 3;
					}
					else if (p4.getText().getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						Window.close();
						return 4;
					} 
					else if (p5.getText().getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						Window.close();
						return 5;
					}
					else if (p6.getText().getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						Window.close();
						return 6;
					}
					
				}
				//-------------------
			}
		}
		screen();
	}
	return 0;
}
void CountNumberPlayers::import()
{
	image.loadFromFile("background.jpg");
	visual.setTexture(image);
	visual.setScale(
		Window.getSize().x / visual.getGlobalBounds().width,
		Window.getSize().y / visual.getGlobalBounds().height
	);
}
void CountNumberPlayers::word( word2& t, std::string chu, float x, float y)
{
	t.play(chu, x, y);
	Window.draw(t.getText());
}
void CountNumberPlayers::screen()
{
	title c;
	c.play();
	Window.clear();
	Window.draw(visual);
	float cong = 100;

	word(p2, "2 PLAYERS ", 170, 430);
	word(p3, "3 PLAYERS", 170, 430 + cong);
	word(p4, "4 PLAYERS", 170, 430 + 2 * cong);
	word(p5, "5 PLAYERS", 170, 430 + 3 * cong);
	word(p6, "6 PLAYERS", 170, 430 + 4 * cong);
	Window.draw(c.getText());
	Window.display();
}


//----------------------------Ngoc


//------------------------------


