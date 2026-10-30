#include "ResultPanel.h"
#include "TablePlayers.h"
#include "FrameEvents.h"
#include "ThreeCards.h"
#include <iostream>
#include "Choiceboard.h"
#include "Player.h"
#include <utility>
#include <cmath>
#include "window.h"
#include "Icongame.h"
#include "gameWindow.h"
#include "LogicThreeCards.h"
#include <fstream>
#include "Login.h"
#include "Leaderboard.h"
extern sf::Sound click;
extern word2 goback;
//word2 goback;
struct player_info
{
	int x;
	int y;
	std::string name;
	int money;
};
void ThreeCards::showMenu(GameState& currentState) {
	sf::RenderWindow menuWindow(sf::VideoMode::getDesktopMode(), "Menu");
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

	sf::Text playWithHuman("Play game", font, 80);
	playWithHuman.setPosition(170, 430);
	playWithHuman.setFillColor(sf::Color::White);


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
			}
		}


		menuWindow.clear();
		menuWindow.draw(sprite);
		menuWindow.draw(playWithHuman);
		//menuWindow.draw(playWithBot);
		menuWindow.draw(goback.getText());
		menuWindow.display();
	}
}
extern string loadPlayerName();
extern vector <std::string> loadAllPlayerNames(Leaderboard& leaderboard);

void ThreeCards::showGameTablePVP(int n) {
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
	//CARD------------------------------------------------------------
	LogicThreeCards logic;

	vector<Card> deck;
	deck = logic.createDeck();
	logic.shuffleDeck(deck);
	vector<vector<Card>> playerHands;
	//std::cout << n;
	playerHands = logic.player_hands_threecard(deck, n);
	//std::cout << 1;
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
	vector <sf::Sprite > card(19);
	vector <sf::Vector2f> destinations =
	{
		{0.f,0.f},
		{605.0f, 770.0f},
		{695.0f, 770.0f},
		{785.0f, 770.0f},
		{1125.0f, 770.0f},
		{1215.0f, 770.0f},
		{1305.0f, 770.0f},
		{1574.0f, 450.0f + 120}, //rotation 90
		{1574.0f, 360.0f + 120}, //rotation 90
		{1574.0f, 270.0f + 120}, //rotation 90
		{1305.0f, 170.0f},
		{1215.0f, 170.0f},
		{1125.0f, 170.0f},
		{785.0f, 170.0f},
		{695.0f, 170.0f},
		{605.0f, 170.0f},
		{340.0f + 200, 450.0f + 120},  //rotation 90
		{340.0f + 200, 360.0f + 120},  //rotation 90
		{340.0f + 200, 270.0f + 120},  //rotation 90
	};
	sf::Texture back;
	back.loadFromFile("Back.png");
	for (int i = 1; i <= 18; i++)
	{
		card[i].setTexture(back);
		card[i].setPosition(destinations[i]);
		if ((i >= 7 && i <= 9) || (i >= 16 && i <= 18)) card[i].setRotation(90.f);
	}

	sf::Sprite Front_card[19];

	sf::Texture texture1;
	int money_pot[6] = { 20 , 20 , 20 , 20 , 20 , 20 };
	texture1.loadFromFile("CardDeck.png");
	sf::Sprite CardDeck;
	CardDeck.setTexture(texture1);
	CardDeck.setPosition(925.0f, 460.0f);
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
	int countdown = 5;
	int money = 20;
	int countdown1 = 10;
	sf::Clock clock;
	Player player[6];
	//player.run(gameWindow, Player_board[turn].x, Player_board[turn].y, 200, "Player 1", countdown);
	for (int i = 0; i < n; i++)
		player[i].update(Player_board[i].x, Player_board[i].y, Player_board[i].name, Player_board[i].money, money);


	bool kt = 0;
	int check_click = 0;
	int count = 0;
	int check_turn[6] = { 0 };
	sf::Clock time;
	int n_tmp = turn;
	bool winRecorded = false;
	//std::cout << 1 << "\n";
	while (gameWindow.isOpen()) {
        FrameEvents frameEvents(gameWindow);
        if (!gameWindow.isOpen()) return;
		if (!count)
		{
			Gamewindow.move_playercard_3card(gameWindow, n, sprite);
                    if (!gameWindow.isOpen()) return;
			count++;
		}
		gameWindow.clear();
		gameWindow.draw(sprite);
		gameWindow.draw(CardDeck);
		for (int i = 0; i < n; i++)
		{
			pot[i].getText().setString(Player_board[i].name + " pot " + std::to_string(money_pot[i]) + "$");

			gameWindow.draw(pot[i].getText());
		}
		if (countdown)
			for (int i = 1; i <= 3 * n; i++)
			{
				gameWindow.draw(card[i]);
			}
		if (countdown != 0)
		{
			word2 Time;
			Time.play(std::to_string(countdown), 800.0f, 300.0f);
			Time.getText().setCharacterSize(300);
			if (clock.getElapsedTime().asSeconds() >= 1.0f)
			{
				clock.restart();
				if (countdown > 0) countdown--;

			}
			gameWindow.draw(Time.getText());
			//gameWindow.display();
		}
		if (countdown == 0)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					sf::Texture k;
					string str = Gamewindow.flig_comunitycard(playerHands[i], j);
					k.loadFromFile(str);
					Front_card[i * 3 + j].setTexture(k);
					Front_card[i * 3 + j].setScale(0.17f, 0.17f);
					Front_card[i * 3 + j].setPosition(destinations[i * 3 + j + 1]);
					if (i == 2 || i == 5)
					{
						Front_card[i * 3 + j].setRotation(90.f);
					}
					gameWindow.draw(Front_card[i * 3 + j]);
				}
			}
			//if ( )
		}
		if (countdown == 0 && countdown1)
		{
			word2 Time;
			Time.play(std::to_string(countdown1), 800.0f, 300.0f);
			//Time.getText().set
			Time.getText().setCharacterSize(300);
			if (clock.getElapsedTime().asSeconds() >= 1.0f)
			{
				clock.restart();
				if (countdown1 > 0) countdown1--;

			}
			gameWindow.draw(Time.getText());
			//gameWindow.display();
		}
		//player[0].draw(gameWindow);
		for (int i = 0; i < n; i++)
		{
			player[i].update(Player_board[i].x, Player_board[i].y, Player_board[i].name, Player_board[i].money, money);
			player[i].draw(gameWindow);
		}
		sf::Text mode("VS Player", font, 30);
		mode.setPosition(10, 10);
		mode.setFillColor(sf::Color::White);
		gameWindow.draw(mode);
		//if (kt && time.getElapsedTime().asSeconds() >= 15.0f )
		if (!countdown1)
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
						ThreeCards tableagain;
						GameState currentState = MENU;

						tableagain.showMenu(currentState);
						if (currentState == GAME_VS_PLAYER) {

							tableagain.showGameTablePVP(n);
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
			gameWindow.draw(end_board);

            if (!winRecorded) {
                WinnerResult result{};
                logic.playBaiCao(n, playerHands, result);
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