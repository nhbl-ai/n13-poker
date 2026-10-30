#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include "Card.h"

class GameWindow
{
    public:
        void move_playercard(sf::RenderWindow& gameWindow, int count_player, sf::Sprite background);
        string flig1_player( int turn, vector<vector<Card>> playerHands, /*int count_player, */int tmp);
        string flig_comunitycard(vector<Card> playerHands, /*int count_player,*/ int tmp );
        void move_playercard_5card(sf::RenderWindow& gameWindow, int count_player, sf::Sprite background);
        void move_playercard_3card(sf::RenderWindow& gameWindow, int count_player, sf::Sprite background);
        /*sf::Sprite flig2_player(int turn, vector<sf::Vector2f> destinations, vector<vector<Card>> playerHands, int count_player);  */
    private:
        sf::Vector2f calculateDirection(sf::Vector2f start, sf::Vector2f end);

};


