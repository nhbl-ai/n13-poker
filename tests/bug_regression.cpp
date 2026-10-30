#include "LogicGame.h"
#include "LogicFiveCards.h"
#include "LogicThreeCards.h"
#include "PokerHand.h"
#include "TablePlayers.h"
#include <iostream>
#include <set>
#include <stdexcept>
#include <type_traits>
#ifdef _WIN32
#include <windows.h>
#include <new>
#endif

void check(bool value, const char* label) { if (!value) throw std::runtime_error(label); }
int main() {
    try {
        Logic holdem; LogicFiveCards five; LogicThreeCards three;
        using Hands = std::vector<std::vector<Card>>;
        // Undersized raw buffers no longer satisfy the API at compile time.
        static_assert(!std::is_invocable_v<decltype(&LogicFiveCards::findWinner), LogicFiveCards*, const Hands&, int*, const std::vector<int>>);
        check(evaluateBestPokerHand({{14,'H'},{13,'H'},{12,'H'},{11,'H'},{10,'H'},{2,'C'},{3,'D'}}).first == 10, "royal flush");
        check(evaluateBestPokerHand({{14,'H'},{13,'H'},{12,'H'},{2,'H'},{3,'H'},{11,'D'},{10,'C'}}).first == 6, "flush plus mixed straight");
        check(evaluateBestPokerHand({{14,'H'},{14,'D'},{13,'H'},{13,'D'},{12,'H'},{12,'D'},{2,'C'}}) == PokerScore(3,{14,13,12}), "three pairs");
        check(evaluateBestPokerHand({{14,'H'},{14,'D'},{14,'C'},{13,'H'},{13,'D'},{13,'C'},{2,'S'}}) == PokerScore(7,{14,13}), "two triples full house");
        check(evaluateBestPokerHand({{14,'H'},{2,'D'},{3,'C'},{4,'S'},{5,'H'}}) == PokerScore(5,{5}), "ace-low straight");
        check(evaluateBestPokerHand({{10,'H'},{11,'D'},{12,'C'},{13,'S'},{14,'H'}}) == PokerScore(5,{14}), "ace-high straight");
        check(evaluateBestPokerHand({}).first == 0, "empty hand");
        WinnerResult result{};
        five.findWinner({{{14,'H'},{14,'D'},{13,'C'},{12,'S'},{8,'H'}},{{14,'S'},{14,'C'},{13,'D'},{12,'H'},{7,'C'}}}, result, {0,1});
        check(result[0] == 0 && result[1] == 1, "five-card last kicker");
        holdem.findWinner({{14,'H'},{14,'D'},{13,'C'},{12,'S'},{2,'H'}}, {{{8,'D'},{6,'C'}},{{7,'S'},{5,'D'}}}, result, {0,1});
        check(result[0] == 0 && result[1] == 1, "holdem last kicker");
        holdem.findWinner({{14,'H'},{13,'D'},{12,'C'},{11,'S'},{9,'H'}}, {{{8,'D'},{7,'C'}},{{6,'D'},{5,'S'}}}, result, {0,1});
        check(result[0] == 1 && result[1] == 2 && result[6] == 2, "holdem best five tie");
        check(formatWinners(result, {"QA0","QA1"}) == "Tied: QA0 QA1", "complete tie label");
        // Reusing a result cannot retain a stale tie flag or winner.
        five.findWinner({}, result, {});
        check(result == WinnerResult{}, "empty result clears state");
        check(formatWinners(result,{}) == "No active players", "empty result presentation");
        for (int n = 2; n <= 6; ++n) {
            const Hands hands(n, {{14,'H'},{2,'D'},{3,'C'}});
            three.playBaiCao(n, hands, result);
            check(result[6] == n, "tie count capacity");
            for (int i = 0; i < n; ++i) check(result[i] == i+1, "all tied seats");
            for (bool bots : {false,true}) for (int available : {0,1,2,5,6}) {
                std::vector<std::string> candidates;
                for (int i = 0; i < available; ++i) candidates.push_back("QA"+std::to_string(i+1));
                const auto names = tablePlayerNames("QA0", candidates, n, bots);
                check(names.size() == 6 && names[0] == "QA0", "fixed board capacity");
                std::set<std::string> unique;
                for (int i=0;i<n;++i) { check(!names[i].empty(), "filled table seat"); unique.insert(names[i]); }
                check(static_cast<int>(unique.size()) == n, "unique table names");
            }
        }
        check(holdem.player_cards(holdem.createDeck(),0).empty(), "cancelled player count");
        check(five.player_hands_fivecard({},6).empty(), "short deck");
#ifdef _WIN32
        SYSTEM_INFO info; GetSystemInfo(&info);
        auto memory = static_cast<unsigned char*>(VirtualAlloc(nullptr, info.dwPageSize*2, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE));
        check(memory != nullptr, "guard allocation");
        DWORD old; VirtualProtect(memory+info.dwPageSize,info.dwPageSize,PAGE_NOACCESS,&old);
        auto guarded = new(memory+info.dwPageSize-sizeof(WinnerResult)) WinnerResult{};
        three.playBaiCao(2, {{{14,'H'},{2,'D'},{3,'C'}},{{14,'D'},{2,'C'},{3,'S'}}}, *guarded);
        check((*guarded)[6] == 2, "guarded three-card result");
        five.findWinner({{{14,'H'},{13,'D'},{11,'C'},{8,'S'},{6,'H'}},{{14,'D'},{13,'C'},{11,'S'},{8,'H'},{6,'D'}}}, *guarded, {0,1});
        check((*guarded)[6] == 2, "guarded five-card result");
        holdem.findWinner({{14,'H'},{13,'D'},{12,'C'},{11,'S'},{9,'H'}}, {{{8,'D'},{7,'C'}},{{8,'S'},{7,'D'}}}, *guarded, {0,1});
        check((*guarded)[6] == 2, "guarded holdem result");
        VirtualFree(memory,0,MEM_RELEASE);
#endif
        std::cout << "PASS: scoring, kickers, best five, all ties, guard page, guest/bot seats, invalid input\n";
    } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
