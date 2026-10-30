#include "PokerHand.h"
#include <algorithm>
#include <functional>

PokerScore evaluateFiveCards(const std::array<Card, 5>& cards) {
    std::array<int, 15> counts{};
    std::vector<int> ranks;
    bool flush = true;
    for (const auto& card : cards) {
        if (card.rank < 2 || card.rank > 14) return {0, {}};
        ++counts[card.rank];
        ranks.push_back(card.rank);
        flush = flush && card.suit == cards[0].suit;
    }
    std::sort(ranks.begin(), ranks.end(), std::greater<int>());
    const bool distinct = std::adjacent_find(ranks.begin(), ranks.end()) == ranks.end();
    int straightTop = distinct && ranks[0] - ranks[4] == 4 ? ranks[0] : 0;
    if (ranks == std::vector<int>{14, 5, 4, 3, 2}) straightTop = 5;
    if (flush && straightTop) return {straightTop == 14 ? 10 : 9, {straightTop}};

    std::vector<std::pair<int, int>> groups;
    for (int rank = 14; rank >= 2; --rank) if (counts[rank]) groups.emplace_back(counts[rank], rank);
    std::sort(groups.rbegin(), groups.rend());
    std::vector<int> kickers;
    for (const auto& group : groups) kickers.push_back(group.second);
    if (groups[0].first == 4) return {8, kickers};
    if (groups[0].first == 3 && groups[1].first == 2) return {7, kickers};
    if (flush) return {6, ranks};
    if (straightTop) return {5, {straightTop}};
    if (groups[0].first == 3) return {4, kickers};
    if (groups[0].first == 2 && groups[1].first == 2) return {3, kickers};
    if (groups[0].first == 2) return {2, kickers};
    return {1, ranks};
}

PokerScore evaluateBestPokerHand(const std::vector<Card>& cards) {
    if (cards.size() < 5 || cards.size() > 7) return {0, {}};
    PokerScore best{0, {}};
    for (size_t a = 0; a + 4 < cards.size(); ++a)
        for (size_t b = a + 1; b + 3 < cards.size(); ++b)
            for (size_t c = b + 1; c + 2 < cards.size(); ++c)
                for (size_t d = c + 1; d + 1 < cards.size(); ++d)
                    for (size_t e = d + 1; e < cards.size(); ++e) {
                        const auto score = evaluateFiveCards({{cards[a], cards[b], cards[c], cards[d], cards[e]}});
                        if (score > best) best = score;
                    }
    return best;
}
