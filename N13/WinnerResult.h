#pragma once
#include <array>
#include <string>
#include <vector>

// Existing result layout, now with a compile-time capacity for all six seats.
// Unique: [0]=0, [1]=one-based seat, [2]=category.
// Tie: [0..count-1]=one-based seats, [6]=count, [7]=category.
using WinnerResult = std::array<int, 8>;

inline WinnerResult makeWinnerResult(const std::vector<int>& seats, int category = 0) {
    WinnerResult result{};
    if (seats.size() == 1) { result[1] = seats[0]; result[2] = category; }
    else if (!seats.empty()) {
        result[6] = static_cast<int>(seats.size() < 6 ? seats.size() : 6);
        for (int i = 0; i < result[6]; ++i) result[i] = seats[i];
        result[7] = category;
    }
    return result;
}

inline std::string formatWinners(const WinnerResult& result, const std::vector<std::string>& names) {
    if (result[0] == 0) {
        const int seat = result[1];
        return seat > 0 && static_cast<size_t>(seat) <= names.size()
            ? "Winner is: " + names[seat - 1] : "No active players";
    }
    std::string text = "Tied:";
    for (int i = 0; i < result[6] && i < 6; ++i) {
        const int seat = result[i];
        if (seat > 0 && static_cast<size_t>(seat) <= names.size()) text += " " + names[seat - 1];
    }
    return text;
}
