#include "LogicThreeCards.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>

#include "Card.h"

using namespace std;

vector<Card> LogicThreeCards::createDeck() {
    vector<Card> deck;
    vector<char> suits = {'H', 'D', 'C', 'S'};
    vector<int> ranks = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    
    for (const auto& rank : ranks) {
        for (const auto& suit : suits) {
            deck.push_back({rank, suit});
        }
    }
    return deck;
}

void LogicThreeCards::shuffleDeck(vector<Card>& deck) {
    auto seed = static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count()); 
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

int LogicThreeCards::calculatePoints(const vector<Card>& hand) {
    int total = 0;
    int count = 0;
    for (const auto& card : hand) {
        if (card.rank >= 11 && card.rank <= 13)
        {
            ++count;
        }
        total += (card.rank == 14 ? 1 : (card.rank >= 11 ? 10 : card.rank)); 
    }
    if (count == 3)
    {
        return 10;
    }
    return total % 10;
}

vector<vector<Card>> LogicThreeCards::player_hands_threecard(const vector<Card>& deck, int numPlayers)
{
    if (numPlayers < 1 || numPlayers > 6 || deck.size() < static_cast<size_t>(numPlayers * 3 + 0)) return {};
    vector<vector<Card>> playerCards(numPlayers);
    int index = 0 ;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < numPlayers; ++j)
        {
            playerCards[j].push_back(deck[index++]);
        }
    }

    return playerCards;
}

void LogicThreeCards::playBaiCao(int numPlayers, const vector<vector<Card>>& playerCards, WinnerResult& arr) {
    arr.fill(0);
    if (numPlayers < 1 || numPlayers > 6 || static_cast<size_t>(numPlayers) > playerCards.size()) return;
    int best = -1;
    vector<int> winners;
    for (int i = 0; i < numPlayers; ++i) {
        if (playerCards[i].size() != 3) return;
        const int points = calculatePoints(playerCards[i]);
        if (points > best) { best = points; winners = {i + 1}; }
        else if (points == best) winners.push_back(i + 1);
    }
    arr = makeWinnerResult(winners, best);
}

