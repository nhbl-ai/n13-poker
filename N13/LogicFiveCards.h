#pragma once
#include "Card.h"
#include "WinnerResult.h"
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

class LogicFiveCards
{
    public:
        vector<Card> createDeck();
        void shuffleDeck(vector<Card>& deck);
        vector<vector<Card>> player_hands_fivecard(const vector<Card>& deck, int numPlayers);
        void findWinner(const vector<vector<Card>>& players, WinnerResult& arr, const vector<int> a);
    private:
        bool compareCards(const Card& a, const Card& b);
        map<int, int> countRanks(const vector<Card>& hand);
        bool isFlush(const vector<Card>& hand);
        bool isStraight(const vector<Card>& hand, int& topRank);
        pair<int, vector<int>> evaluateHand(vector<Card> hand);
        int compareHands(pair<int, vector<int>> hand1, pair<int, vector<int>> hand2);
};

