#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Leaderboard {
public:

	struct Player {
		std::string name;
		int wins;
		int match;

		Player(const std::string& playerName, int playerWins, int matches)
			: name(playerName), wins(playerWins), match(matches) {}
	};
	void showBoard();
	void readLeaderboard();
	void saveLeaderboard();
	void sortLeaderboard(); 
    std::vector<Player> players;
	void updateWins(const std::string& playerName);
	void updateMatch(const std::string& playerName);
	void updateAllMatches(const std::vector<std::string>& playerNames);


private:
	std::string filename;
	sf::Text texts;
	sf::Text nameText;
	sf::Text winsText;
};



