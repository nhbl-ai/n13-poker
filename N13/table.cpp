#include "ResultPanel.h"
#include "TablePlayers.h"
#include "FrameEvents.h"
#include "table.h"
#include <iostream>
#include "Choiceboard.h"
#include "Player.h"
#include <utility>
#include <cmath>
#include "window.h"
#include "Icongame.h"
#include "gameWindow.h"
#include "LogicGame.h"
#include <fstream>
#include "Login.h"
#include "word2.h"
#include <random>
#include <vector>
#include "Leaderboard.h"
#include <random>
using namespace std;
struct player_info
{
	int x;
	int y;
	std::string name;
	int money;
};
#ifdef M_PI
#undef M_PI
#endif
const float M_PI = 3.14;
extern sf::Sound click;
word2 goback;
int random(int l, int r)
{
	return rand() % (r-l+1) + l;
}
void TableWindow::showMenu(GameState& currentState) {
	sf::RenderWindow menuWindow(sf::VideoMode::getDesktopMode(), "Menu" , sf::Style::Fullscreen);
	Icongame x;
	x.windowseticon(menuWindow);
	sf::Font font;
	if (!font.loadFromFile("Tajawal-ExtraLight.ttf")) {
		std::cout << "Failed to load font" << std::endl;
		currentState = EXIT;
		return;
	}


	sf::Texture texture;
	if (!texture.loadFromFile("background.jpg")) {
		std::cerr << "Failed to load background.jpg" << std::endl;
		currentState = EXIT;
		return;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(
		menuWindow.getSize().x / sprite.getGlobalBounds().width,
		menuWindow.getSize().y / sprite.getGlobalBounds().height
	);

	sf::Text playWithHuman("VS Player", font, 80);
	playWithHuman.setPosition(170, 430);
	playWithHuman.setFillColor(sf::Color::White);

	sf::Text playWithBot("VS Bot", font, 80);
	playWithBot.setPosition(170, 530);
	playWithBot.setFillColor(sf::Color::White);

	goback.play("Go back", 100, 60);

	while (menuWindow.isOpen()) {
		sf::Event event;
		sf::Vector2i mousepos = sf::Mouse::getPosition(menuWindow);

		while (menuWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				currentState = EXIT;
				menuWindow.close();
			}


			if (event.type == sf::Event::MouseButtonPressed) {
				click.play();
				sf::Vector2f mousePos = menuWindow.mapPixelToCoords(sf::Mouse::getPosition(menuWindow));
				if (goback.getText().getGlobalBounds().contains(mousepos.x, mousepos.y)) {
					menuWindow.close();
					window newwindow;
					newwindow;
				}
				if (playWithHuman.getGlobalBounds().contains(mousePos)) {
					currentState = GAME_VS_PLAYER;
					menuWindow.close();
				}
				else if (playWithBot.getGlobalBounds().contains(mousePos)) {
					currentState = GAME_VS_BOT;
					menuWindow.close();
				}
			}
		}


		menuWindow.clear();
		menuWindow.draw(sprite);
		menuWindow.draw(playWithHuman);
		menuWindow.draw(playWithBot);
		menuWindow.draw(goback.getText());
		menuWindow.display();
	}
}

void repairTime(Player& time, int countdown)
{
	time.getPlayerinformation().getTime().getText().setString("Time: " + std::to_string(countdown));
}

std::string loadPlayerName() {
	std::ifstream file("player.txt");
	std::string playerName;
	if (file.is_open()) {
		std::getline(file, playerName);
		file.close();
	}
	return playerName;
}

std::vector<std::string> loadAllPlayerNames(Leaderboard& leaderboard) {
	std::vector<std::string> playerNames;
	for (const auto& player : leaderboard.players) {
		playerNames.push_back(player.name);
	}
	return playerNames;
}


void TableWindow::showGameTablePVP(int n) {
    if (n < 2 || n > 6) return;
	std::string player1 = loadPlayerName();
	Leaderboard leaderboard;
	leaderboard.readLeaderboard();

	std::vector<std::string> registeredPlayers = loadAllPlayerNames(leaderboard);
	registeredPlayers.erase(std::remove(registeredPlayers.begin(), registeredPlayers.end(), player1), registeredPlayers.end());

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::shuffle(registeredPlayers.begin(), registeredPlayers.end(), eng);

	std::vector<std::string> selectedPlayers = tablePlayerNames(player1, registeredPlayers, n, false);


	player_info Player_board[6] = {
		{270,750,selectedPlayers[0],200} , {800,750,selectedPlayers[1],200} ,
		{1500, 630,selectedPlayers[2],200} , {1330,75,selectedPlayers[3],200} ,
		{800,75,selectedPlayers[4],200} , {150,615,selectedPlayers[5],200}
	};
	//std::cout << 1;
	std::vector < int > a;
	for (int i = 0; i < n; i++) a.push_back(i);
	std::pair < int, int > Choice_board_xyz[6] = { {800,750} , {1315,750} , {1500, 215} , {800,75} , {285,75} , {150, 200} };
	//CARD------------------------------------------------------------
	Logic logic;

	vector<Card> deck;
	deck = logic.createDeck();
	logic.shuffleDeck(deck);
	vector<vector<Card>> playerHands;
	playerHands = logic.player_cards(deck, n);
	vector<Card>  communityCards;
	communityCards = logic.community_cards(deck, n);
	word2 pot[6];
	pot[0].set("Pot: ", 40, 615, 970);
	pot[1].set("Pot: ", 40, 1135, 970);
	pot[2].set("Pot: ", 40, 1750, 450);
	pot[2].getText().setRotation(90);
	pot[3].set("Pot: ", 40, 1145, 20);
	pot[4].set("Pot: ", 40, 620, 20);
	pot[5].set("Pot: ", 40, 300, 435);
	pot[5].getText().setRotation(90);
	pot[0].getText().setFillColor(sf::Color::Cyan);
	pot[1].getText().setFillColor(sf::Color::Cyan);
	pot[2].getText().setFillColor(sf::Color::Cyan);
	pot[3].getText().setFillColor(sf::Color::Cyan);
	pot[4].getText().setFillColor(sf::Color::Cyan);
	pot[5].getText().setFillColor(sf::Color::Cyan);
	GameWindow Gamewindow;
	vector <sf::Sprite > card(18);
	vector <sf::Vector2f> destinations =
	{
		{0.f,0.f},
		{780.0f, 460.0f},
		{865.0f, 460.0f},
		{950.0f, 460.0f},
		{1035.0f, 460.0f},
		{1120.0f, 460.0f},
		{615.0f, 770.0f},
		{705.0f, 770.0f},
		{1135.0f, 770.0f},
		{1225.0f, 770.0f},
		{1674.0f, 540.0f}, // rotation 90
		{1674.0f, 450.0f}, //rotation 90
		{1235.0f, 170.0f},
		{1145.0f, 170.0f},
		{710.0f, 170.0f},
		{620.0f, 170.0f},
		{440.0f, 435.0f}, //rotation 90 
		{440.0f, 525.0f}  //rotation 90
	};
	sf::Texture back;
	back.loadFromFile("Back.png");
	for (int i = 1; i <= 17; i++)
	{
		card[i].setTexture(back);
		card[i].setPosition(destinations[i]);
		if (i == 10 || i == 11 || i == 16 || i == 17) card[i].setRotation(90.f);
	}
	sf::Texture texture1;
	int money_pot[6] = { 0 };
	texture1.loadFromFile("CardDeck.png");
	sf::Sprite CardDeck;
	CardDeck.setTexture(texture1);
	CardDeck.setPosition(925.0f, 160.0f);
	//----------------------------------------------------------------
	bool check_players[6] = { 0 };
	sf::RenderWindow gameWindow(sf::VideoMode::getDesktopMode(), "PVP" , sf::Style::Fullscreen);
	Icongame x;
	x.windowseticon(gameWindow);
	sf::Texture texture;
	if (!texture.loadFromFile("poker_table.jpg")) {
		std::cerr << "Failed to load" << std::endl;
		return;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(
		gameWindow.getSize().x / sprite.getGlobalBounds().width,
		gameWindow.getSize().y / sprite.getGlobalBounds().height
	);


	sf::Font font;
	if (!font.loadFromFile("Tajawal-ExtraLight.ttf")) {
		std::cerr << "Failed to load font" << std::endl;
		return;
	}

	sf::Texture texture2;
	texture2.loadFromFile("endboard.png");
	sf::Sprite end_board;
	end_board.setTexture(texture2);
	end_board.setPosition(150, -125);
	end_board.setScale(2.5f, 2.5f);
	sf::Vector2f position = end_board.getPosition();
	sf::Vector2f size = sf::Vector2f(end_board.getGlobalBounds().width, end_board.getGlobalBounds().height);
	word2 end_sentence;
	end_sentence.play("Do you want to play again?", position.x + size.x / 6, position.y + size.y / 2 - 20);
	word2 winner;
	word2 yes, no;
	yes.play("Yes", position.x + size.x / 2 + 300, position.y + size.y / 2 - 30);
	no.play("No", position.x + size.x / 2 + 300, position.y + size.y / 2 + 40);
    ResultPanel resultPanel(gameWindow, end_sentence, yes, no);
	//---------------------------

	int turn = 0;

	Choiceboard choiceboard;

	choiceboard.import(Choice_board_xyz[turn].first, Choice_board_xyz[turn].second, "CALL", "RAISE", "FOLD THIS HAND");

	int countdown = 20;
	sf::Clock clock;
	choiceboard.getinputbox().setFillColor(sf::Color::Transparent);
	Player player;
	player.run(gameWindow, Player_board[turn].x, Player_board[turn].y, 200, "Player 1", countdown);
	player.update(Player_board[turn].x, Player_board[turn].y, Player_board[turn].name, Player_board[turn].money, countdown);


	bool kt = 0;
	int check_click = 0;
	int count = 0;
	int check_turn[6] = { 0 };
	sf::Clock time;
	int n_tmp = turn;
	bool winRecorded = false;
	std::cout << 1 << "\n";
	while (gameWindow.isOpen()) {
        FrameEvents frameEvents(gameWindow);
        if (!gameWindow.isOpen()) return;
		if (!kt) time.restart();
		sf::Event event;
		if (a.empty()) return;
		kt = 1;
		if (check_turn[a[0]] == 0 || money_pot[a[0]] != money_pot[a.back()])
		{
			kt = 0;
		}
		for (int i = 1; i < a.size(); i++)
		{
			if (check_turn[a[i]] == 0 || /*check_turn[a[i]] != check_turn[a[i - 1]] || */money_pot[a[i]] != money_pot[a[i - 1]])
			{
				kt = 0;
			}
		}
		if (!kt)
		{
			if (a.size() == 1) n_tmp = turn;
			for (int i = 0; i < a.size(); i++)
			{
				if (a[i] == turn)
				{
					if (i == 0) n_tmp = a.back();
					else n_tmp = a[i - 1];
					break;
				}
			}
			if (n_tmp == turn)
			{
				check_turn[turn] = 2;
				kt = 1;
				//std::cout << n_tmp << " " << turn << "\n";
			}
			while (frameEvents.poll(event)) {
				if (event.type == sf::Event::Closed) {
					gameWindow.close();
				}
				if (!count)
				{
					Gamewindow.move_playercard(gameWindow, n, sprite);
                    if (!gameWindow.isOpen()) return;
					count++;
				}

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				{
					click.play();
					//click.play();
					if (check_click == 2)
					{
						if ((Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 20 >= 0 && choiceboard.Call(gameWindow, event)))
						{
							/*std::cout << "20: ";
							std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
							Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 20;
							money_pot[turn] = money_pot[n_tmp] + 20;
							check_click = 4;
							check_turn[turn]++;
						}
						if ((Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 30 >= 0 && choiceboard.Raise(gameWindow, event)))
						{
							/*std::cout << "30: ";
							std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
							Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 30;
							money_pot[turn] = money_pot[n_tmp] + 30;
							check_click = 4;
							check_turn[turn]++;
						}

						if ((Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 50 >= 0 && choiceboard.Foldthishand(gameWindow, event)))
						{
							/*std::cout << "50: ";
							std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
							Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 50;
							money_pot[turn] = money_pot[n_tmp] + 50;
							check_click = 4;
							check_turn[turn]++;
						}

					}
					else {
						if (kt == 0)
						{
							if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) < 0)
							{
								check_click = 4;
								check_players[turn] = 1;
								//check_click = 4;
								check_turn[turn]++;
								for (int i = 0; i < a.size(); i++)
								{
									if (a[i] == turn)
									{
										a.erase(a.begin() + i);
										break;
									}
								}
							}
							else
							{
								if (choiceboard.Call(gameWindow, event))
								{
									check_click = 4;
									if (money_pot[turn] == money_pot[n_tmp])
										Player_board[turn].money -= 20, money_pot[turn] += 20;
									else Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]), money_pot[turn] = money_pot[n_tmp];
									check_turn[turn]++;
								}
								else
									if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 20 >= 0 && choiceboard.Raise(gameWindow, event))
									{
										check_click = 2;
									}
									else
										if (choiceboard.Foldthishand(gameWindow, event))
										{
											check_players[turn] = 1;
											check_click = 4;
											check_turn[turn]++;
											for (int i = 0; i < a.size(); i++)
											{
												if (a[i] == turn)
												{
													a.erase(a.begin() + i);
													break;
												}
											}
										}
							}
						}
						/*sf::Vector2i mousepos = sf::Mouse::getPosition(gameWindow);
						if (yes.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
						{
							gameWindow.close();
							TableWindow tableagain;
							GameState currentState = MENU;

							tableagain.showMenu(currentState);
							if (currentState == GAME_VS_PLAYER) {

								tableagain.showGameTablePVP(n);
							}
							else if (currentState == GAME_VS_BOT) {
								tableagain.showGameTablePVE(n);
							}
						}
						else if (no.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
						{
							gameWindow.close();
							window();
                        return;
						}*/
					}
				}
				//else if (countdown == 0)
				//{
				//	//countdown = 21;
				//	check_click = 4;
				//	/*check_players[turn] = 1;
				//	check_turn[turn]++;*/
				//	if (!kt)
				//		for (int i = 0; i < a.size(); i++)
				//		{
				//			if (a[i] == turn)
				//			{
				//				a.erase(a.begin() + i);
				//				break;
				//			}
				//		}
				//}
			}
			if (countdown == 0 && !kt)
			{
                check_players[turn] = true;
				//countdown = 21;
				check_click = 4;
				/*check_players[turn] = 1;
				check_turn[turn]++;*/
				if (!kt)
					for (int i = 0; i < a.size(); i++)
					{
						if (a[i] == turn)
						{
							a.erase(a.begin() + i);
							break;
						}
					}
				}
			std::cout << check_click<<" " << turn << "\n";
			//std::cout << countdown <<" " << check_click << "\n";
			if (check_click == 4)
			{
				do
				{
					turn++;
					turn = turn % n;
				} while (check_players[turn]);
				countdown = 21;
				check_click = 0;
			}
			if (clock.getElapsedTime().asSeconds() >= 1.0f)
			{
				clock.restart();
				if (countdown > 0) countdown--;
				repairTime(player, countdown);
			}
		}
		gameWindow.clear();
		gameWindow.draw(sprite);
		gameWindow.draw(CardDeck);
		for (int i = 0; i < n; i++)
		{
			pot[i].getText().setString(Player_board[i].name + " pot " + std::to_string(money_pot[i]) + "$");

			gameWindow.draw(pot[i].getText());
		}
		for (int i = 1; i <= 2 * n + 5; i++)
		{
			if (i > 5 && (((i - 5) / 2 - 1 + ((i - 5) % 2) == turn) && kt == 0))
			{
				sf::Sprite sprite1;
				sf::Texture j;
				string str = Gamewindow.flig1_player(turn, playerHands, 1 - ((i - 5) % 2));
				j.loadFromFile(str);
				sprite1.setTexture(j);
				sprite1.setScale(0.17f, 0.17f);
				sprite1.setPosition(destinations[i]);
				if (turn == 2 || turn == 5)
				{
					sprite1.setRotation(90.f);
				}

				gameWindow.draw(sprite1);
			}
			else if (i <= 3)
			{
				sf::Sprite sprite1;
				sf::Texture j;
				string str = Gamewindow.flig_comunitycard(communityCards, i - 1);
				j.loadFromFile(str);
				sprite1.setTexture(j);
				sprite1.setScale(0.17f, 0.17f);
				sprite1.setPosition(destinations[i]);
				gameWindow.draw(sprite1);
			}
			else if (i > 3 && i <= 5)
			{
				if (i == 4 && (check_turn[turn] >= 1 || kt == 1))
				{
					sf::Sprite sprite1;
					sf::Texture j;
					string str = Gamewindow.flig_comunitycard(communityCards, i - 1);
					j.loadFromFile(str);
					sprite1.setTexture(j);
					sprite1.setScale(0.17f, 0.17f);
					sprite1.setPosition(destinations[i]);
					gameWindow.draw(sprite1);
				}
				else
					if (i == 5 && (check_turn[turn] >= 2 || kt == 1))
					{
						sf::Sprite sprite1;
						sf::Texture j;
						string str = Gamewindow.flig_comunitycard(communityCards, i - 1);
						j.loadFromFile(str);
						sprite1.setTexture(j);
						sprite1.setScale(0.17f, 0.17f);
						sprite1.setPosition(destinations[i]);
						gameWindow.draw(sprite1);
					}
					else gameWindow.draw(card[i]);

			}
			else gameWindow.draw(card[i]);
		}
		if (kt)
		{
			for (int i = 0; i < n; i++)
				if (!check_players[i])
				{
					sf::Sprite sprite1;
					sf::Sprite sprite2;
					sf::Texture j, k;
					string str = Gamewindow.flig1_player(i, playerHands, 0);
					string str2 = Gamewindow.flig1_player(i, playerHands, 1);
					j.loadFromFile(str);
					sprite1.setTexture(j);
					sprite1.setScale(0.17f, 0.17f);
					sprite1.setPosition(destinations[i * 2 + 6]);
					k.loadFromFile(str2);
					sprite2.setTexture(k);
					sprite2.setScale(0.17f, 0.17f);
					sprite2.setPosition(destinations[i * 2 + 7]);
					if (i == 2 || i == 5)
					{
						sprite1.setRotation(90.f);
						sprite2.setRotation(90.f);
					}
					gameWindow.draw(sprite1);
					gameWindow.draw(sprite2);
				}
		}
		player.update(Player_board[turn].x, Player_board[turn].y, Player_board[turn].name, Player_board[turn].money, countdown);
		player.draw(gameWindow);
		sf::Text mode("VS Player", font, 30);
		mode.setPosition(10, 10);
		mode.setFillColor(sf::Color::White);
		gameWindow.draw(mode);
		if (check_click == 2)
			choiceboard.update(Choice_board_xyz[turn].first, Choice_board_xyz[turn].second, "20", "30", "50");
		else
			choiceboard.update(Choice_board_xyz[turn].first, Choice_board_xyz[turn].second, "CALL", "RAISE", "FOLD THIS HAND");
		choiceboard.draw(gameWindow);
		//if (kt && time.getElapsedTime().asSeconds() >= 15.0f )
		if (kt && time.getElapsedTime().asSeconds() >= 7.0f)
		{
			sf::Event event2;
			while (frameEvents.poll(event2))
			{
				if (event2.type == sf::Event::MouseButtonPressed)
				{
					sf::Vector2i mousepos = sf::Mouse::getPosition(gameWindow);
					if (yes.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
					{
						gameWindow.close();
						TableWindow tableagain;
						GameState currentState = MENU;

						tableagain.showMenu(currentState);
						if (currentState == GAME_VS_PLAYER) {

							tableagain.showGameTablePVP(n);
						}
						else if (currentState == GAME_VS_BOT) {
							tableagain.showGameTablePVE(n);
						}
					}
					else if (no.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
					{
						gameWindow.close();
						window();
                        return;
					}
				}
			}
			//gameWindow.draw(end_board);

            if (!winRecorded) {
                WinnerResult result{};
                logic.findWinner(communityCards, playerHands, result, a);
                std::vector<std::string> participantNames;
                for (int i = 0; i < n; ++i) participantNames.push_back(Player_board[i].name);
                resultPanel.setWinner(winner, formatWinners(result, participantNames));
                Leaderboard resultsBoard;
                resultsBoard.readLeaderboard();
                if (result[0] == 0 && result[1] > 0 && result[1] <= n)
                    resultsBoard.updateWins(participantNames[result[1] - 1]);
                resultsBoard.updateAllMatches(participantNames);
                resultsBoard.saveLeaderboard();
                winRecorded = true;
            }
            resultPanel.draw(gameWindow);
            gameWindow.draw(winner.getText());
            gameWindow.draw(end_sentence.getText());
            gameWindow.draw(yes.getText());
            gameWindow.draw(no.getText());
		}
		gameWindow.display();
	}

}




void TableWindow::showGameTablePVE(int n) {
    if (n < 2 || n > 6) return;
	srand(time(NULL));
	std::string player1 = loadPlayerName();
	Leaderboard leaderboard;
	leaderboard.readLeaderboard();

	std::vector<std::string> registeredPlayers = loadAllPlayerNames(leaderboard);
	registeredPlayers.erase(std::remove(registeredPlayers.begin(), registeredPlayers.end(), player1), registeredPlayers.end());

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::shuffle(registeredPlayers.begin(), registeredPlayers.end(), eng);

	std::vector<std::string> selectedPlayers = tablePlayerNames(player1, registeredPlayers, n, true);


	player_info Player_board[6] = {
		{270,750,selectedPlayers[0],200} , {800,750,selectedPlayers[1],200} ,
		{1500, 630,selectedPlayers[2],200} , {1330,75,selectedPlayers[3],200} ,
		{800,75,selectedPlayers[4],200} , {150,615,selectedPlayers[5],200}
	};
	//std::cout << 1;
	std::vector < int > a;
	for (int i = 0; i < n; i++) a.push_back(i);
	std::pair < int, int > Choice_board_xyz[6] = { {800,750} , {1315,750} , {1500, 215} , {800,75} , {285,75} , {150, 200} };
	//CARD------------------------------------------------------------
	Logic logic;

	vector<Card> deck;
	deck = logic.createDeck();
	logic.shuffleDeck(deck);
	vector<vector<Card>> playerHands;
	playerHands = logic.player_cards(deck, n);
	vector<Card>  communityCards;
	communityCards = logic.community_cards(deck, n);
	std::vector<int> player_point(n);
	logic.player_point(communityCards, playerHands, player_point.data());
	word2 pot[6];
	int money_pot[6];
	for (int i = 0; i < n; i++) money_pot[i] = 0;
	pot[0].set("Pot: ", 40, 615, 970);
	pot[1].set("Pot: ", 40, 1135, 970);
	pot[2].set("Pot: ", 40, 1750, 450);
	pot[2].getText().setRotation(90);
	pot[3].set("Pot: ", 40, 1145, 20);
	pot[4].set("Pot: ", 40, 620, 20);
	pot[5].set("Pot: ", 40, 300, 435);
	pot[5].getText().setRotation(90);
	pot[0].getText().setFillColor(sf::Color::Cyan);
	pot[1].getText().setFillColor(sf::Color::Cyan);
	pot[2].getText().setFillColor(sf::Color::Cyan);
	pot[3].getText().setFillColor(sf::Color::Cyan);
	pot[4].getText().setFillColor(sf::Color::Cyan);
	pot[5].getText().setFillColor(sf::Color::Cyan);
	GameWindow Gamewindow;
	vector <sf::Sprite > card(18);
	vector <sf::Vector2f> destinations =
	{
		{0.f,0.f},
		{780.0f, 460.0f},
		{865.0f, 460.0f},
		{950.0f, 460.0f},
		{1035.0f, 460.0f},
		{1120.0f, 460.0f},
		{615.0f, 770.0f},
		{705.0f, 770.0f},
		{1135.0f, 770.0f},
		{1225.0f, 770.0f},
		{1674.0f, 540.0f}, // rotation 90
		{1674.0f, 450.0f}, //rotation 90
		{1235.0f, 170.0f},
		{1145.0f, 170.0f},
		{710.0f, 170.0f},
		{620.0f, 170.0f},
		{440.0f, 435.0f}, //rotation 90 
		{440.0f, 525.0f}  //rotation 90
	};
	sf::Texture back;
	back.loadFromFile("Back.png");
	for (int i = 1; i <= 17; i++)
	{
		card[i].setTexture(back);
		card[i].setPosition(destinations[i]);
		if (i == 10 || i == 11 || i == 16 || i == 17) card[i].setRotation(90.f);
	}
	sf::Texture texture1;
	texture1.loadFromFile("CardDeck.png");
	sf::Sprite CardDeck;
	CardDeck.setTexture(texture1);
	CardDeck.setPosition(925.0f, 160.0f);
	//----------------------------------------------------------------
	bool check_players[6] = { 0 };
	sf::RenderWindow gameWindow(sf::VideoMode::getDesktopMode(), "PVP", sf::Style::Fullscreen);
	Icongame x;
	x.windowseticon(gameWindow);
	sf::Texture texture;
	if (!texture.loadFromFile("poker_table.jpg")) {
		std::cerr << "Failed to load" << std::endl;
		return;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(
		gameWindow.getSize().x / sprite.getGlobalBounds().width,
		gameWindow.getSize().y / sprite.getGlobalBounds().height
	);


	sf::Font font;
	if (!font.loadFromFile("Tajawal-ExtraLight.ttf")) {
		std::cerr << "Failed to load font" << std::endl;
		return;
	}

	sf::Texture texture2;
	texture2.loadFromFile("endboard.png");
	sf::Sprite end_board;
	end_board.setTexture(texture2);
	end_board.setPosition(150, -125);
	end_board.setScale(2.5f, 2.5f);
	sf::Vector2f position = end_board.getPosition();
	sf::Vector2f size = sf::Vector2f(end_board.getGlobalBounds().width, end_board.getGlobalBounds().height);
	word2 end_sentence;
	end_sentence.play("Do you want to play again?", position.x + size.x / 6, position.y + size.y / 2 - 20);
	word2 winner;
	word2 yes, no;
	yes.play("Yes", position.x + size.x / 2 + 300, position.y + size.y / 2 - 30);
	no.play("No", position.x + size.x / 2 + 300, position.y + size.y / 2 + 40);
    ResultPanel resultPanel(gameWindow, end_sentence, yes, no);
	//---------------------------

	int turn = 0;

	Choiceboard choiceboard;

	choiceboard.import(Choice_board_xyz[turn].first, Choice_board_xyz[turn].second, "CALL", "RAISE", "FOLD THIS HAND");

	int countdown = 20;
	sf::Clock clock;
	choiceboard.getinputbox().setFillColor(sf::Color::Transparent);
	Player player;
	player.run(gameWindow, Player_board[turn].x, Player_board[turn].y, 200, "Player 1", countdown);
	player.update(Player_board[turn].x, Player_board[turn].y, Player_board[turn].name, Player_board[turn].money, countdown);


	bool kt = 0;
	int check_click = 0;
	int count = 0;
	int check_turn[6] = { 0 };
	sf::Clock time;
	int n_tmp = turn;
	bool winRecorded = false;
	std::cout << 1 << "\n";
	int bots_action = 0;
	int max_point = 0;
	for (int i = 0; i < n; i++)  max_point = max(max_point, player_point[i]);
		//bots_action = 0;
	bool check_bot[6] = { 0 };
	while (gameWindow.isOpen()) {
        FrameEvents frameEvents(gameWindow);
        if (!gameWindow.isOpen()) return;
		if (!kt) time.restart();
		sf::Event event;
		if (a.empty()) return;
		kt = 1;
		if (check_turn[a[0]] == 0 || money_pot[a[0]] != money_pot[a.back()])
		{
			kt = 0;
		}
		for (int i = 1; i < a.size(); i++)
		{
			if (check_turn[a[i]] == 0 || /*check_turn[a[i]] != check_turn[a[i - 1]] || */money_pot[a[i]] != money_pot[a[i - 1]])
			{
				kt = 0;
			}
		}
		if (!kt)
		{
			if (a.size() == 1) n_tmp = turn;
			for (int i = 0; i < a.size(); i++)
			{
				if (a[i] == turn)
				{
					if (i == 0) n_tmp = a.back();
					else n_tmp = a[i - 1];
					break;
				}
			}
			if (n_tmp == turn)
			{
				check_turn[turn] = 2;
				kt = 1;
				std::cout << n_tmp << " " << turn << "\n";
			}
			
			////1 neu call
			////21 neu raise 20
			////22 neu raise 30
			////23 neu raise 50
			////3 neu fold
			//if (turn != 0 && !check_bot[turn] && countdown == 15)
			//{
			//	check_bot[turn] = 1;
			//	if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) < 0) bots_action = 3;
			//	else
			//		if (player_point[turn] == 1 && max_point == player_point[turn]) bots_action = 1;
			//		else
			//			if (player_point[turn] == 1) bots_action = 3;
			//			else
			//				if (player_point[turn] < 5)
			//				{
			//					if (player_point[turn] == max_point)
			//					{
			//						if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 30 >= 0) bots_action = random(21, 22);
			//						else if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 20 >= 0) bots_action = 21;
			//						else bots_action = 1;
			//					}
			//					else if (player_point[turn] < max_point) bots_action = 1;
			//				}
			//				else if (player_point[turn] <= 10)
			//				{
			//					if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 50 >= 0)
			//					{
			//						bots_action = random(21, 23);
			//					}
			//					else if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 30 >= 0) bots_action = random(21, 22);
			//					else if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 20 >= 0) bots_action = 21;
			//					else bots_action = 1;
			//				}
			//	if (kt == 0)
			//	{
			//		if (Player_board[turn].money == 0) continue;
			//		if (bots_action == 1)
			//		{
			//			check_click = 4;
			//			if (money_pot[turn] == money_pot[n_tmp])
			//				Player_board[turn].money -= 20, money_pot[turn] += 20;
			//			else Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]), money_pot[turn] = money_pot[n_tmp];
			//			check_turn[turn]++;
			//		}
			//		else
			//			if (bots_action > 20)
			//			{
			//				check_click = 2;
			//			}
			//			else
			//				if (bots_action == 3)
			//				{
			//					check_players[turn] = 1;
			//					check_click = 4;
			//					check_turn[turn]++;
			//					for (int i = 0; i < a.size(); i++)
			//					{
			//						if (a[i] == turn)
			//						{
			//							a.erase(a.begin() + i);
			//							break;
			//						}
			//					}
			//				}
			//	}
			//	if (check_click == 2)
			//	{
			//		if (bots_action == 21)
			//		{
			//			/*std::cout << "20: ";
			//			std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
			//			Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 20;
			//			money_pot[turn] = money_pot[n_tmp] + 20;
			//			check_click = 4;
			//			check_turn[turn]++;
			//		}
			//		if (bots_action == 22)
			//		{
			//			/*std::cout << "30: ";
			//			std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
			//			Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 30;
			//			money_pot[turn] = money_pot[n_tmp] + 30;
			//			check_click = 4;
			//			check_turn[turn]++;
			//		}

			//		if (bots_action == 23)
			//		{
			//			/*std::cout << "50: ";
			//			std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
			//			Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 50;
			//			money_pot[turn] = money_pot[n_tmp] + 50;
			//			check_click = 4;
			//			check_turn[turn]++;
			//		}

			//	}
			//}
			while (frameEvents.poll(event)) {
				if (event.type == sf::Event::Closed) {
					gameWindow.close();
				}
				if (!count)
				{
					Gamewindow.move_playercard(gameWindow, n, sprite);
                    if (!gameWindow.isOpen()) return;
					count++;
				}

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && turn == 0)
				{
					click.play();
					if (check_click == 2)
					{
						if ((Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 20 >= 0 && choiceboard.Call(gameWindow, event)))
						{
							/*std::cout << "20: ";
							std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
							Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 20;
							money_pot[turn] = money_pot[n_tmp] + 20;
							check_click = 4;
							check_turn[turn]++;
						}
						if ((Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 30 >= 0 && choiceboard.Raise(gameWindow, event)))
						{
							/*std::cout << "30: ";
							std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
							Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 30;
							money_pot[turn] = money_pot[n_tmp] + 30;
							check_click = 4;
							check_turn[turn]++;
						}

						if ((Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 50 >= 0 && choiceboard.Foldthishand(gameWindow, event)))
						{
							/*std::cout << "50: ";
							std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
							Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 50;
							money_pot[turn] = money_pot[n_tmp] + 50;
							check_click = 4;
							check_turn[turn]++;
						}

					}
					else if ( turn == 0 ) {
						if (kt == 0)
						{
							if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) < 0)
							{
								check_click = 4;
								check_players[turn] = 1;
								check_click = 4;
								check_turn[turn]++;
								for (int i = 0; i < a.size(); i++)
								{
									if (a[i] == turn)
									{
										a.erase(a.begin() + i);
										break;
									}
								}
							}
							else
							{
								if (choiceboard.Call(gameWindow, event))
								{
									check_click = 4;
									if (money_pot[turn] == money_pot[n_tmp])
										Player_board[turn].money -= 20, money_pot[turn] += 20;
									else Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]), money_pot[turn] = money_pot[n_tmp];
									check_turn[turn]++;
								}
								else
									if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 20 >= 0 && choiceboard.Raise(gameWindow, event))
									{
										check_click = 2;
									}
									else
										if (choiceboard.Foldthishand(gameWindow, event))
										{
											check_players[turn] = 1;
											check_click = 4;
											check_turn[turn]++;
											for (int i = 0; i < a.size(); i++)
											{
												if (a[i] == turn)
												{
													a.erase(a.begin() + i);
													break;
												}
											}
										}
							}
						}
						/*sf::Vector2i mousepos = sf::Mouse::getPosition(gameWindow);
						if (yes.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
						{
							gameWindow.close();
							TableWindow tableagain;
							GameState currentState = MENU;

							tableagain.showMenu(currentState);
							if (currentState == GAME_VS_PLAYER) {

								tableagain.showGameTablePVP(n);
							}
							else if (currentState == GAME_VS_BOT) {
								tableagain.showGameTablePVE(n);
							}
						}
						else if (no.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
						{
							gameWindow.close();
							window();
                        return;
						}*/
					}
				}
				//else if (countdown == 0)
				//{
				//	//countdown = 21;
				//	check_click = 4;
				//	/*check_players[turn] = 1;
				//	check_turn[turn]++;*/
				//	if (!kt)
				//		for (int i = 0; i < a.size(); i++)
				//		{
				//			if (a[i] == turn)
				//			{
				//				a.erase(a.begin() + i);
				//				break;
				//			}
				//		}
				//}
			}
			//1 neu call
			//21 neu raise 20
			//22 neu raise 30
			//23 neu raise 50
			//3 neu fold
			if (turn != 0 && !check_bot[turn] && countdown == 17)
			{
				check_bot[turn] = 1;
				if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) < 0) bots_action = 3;
				else
					if (player_point[turn] == 1 && max_point == player_point[turn]) bots_action = 1;
					else
						if (player_point[turn] == 1) bots_action = 3;
						else
							if (player_point[turn] < 5)
							{
								if (player_point[turn] == max_point)
								{
									if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 30 >= 0) bots_action = random(21, 22);
									else if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 20 >= 0) bots_action = 21;
									else bots_action = 1;
								}
								else if (player_point[turn] < max_point) bots_action = 1;
							}
							else if (player_point[turn] <= 10)
							{
								if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 50 >= 0)
								{
									bots_action = random(21, 23);
								}
								else if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 30 >= 0) bots_action = random(21, 22);
								else if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) - 20 >= 0) bots_action = 21;
								else bots_action = 1;
							}
				if (kt == 0)
				{
					if (Player_board[turn].money - (money_pot[n_tmp] - money_pot[turn]) < 0)
					{
						check_click = 4;
						check_players[turn] = 1;
						check_click = 4;
						check_turn[turn]++;
						for (int i = 0; i < a.size(); i++)
						{
							if (a[i] == turn)
							{
								a.erase(a.begin() + i);
								break;
							}
						}
					}
					if (bots_action == 1)
					{
						check_click = 4;
						if (money_pot[turn] == money_pot[n_tmp])
							Player_board[turn].money -= 20, money_pot[turn] += 20;
						else Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]), money_pot[turn] = money_pot[n_tmp];
						check_turn[turn]++;
					}
					else
						if (bots_action > 20)
						{
							check_click = 2;
						}
						else
							if (bots_action == 3)
							{
								check_players[turn] = 1;
								check_click = 4;
								check_turn[turn]++;
								for (int i = 0; i < a.size(); i++)
								{
									if (a[i] == turn)
									{
										a.erase(a.begin() + i);
										break;
									}
								}
							}
				}
				if (check_click == 2)
				{
					if (bots_action == 21)
					{
						/*std::cout << "20: ";
						std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
						Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 20;
						money_pot[turn] = money_pot[n_tmp] + 20;
						check_click = 4;
						check_turn[turn]++;
					}
					if (bots_action == 22)
					{
						/*std::cout << "30: ";
						std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
						Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 30;
						money_pot[turn] = money_pot[n_tmp] + 30;
						check_click = 4;
						check_turn[turn]++;
					}

					if (bots_action == 23)
					{
						/*std::cout << "50: ";
						std::cout << Player_board[turn].money << " " << Player_board[n_tmp].money << " " << turn << " " << n_tmp << "\n";*/
						Player_board[turn].money -= (money_pot[n_tmp] - money_pot[turn]) + 50;
						money_pot[turn] = money_pot[n_tmp] + 50;
						check_click = 4;
						check_turn[turn]++;
					}

				}
			}
			if (countdown == 0 && !kt)
			{
                check_players[turn] = true;
				//countdown = 21;
				check_click = 4;
				/*check_players[turn] = 1;
				check_turn[turn]++;*/
				if (!kt)
					for (int i = 0; i < a.size(); i++)
					{
						if (a[i] == turn)
						{
							a.erase(a.begin() + i);
							break;
						}
					}
			}
			//std::cout << countdown <<" " << check_click << "\n";
			std::cout << turn << " " << check_bot[turn] << " " << check_click <<" " << bots_action << "\n";
			if (check_click == 4)
			{
				if ((turn != 0 && countdown <= 17) || turn == 0)
				{
					check_bot[turn] = 0;
					do
					{
						turn++;
						turn = turn % n;
					} while (check_players[turn]);
					countdown = 21;
					check_click = 0;
					bots_action = 0;
				}
			}
			if (clock.getElapsedTime().asSeconds() >= 1.0f)
			{
				clock.restart();
				if (countdown > 0) countdown--;
				repairTime(player, countdown);
			}
		}
		gameWindow.clear();
		gameWindow.draw(sprite);
		gameWindow.draw(CardDeck);
		for (int i = 0; i < n; i++)
		{
			pot[i].getText().setString(Player_board[i].name + " pot " + std::to_string(money_pot[i]) + "$");
			gameWindow.draw(pot[i].getText());
		}
		for (int i = 1; i <= 2 * n + 5; i++)
		{
			if (i > 5 && (((i - 5) / 2 - 1 + ((i - 5) % 2) == turn) && kt == 0))
			{
				sf::Sprite sprite1;
				sf::Texture j;
				string str = Gamewindow.flig1_player(turn, playerHands, 1 - ((i - 5) % 2));
				j.loadFromFile(str);
				sprite1.setTexture(j);
				sprite1.setScale(0.17f, 0.17f);
				sprite1.setPosition(destinations[i]);
				if (turn == 2 || turn == 5)
				{
					sprite1.setRotation(90.f);
				}

				gameWindow.draw(sprite1);
			}
			else if (i <= 3)
			{
				sf::Sprite sprite1;
				sf::Texture j;
				string str = Gamewindow.flig_comunitycard(communityCards, i - 1);
				j.loadFromFile(str);
				sprite1.setTexture(j);
				sprite1.setScale(0.17f, 0.17f);
				sprite1.setPosition(destinations[i]);
				gameWindow.draw(sprite1);
			}
			else if (i > 3 && i <= 5)
			{
				if (i == 4 && (check_turn[turn] >= 1 || kt == 1))
				{
					sf::Sprite sprite1;
					sf::Texture j;
					string str = Gamewindow.flig_comunitycard(communityCards, i - 1);
					j.loadFromFile(str);
					sprite1.setTexture(j);
					sprite1.setScale(0.17f, 0.17f);
					sprite1.setPosition(destinations[i]);
					gameWindow.draw(sprite1);
				}
				else
					if (i == 5 && (check_turn[turn] >= 2 || kt == 1))
					{
						sf::Sprite sprite1;
						sf::Texture j;
						string str = Gamewindow.flig_comunitycard(communityCards, i - 1);
						j.loadFromFile(str);
						sprite1.setTexture(j);
						sprite1.setScale(0.17f, 0.17f);
						sprite1.setPosition(destinations[i]);
						gameWindow.draw(sprite1);
					}
					else gameWindow.draw(card[i]);

			}
			else gameWindow.draw(card[i]);
		}
		if (kt)
		{
			for (int i = 0; i < n; i++)
				if (!check_players[i])
				{
					sf::Sprite sprite1;
					sf::Sprite sprite2;
					sf::Texture j, k;
					string str = Gamewindow.flig1_player(i, playerHands, 0);
					string str2 = Gamewindow.flig1_player(i, playerHands, 1);
					j.loadFromFile(str);
					sprite1.setTexture(j);
					sprite1.setScale(0.17f, 0.17f);
					sprite1.setPosition(destinations[i * 2 + 6]);
					k.loadFromFile(str2);
					sprite2.setTexture(k);
					sprite2.setScale(0.17f, 0.17f);
					sprite2.setPosition(destinations[i * 2 + 7]);
					if (i == 2 || i == 5)
					{
						sprite1.setRotation(90.f);
						sprite2.setRotation(90.f);
					}
					gameWindow.draw(sprite1);
					gameWindow.draw(sprite2);
				}
		}
		player.update(Player_board[turn].x, Player_board[turn].y, Player_board[turn].name, Player_board[turn].money, countdown);
		if (!kt) player.draw(gameWindow);
		sf::Text mode("VS Bot", font, 30);
		mode.setPosition(10, 10);
		mode.setFillColor(sf::Color::White);
		gameWindow.draw(mode);
		if (check_click == 2)
			choiceboard.update(Choice_board_xyz[turn].first, Choice_board_xyz[turn].second, "20", "30", "50");
		else
			choiceboard.update(Choice_board_xyz[turn].first, Choice_board_xyz[turn].second, "CALL", "RAISE", "FOLD THIS HAND");
		if ( turn == 0 && !kt )
			choiceboard.draw(gameWindow);
		//if (kt && time.getElapsedTime().asSeconds() >= 15.0f )
		if (kt && time.getElapsedTime().asSeconds() >= 7.0f)
		{
			sf::Event event2;
			while (frameEvents.poll(event2))
			{
				if (event2.type == sf::Event::MouseButtonPressed)
				{
					sf::Vector2i mousepos = sf::Mouse::getPosition(gameWindow);
					if (yes.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
					{
						gameWindow.close();
						TableWindow tableagain;
						GameState currentState = MENU;

						tableagain.showMenu(currentState);
						if (currentState == GAME_VS_PLAYER) {

							tableagain.showGameTablePVP(n);
						}
						else if (currentState == GAME_VS_BOT) {
							tableagain.showGameTablePVE(n);
						}
					}
					else if (no.getText().getGlobalBounds().contains(mousepos.x, mousepos.y))
					{
						gameWindow.close();
						window();
                        return;
					}
				}
			}
            // Result text is rendered below.
            if (!winRecorded) {
                WinnerResult result{};
                logic.findWinner(communityCards, playerHands, result, a);
                std::vector<std::string> participantNames;
                for (int i = 0; i < n; ++i) participantNames.push_back(Player_board[i].name);
                resultPanel.setWinner(winner, formatWinners(result, participantNames));
                Leaderboard resultsBoard;
                resultsBoard.readLeaderboard();
                if (result[0] == 0 && result[1] > 0 && result[1] <= n)
                    resultsBoard.updateWins(participantNames[result[1] - 1]);
                resultsBoard.updateAllMatches(participantNames);
                resultsBoard.saveLeaderboard();
                winRecorded = true;
            }
            resultPanel.draw(gameWindow);
            gameWindow.draw(winner.getText());
            gameWindow.draw(end_sentence.getText());
            gameWindow.draw(yes.getText());
            gameWindow.draw(no.getText());
		}
		gameWindow.display();
	}
}







