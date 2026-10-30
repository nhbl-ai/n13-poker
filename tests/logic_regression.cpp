#include <map>
#include "LogicGame.h"
#include "LogicFiveCards.h"
#include "LogicThreeCards.h"
#include <array>
#include <cstdint>
#include <iostream>
#include <random>
#include <set>
#include <stdexcept>

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
bool same(const Card& a, const Card& b) { return a.rank == b.rank && a.suit == b.suit; }

int main() {
    try {
        Logic holdem;
        LogicFiveCards five;
        LogicThreeCards three;
        auto deck = holdem.createDeck();
        require(deck.size() == 52, "deck size");
        std::set<std::pair<int, char>> unique;
        for (const auto& card : deck) unique.emplace(card.rank, card.suit);
        require(unique.size() == 52, "deck uniqueness");
        for (const auto& other : {five.createDeck(), three.createDeck()}) {
            require(std::equal(deck.begin(), deck.end(), other.begin(), same), "deck order changed");
        }
        for (int count = 2; count <= 6; ++count) {
            auto hands = holdem.player_cards(deck, count);
            auto cao = three.player_hands_threecard(deck, count);
            const auto hands5 = five.player_hands_fivecard(deck, count);
            for (int p = 0; p < count; ++p)
                for (int c = 0; c < 5; ++c) require(same(hands5[p][c], deck[p + count*c]), "five-card dealing");
            for (int p = 0; p < count; ++p) {
                for (int c = 0; c < 2; ++c) require(same(hands[p][c], deck[p + count*c]), "holdem dealing");
                for (int c = 0; c < 3; ++c) require(same(cao[p][c], deck[p + count*c]), "three-card dealing");
            }
            const auto community = holdem.community_cards(deck, count);
            for (int c = 0; c < 5; ++c) require(same(community[c], deck[count*2+c]), "community dealing");
        }
        require(three.calculatePoints({{11,'H'},{12,'D'},{13,'S'}}) == 10, "three faces");
        require(three.calculatePoints({{14,'H'},{2,'D'},{3,'S'}}) == 6, "ace value");
        require(three.calculatePoints({{10,'H'},{12,'D'},{9,'S'}}) == 9, "modulo points");
        std::array<int,8> result{};
        three.playBaiCao(2, {{{11,'H'},{12,'D'},{13,'S'}},{{14,'H'},{2,'D'},{3,'S'}}}, result);
        require(result[0] == 0 && result[1] == 1, "three-card winner");
        result.fill(0);
        three.playBaiCao(2, {{{14,'H'},{2,'D'},{3,'S'}},{{14,'D'},{2,'S'},{3,'H'}}}, result);
        require(result[0] == 1 && result[1] == 2 && result[6] == 2, "three-card tie");

        const std::vector<Card> high = {{2,'H'},{4,'D'},{6,'S'},{8,'C'},{11,'H'}};
        const std::vector<std::vector<Card>> categories = {
            {{10,'H'},{11,'H'},{12,'H'},{13,'H'},{14,'H'}},
            {{5,'H'},{6,'H'},{7,'H'},{8,'H'},{9,'H'}},
            {{14,'H'},{14,'D'},{14,'C'},{14,'S'},{2,'H'}},
            {{13,'H'},{13,'D'},{13,'C'},{2,'S'},{2,'H'}},
            {{2,'H'},{4,'H'},{6,'H'},{8,'H'},{12,'H'}},
            {{14,'H'},{2,'D'},{3,'C'},{4,'S'},{5,'H'}},
            {{12,'H'},{12,'D'},{12,'C'},{2,'S'},{4,'H'}},
            {{12,'H'},{12,'D'},{11,'C'},{11,'S'},{4,'H'}},
            {{12,'H'},{12,'D'},{3,'C'},{7,'S'},{4,'H'}}
        };
        for (size_t i = 0; i < categories.size(); ++i) {
            result.fill(0);
            five.findWinner({categories[i], high}, result, {0,1});
            require(result[0] == 0 && result[1] == 1 && result[2] == 10-static_cast<int>(i), "five-card ranking");
        }
        result.fill(0);
        five.findWinner({high, high}, result, {0,1});
        require(result[0] == 1 && result[1] == 2 && result[6] == 2, "five-card tie");
        const std::vector<Card> board = {{2,'H'},{4,'D'},{6,'C'},{8,'S'},{10,'H'}};
        result.fill(0);
        holdem.findWinner(board, {{{12,'D'},{14,'C'}},{{11,'S'},{13,'D'}}}, result, {0,1});
        require(result[0] == 0 && result[1] == 1, "holdem winner");
        result.fill(0);
        holdem.findWinner(board, {{{12,'D'},{14,'C'}},{{12,'S'},{14,'D'}}}, result, {0,1});
        require(result[0] == 1 && result[1] == 2 && result[6] == 2, "holdem tie");

        // Stable inputs exercise all three games, including repeated ranks.
        std::mt19937 engine(24127201);
        std::uint64_t digest = 1469598103934665603ULL;
        auto record = [&]() { for (int value : result) { digest ^= static_cast<unsigned>(value); digest *= 1099511628211ULL; } };
        int accepted = 0;
        for (int trial = 0; trial < 500; ++trial) {
            std::shuffle(deck.begin(), deck.end(), engine);
            std::vector<std::vector<Card>> hands5 = {{deck.begin(),deck.begin()+5},{deck.begin()+5,deck.begin()+10}};
            result.fill(0);
            five.findWinner(hands5, result, {0,1}); record();
            auto cao = three.player_hands_threecard(deck, 6);
            result.fill(0);
            three.playBaiCao(6, cao, result); record();
            const auto community = holdem.community_cards(deck, 2);
            const auto hands = holdem.player_cards(deck, 2);
            result.fill(0);
            holdem.findWinner(community, hands, result, {0,1}); record();
            ++accepted;
        }
        auto shuffled = holdem.createDeck();
        holdem.shuffleDeck(shuffled);
        unique.clear();
        for (auto c : shuffled) unique.emplace(c.rank,c.suit);
        require(shuffled.size() == 52 && unique.size() == 52, "shuffle permutation");
        std::cout << "PASS: deck, dealing, scoring, ranking, winners, ties, shuffle\n";
        std::cout << "Regression transcript: " << digest << "; holdem cases: " << accepted << "; five-card/three-card cases: 1000\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}

