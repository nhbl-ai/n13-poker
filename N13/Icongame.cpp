#include "Icongame.h"
void Icongame::windowseticon(sf::RenderWindow& window)
{
	icon.loadFromFile("poker_icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}