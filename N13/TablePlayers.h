#pragma once
#include <algorithm>
#include <string>
#include <vector>

// Six entries keep the existing fixed board layout safe; only requested seats play.
inline std::vector<std::string> tablePlayerNames(const std::string& current,
    const std::vector<std::string>& candidates, int requested, bool withBots) {
    std::vector<std::string> names(6);
    if (requested < 2 || requested > 6) return names;
    names[0] = current.empty() ? "Player 1" : current;
    size_t next = 0;
    for (int seat = 1; seat < requested; ++seat) {
        while (next < candidates.size() && (candidates[next].empty() ||
            std::find(names.begin(), names.end(), candidates[next]) != names.end())) ++next;
        if (next < candidates.size()) names[seat] = candidates[next++];
        else {
            int number = seat;
            do { names[seat] = std::string(withBots ? "Bot " : "Guest ") + std::to_string(number++); }
            while (std::find(names.begin(), names.begin() + seat, names[seat]) != names.begin() + seat);
        }
    }
    return names;
}
