#include "PokerHand.h"
#include "LogicFiveCards.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <chrono>
#include "Card.h"

using namespace std;

vector<Card> LogicFiveCards::createDeck() 
{
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

void LogicFiveCards::shuffleDeck(std::vector<Card>& deck) 
{  
    auto seed = static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count()); 
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

vector<vector<Card>> LogicFiveCards::player_hands_fivecard(const vector<Card>& deck, int numPlayers)
{
    if (numPlayers < 1 || numPlayers > 6 || deck.size() < static_cast<size_t>(numPlayers * 5 + 0)) return {};
    vector<vector<Card>> playerCards(numPlayers);
    int index = 0;
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < numPlayers; ++j) {
            playerCards[j].push_back(deck[index++]);
        }
    }
    return playerCards;
}

bool LogicFiveCards::compareCards(const Card& a, const Card& b) {
    return a.rank > b.rank;
}

map<int, int> LogicFiveCards::countRanks(const vector<Card>& hand) {
    map<int, int> rankCount;
    for (const auto& card : hand) {
        rankCount[card.rank]++;
    }
    return rankCount;
}

bool LogicFiveCards::isFlush(const vector<Card>& hand) {
    if (hand.empty()) return false;
    char suit = hand[0].suit;
    for (const auto& card : hand) {
        if (card.suit != suit) return false;
    }
    return true;
}

bool LogicFiveCards::isStraight(const vector<Card>& hand, int& topRank) {
    vector<int> ranks;
    for (const auto& card : hand) {
        ranks.push_back(card.rank);
    }
    sort(ranks.rbegin(), ranks.rend());
    ranks.erase(unique(ranks.begin(), ranks.end()), ranks.end());

    if (ranks.size() != 5) return false;

    if (ranks[0] - ranks[4] == 4) {
        topRank = ranks[0];
        return true;
    }

    if (ranks[0] == 14 && ranks[1] == 5 && ranks[2] == 4 && ranks[3] == 3 && ranks[4] == 2) {
        topRank = 5;
        return true;
    }

    return false;
}

pair<int, vector<int>> LogicFiveCards::evaluateHand(vector<Card> hand) {
    return evaluateBestPokerHand(hand);
}

int LogicFiveCards::compareHands(pair<int, vector<int>> hand1, pair<int, vector<int>> hand2) {
    return hand1 == hand2 ? 0 : (hand1 > hand2 ? 1 : -1);
}

void LogicFiveCards::findWinner(const vector<vector<Card>>& players, WinnerResult& arr, const vector<int> a) {
    PokerScore best{0, {}};
    vector<int> winners;
    vector<bool> seen(players.size(), false);
    for (int seat : a) {
        if (seat < 0 || static_cast<size_t>(seat) >= players.size() || seen[seat]) continue;
        seen[seat] = true;
        const auto score = evaluateHand(players[seat]);
        if (score.first == 0) continue;
        if (score > best) { best = score; winners = {seat + 1}; }
        else if (score == best) winners.push_back(seat + 1);
    }
    arr = makeWinnerResult(winners, best.first);
}

