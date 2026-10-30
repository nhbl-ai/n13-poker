#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <chrono>
#include "Card.h"
#include "WinnerResult.h"

class Logic
{
    public:
        vector<Card> createDeck();
        void shuffleDeck(vector<Card>& deck);
        vector<vector<Card>> player_cards(const vector<Card>& deck, int numPlayers);
        vector<Card> community_cards(const vector<Card>& deck, int numPlayers);
        void findWinner(const vector<Card>& communityCards, const vector<vector<Card>>& players, WinnerResult& arr, const vector<int> a);
        void player_point(const vector<Card>& communityCards, const vector<vector<Card>>& players, int* arr);
    private:
        bool compareCards(const Card& a, const Card& b);
        map<int, int> countRanks(const vector<Card>& hand);
        bool isFlush(const vector<Card>& hand, vector<int>& flushRanks);
        bool isStraight(const vector<Card>& hand, int& topRank);
        pair<int, vector<int>> evaluateHand(const vector<Card>& hand);
        int compareHands(pair<int, vector<int>> hand1, pair<int, vector<int>> hand2);
};
