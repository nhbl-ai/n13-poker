#include "word2.h"
#include "window.h"
#include "tittle.h" 
#include "OptionWindow.h"
#include "credits.h"
#include "LoginWindow.h"
#include "table.h"
#include "Icongame.h"
#include "Leaderboard.h"
//#include "sfml"
//---------------------- Gia
extern sf::Sound click;
void window::option(sf::Event sukien, float x, float y)
{
	sf::Font font;
	font.loadFromFile("Tajawal-ExtraLight.ttf");
	sf::Text op("Option", font, 70);
	op.setPosition(170, 430 + 2 * 100);
	if (sukien.type == sf::Event::MouseButtonPressed && sukien.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i toadochuot = sf::Mouse::getPosition(Window);
		if (op.getGlobalBounds().contains(toadochuot.x, toadochuot.y))
		{
			Window.close();
			OptionWindow newWindow;
			newWindow.run();
		}

	}
}
//-----------------------------

/*LoginWindow Loginwindow;*/ // Ensure this instance is declared

window::window() : Window(sf::VideoMode::getDesktopMode(), "poker", sf::Style::Fullscreen)
{
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
			if (event.type == sf::Event::Closed) Window.close();
			leaderboard(event, 170, 430 + 100);
			//------------------- Gia
			option(event, 170, 430 + 2 * 100);
			//-------------------
			credits(event, 170, 430 + 2 * 100);
			//-------------------
			quit(event, 170, 430 + 4 * 100);
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition();
					sf::Font font;
					font.loadFromFile("Tajawal-ExtraLight.ttf");
					sf::Text log("Login", font, 70);
					log.setPosition(170, 430);
					if (log.getGlobalBounds().contains(mousePos.x,mousePos.y))
					{

						Window.close();
						LoginWindow login;
						login.showMenu();
						//logic.draw();

					}
				}
				//-------------------
			}
		}
		screen();
	}
	//screen();
}
void window::import()
{
	image.loadFromFile("background.jpg");
	visual.setTexture(image);
	visual.setScale(
		Window.getSize().x / visual.getGlobalBounds().width,
		Window.getSize().y / visual.getGlobalBounds().height
	);
}
void window::word(std::string chu, float x, float y)
{
	word2 t;
	t.play(chu, x, y);
	Window.draw(t.getText());
}
void window::screen()
{
	title c;
	c.play();
	Window.clear();
	Window.draw(visual);
	float cong = 100;
	word("Login", 170, 430);
	word("Leaderboard", 170, 430 + cong);
	word("Option", 170, 430 + 2 * cong);
	word("Credit", 170, 430 + 3 * cong);
	word("Quit", 170, 430 + 4 * cong);
	Window.draw(c.getText());
	Window.display();	
}


//----------------------------Ngoc
void window::credits(sf::Event sukien, float x, float y)
{
	sf::Font font;
	font.loadFromFile("Tajawal-ExtraLight.ttf");
	sf::Text op("Credits", font, 70);
	op.setPosition(250.f, 430.f + 3 * 100);
	if (sukien.type == sf::Event::MouseButtonPressed && sukien.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i toadochuot = sf::Mouse::getPosition(Window);
		if (op.getGlobalBounds().contains(toadochuot.x, toadochuot.y))
		{
			Window.close();
			CreditsWindow newWindow;
			newWindow.run();
		}

	}
}

//------------------------------
void window::leaderboard(sf::Event sukien, float x, float y)
{
	sf::Font font;
	font.loadFromFile("Tajawal-ExtraLight.ttf");
	sf::Text guestText("Leaderboard", font, 70);
	guestText.setPosition(170, 430 + 100);

	if (sukien.type == sf::Event::MouseButtonPressed && sukien.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i toadochuot = sf::Mouse::getPosition(Window);
		if (guestText.getGlobalBounds().contains(toadochuot.x, toadochuot.y))
		{
			Window.close();
			Leaderboard board; 
			board.readLeaderboard(); 
			board.sortLeaderboard(); 
			board.showBoard(); 
		}

	}
}

void window::quit(sf::Event sukien, float x, float y) {
    sf::Font font;
    font.loadFromFile("Tajawal-ExtraLight.ttf");
    sf::Text text("Quit", font, 70);
    text.setPosition(170, 430 + 4 * 100);
    if (sukien.type == sf::Event::MouseButtonPressed && sukien.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(Window);
        if (text.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            Window.close();
        }
    }
} 


