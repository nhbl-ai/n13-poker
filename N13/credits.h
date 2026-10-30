#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
class CreditsWindow
{
public:
    CreditsWindow();
    void import();
    bool loadCredits();
    void showCredits(sf::RenderWindow& Window, float x, float y);
    void run();
private:
    std::string CreditsFile = "credits.txt";
    sf::RenderWindow Window;
    sf::Texture giaodienCredits;
    sf::Sprite backgroundCredits;
    sf::Text text;
    sf::Font font;
    std::vector<std::string> content;
};

#pragma once
