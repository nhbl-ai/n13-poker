#pragma once
#include "word2.h"
#include <SFML/Graphics.hpp>

class ResultPanel {
public:
    ResultPanel(sf::RenderWindow& window, word2& question, word2& yes, word2& no) {
        const auto size = window.getSize();
        const float width = size.x * 0.84f;
        left = (size.x - width) / 2.f;
        top = (size.y - 260.f) / 2.f;
        panel.setSize({width, 260.f});
        panel.setPosition(left, top);
        panel.setFillColor(sf::Color(12, 24, 20, 245));
        panel.setOutlineColor(sf::Color(210, 185, 110));
        panel.setOutlineThickness(2.f);
        question.play("Do you want to play again?", left + 28.f, top + 105.f);
        question.getText().setCharacterSize(34);
        yes.play("Yes", left + 28.f, top + 175.f);
        no.play("No", left + 220.f, top + 175.f);
        yes.getText().setCharacterSize(38);
        no.getText().setCharacterSize(38);
    }
    void setWinner(word2& winner, const std::string& text) const {
        winner.play(text, left + 28.f, top + 24.f);
        auto& label = winner.getText();
        label.setCharacterSize(44);
        while (label.getGlobalBounds().width > panel.getSize().x - 56.f && label.getCharacterSize() > 20)
            label.setCharacterSize(label.getCharacterSize() - 2);
    }
    void draw(sf::RenderWindow& window) const { window.draw(panel); }
private:
    sf::RectangleShape panel;
    float left = 0.f, top = 0.f;
};
