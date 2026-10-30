#include "PokerHand.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <tuple>
#include "LogicGame.h"

using namespace std;

vector<Card> Logic::createDeck() 
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

void Logic::shuffleDeck(std::vector<Card>& deck) 
{  
    auto seed = static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count()); 
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

vector<vector<Card>> Logic::player_cards(const vector<Card>& deck, int numPlayers) 
{
    if (numPlayers < 1 || numPlayers > 6 || deck.size() < static_cast<size_t>(numPlayers * 2 + 5)) return {};
    vector<vector<Card>> playerHands(numPlayers);
    
    int index = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < numPlayers; ++j) {
            playerHands[j].push_back(deck[index++]);
        }
    }

    return playerHands;
}

vector<Card> Logic::community_cards(const vector<Card>& deck, int numPlayers)
{
    if (numPlayers < 1 || numPlayers > 6 || deck.size() < static_cast<size_t>(numPlayers * 2 + 5)) return {};
    vector<Card> communityCards;
    int index = numPlayers * 2;
    for (int i = 0; i < 5; ++i) {
        communityCards.push_back(deck[index++]);
    }

    return communityCards;
}

bool Logic::compareCards(const Card& a, const Card& b) {
    return a.rank > b.rank;
}

map<int, int> Logic::countRanks(const vector<Card>& hand) {
    map<int, int> rankCount;
    for (const auto& card : hand) {
        rankCount[card.rank]++;
    }
    return rankCount;
}

bool Logic::isFlush(const vector<Card>& hand, vector<int>& flushRanks) {
    map <char, vector <int> > suits;
    for (const auto& card : hand) {
       suits[card.suit].push_back(card.rank);
    }
    for (auto& pair : suits) {
        char suit = pair.first;
        vector<int>& ranks = pair.second;
        if (ranks.size() >= 5) {
            sort(ranks.rbegin(), ranks.rend());
            flushRanks.assign(ranks.begin(), ranks.begin() + 5);
            return true;
        }
    }
    return false;
}

bool Logic::isStraight(const vector<Card>& hand, int& topRank) {
    vector<int> ranks;
    for (const auto& card : hand) {
        ranks.push_back(card.rank);
    }
    sort(ranks.rbegin(), ranks.rend());
    ranks.erase(unique(ranks.begin(), ranks.end()), ranks.end());

    for (size_t i = 0; i + 4 < ranks.size(); ++i) {
        if (ranks[i] - ranks[i + 4] == 4) {
            topRank = ranks[i];
            return true;
        }
    }

    if (find(ranks.begin(), ranks.end(), 14) != ranks.end() && find(ranks.begin(), ranks.end(), 5) != ranks.end() && find(ranks.begin(), ranks.end(), 4) != ranks.end() && find(ranks.begin(), ranks.end(), 3) != ranks.end() && find(ranks.begin(), ranks.end(), 2) != ranks.end()) {
        topRank = 5;
        return true;
    }

    return false;
}

pair<int, vector<int>> Logic::evaluateHand(const vector<Card>& hand) {
    return evaluateBestPokerHand(hand);
}

int Logic::compareHands(pair<int, vector<int>> hand1, pair<int, vector<int>> hand2) {
    return hand1 == hand2 ? 0 : (hand1 > hand2 ? 1 : -1);
}

void Logic::findWinner(const vector<Card>& communityCards, const vector<vector<Card>>& players, WinnerResult& arr, const vector<int> a) {
    PokerScore best{0, {}};
    vector<int> winners;
    vector<bool> seen(players.size(), false);
    for (int seat : a) {
        if (seat < 0 || static_cast<size_t>(seat) >= players.size() || seen[seat]) continue;
        seen[seat] = true;
        auto fullHand = communityCards;
        fullHand.insert(fullHand.end(), players[seat].begin(), players[seat].end());
        const auto score = evaluateHand(fullHand);
        if (score.first == 0) continue;
        if (score > best) { best = score; winners = {seat + 1}; }
        else if (score == best) winners.push_back(seat + 1);
    }
    arr = makeWinnerResult(winners, best.first);
}

void Logic::player_point(const vector<Card>& communityCards, const vector<vector<Card>>& players, int* arr) {
    
    for (int i = 0; i < players.size(); ++i) {
        vector<Card> fullHand = communityCards;
        fullHand.insert(fullHand.end(), players[i].begin(), players[i].end());
        pair<int, vector<int>> handRank = evaluateHand(fullHand);
        arr[i] = handRank.first;
    }
}




