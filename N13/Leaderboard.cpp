#include "Leaderboard.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include "word2.h"
#include "window.h"
#include <SFML/Audio.hpp>
#include "Icongame.h"

extern sf::Sound click;
void Leaderboard::readLeaderboard() {
    players.clear();
	std::ifstream file("Leaderboard.txt");
	if (file.is_open()) {
		std::string name;
		int wins, match;
		while (file >> name >> wins >> match) {
			players.push_back(Player(name, wins, match));
		}
		file.close();
	}
	else {
		std::cout << "Can not open file" << filename << std::endl;
	}
}

void Leaderboard::saveLeaderboard() {
	std::ofstream file("Leaderboard.txt");
	if (file.is_open()) {
		for (const auto& player : players) {
			file << player.name << " " << player.wins << " " << player.match << std::endl;
		}
		file.close();
	}
	else {
		std::cout << "Can not save file " << filename << std::endl;
	}
}

void Leaderboard::sortLeaderboard() {
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.wins > b.wins;
        });
}
 
void Leaderboard::updateWins(const std::string& playerName) {   
    for (auto& player : players) {
        if (player.name == playerName) {
            player.wins++;
            break;
        }
    }
}

void Leaderboard::updateMatch(const std::string& playerName) {
    for (auto& player : players) {
        if (player.name == playerName) {
            player.match++;
            break;
        }
    }
}
void Leaderboard::updateAllMatches(const std::vector<std::string>& playerNames) {
    for (const auto& names : playerNames) {
        updateMatch(names);
    }
}

void Leaderboard::showBoard() {
    sf::RenderWindow leaderBoard(sf::VideoMode::getDesktopMode(), "Leaderboard" , sf::Style::Fullscreen);

    sf::Texture visual;
    if (!visual.loadFromFile("LEADERBOARD.png")) {
        std::cerr << "Failed to load visual" << std::endl;
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(visual);
    sprite.setScale(
        leaderBoard.getSize().x / sprite.getGlobalBounds().width,
        leaderBoard.getSize().y / sprite.getGlobalBounds().height
    );

    sf::Font font;
    if (!font.loadFromFile("Tajawal-ExtraLight.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    sf::Texture gold, silver, bronze;
    if (!gold.loadFromFile("vang.png") ||
        !silver.loadFromFile("bac.png") ||
        !bronze.loadFromFile("dong.png")) {
        std::cerr << "Failed to load medal icons" << std::endl;
        return;
    }

	word2 name, wins, match;
	name.set("Username", 50, 650, 140);
	wins.set("Win", 50, 1095, 140);
	match.set("Match", 50, 1230, 140);

    std::vector<sf::Text> texts;
    std::vector<sf::RectangleShape> boxes;
    std::vector<sf::Sprite> medals; 
   
	float y = 220;
	float xName = 650;
	float xWins = 1110;
	float xMatch = 1270;

    for (size_t i = 0; i < players.size(); ++i) {
        const auto& player = players[i];
        sf::RectangleShape box(sf::Vector2f(750, 52));
        box.setFillColor(sf::Color(50, 50, 50, 200));
        box.setPosition(600, y);
        boxes.push_back(box);

        sf::Text nameText;
        nameText.setFont(font);
        nameText.setCharacterSize(50);
        nameText.setFillColor(sf::Color::White);
        nameText.setString(player.name);
        nameText.setPosition(xName, y);
        texts.push_back(nameText);

        sf::Text winsText;
        winsText.setFont(font);
        winsText.setCharacterSize(50);
        winsText.setFillColor(sf::Color::White);
        winsText.setString(std::to_string(player.wins));
        winsText.setPosition(xWins, y);
        texts.push_back(winsText);

		sf::Text matchText;
		matchText.setFont(font);
		matchText.setCharacterSize(50);
		matchText.setFillColor(sf::Color::White);
		matchText.setString(std::to_string(player.match));
		matchText.setPosition(xMatch, y);
		texts.push_back(matchText);

        if (i < 3) {
            sf::Sprite medal;
            if (i == 0) {
                medal.setTexture(gold);
            }
            else if (i == 1) {
                medal.setTexture(silver);
            }
            else if (i == 2) {
                medal.setTexture(bronze);
            }
            medal.setPosition(600, y + 10);
            medals.push_back(medal);
        }
        y += 80;
    }

    word2 goback; 
    goback.play("Go back", 120, 60); 
    Icongame x;
    x.windowseticon(leaderBoard);
    while (leaderBoard.isOpen()) {
        sf::Event event;
        sf::Vector2i mousepos = sf::Mouse::getPosition(leaderBoard);

        while (leaderBoard.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderBoard.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                click.play();
                if (goback.getText().getGlobalBounds().contains(mousepos.x, mousepos.y)) {
                    leaderBoard.close();
                    window newwindow;
                    newwindow;
                }

            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                leaderBoard.close();
            }
        }

        leaderBoard.clear(sf::Color::Black);
        leaderBoard.draw(sprite);
		leaderBoard.draw(name.getText());  
		leaderBoard.draw(wins.getText());   
		leaderBoard.draw(match.getText());  
        leaderBoard.draw(goback.getText());
        for (const auto& box : boxes) {
            leaderBoard.draw(box);
        }

        for (const auto& text : texts) {
            leaderBoard.draw(text);
        }

        for (const auto& medal : medals) {
            leaderBoard.draw(medal);
        }

        leaderBoard.display();
    }
}