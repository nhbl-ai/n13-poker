#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

// Always process Close, including countdowns and result screens. Other events
// remain queued for the existing betting/result handlers in the current frame.
class FrameEvents {
public:
    explicit FrameEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); break; }
            events.push_back(event);
        }
    }
    bool poll(sf::Event& event) {
        if (events.empty()) return false;
        event = events.front(); events.pop_front(); return true;
    }
private:
    std::deque<sf::Event> events;
};

inline bool continueCardAnimation(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) if (event.type == sf::Event::Closed) { window.close(); return false; }
    return window.isOpen();
}
