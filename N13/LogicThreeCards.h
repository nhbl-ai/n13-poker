#pragma once
#include "Card.h"
#include "WinnerResult.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
class LogicThreeCards
{
    public:
        vector<Card> createDeck();
        void shuffleDeck(vector<Card>& deck);
        int calculatePoints(const vector<Card>& hand);
        vector<vector<Card>> player_hands_threecard(const vector<Card>& deck, int numPlayers);
        void playBaiCao(int numPlayers, const vector<vector<Card>>& playerCards, WinnerResult& arr);
};

