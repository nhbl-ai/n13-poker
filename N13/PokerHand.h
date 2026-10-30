#pragma once
#include "Card.h"
#include <array>
#include <utility>
#include <vector>

using PokerScore = std::pair<int, std::vector<int>>;
PokerScore evaluateFiveCards(const std::array<Card, 5>& cards);
PokerScore evaluateBestPokerHand(const std::vector<Card>& cards);
