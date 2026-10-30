#include "pokerChooseGame.h"
#include "table.h"
#include "word2.h"
#include "CountNumberPlayers.h" 
#include "Fivecardspoker.h"
#include "ThreeCards.h"
#include <iostream>
#include "Icongame.h"
void pokerChooseGame::showMenu() {
    sf::RenderWindow menuWindow(sf::VideoMode::getDesktopMode(), "Choose Game" , sf::Style::Fullscreen);
    Icongame x;
    x.windowseticon(menuWindow);
    font.loadFromFile("Tajawal-ExtraLight.ttf");
    image.loadFromFile("background.jpg");
    visual.setTexture(image);
    visual.setScale(
        menuWindow.getSize().x / visual.getGlobalBounds().width,
        menuWindow.getSize().y / visual.getGlobalBounds().height
    );

    word2 menu1, menu2, menu3; 
    menu1.play("Five-card Poker", 170, 430);
    menu2.play("Texas Hold'em", 170, 530);
    menu3.play("Three-card Poker", 170, 630);

    while (menuWindow.isOpen()) {
        sf::Event event;
        sf::Vector2i mousepos = sf::Mouse::getPosition(menuWindow);

        while (menuWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                menuWindow.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (menu1.getText().getGlobalBounds().contains(mousepos.x, mousepos.y)) {
                    menuWindow.close();
                    Fivecardspoker menu;
                    int n = 0;
                    GameState currentState = MENU;

                    menu.showMenu(currentState);
                    CountNumberPlayers x;
                    if (currentState == GAME_VS_PLAYER) {
                        n = x.Count();
                        if (n < 2 || n > 6) return;
                        menu.showGameTablePVP(n);
                    }

                }
                else if (menu2.getText().getGlobalBounds().contains(mousepos.x, mousepos.y)) {
                    menuWindow.close();
                    TableWindow menu;
                    int n = 0;
                    GameState currentState = MENU;

                    menu.showMenu(currentState);
                    CountNumberPlayers x;
                    if (currentState == GAME_VS_PLAYER) {
                        n = x.Count();
                        if (n < 2 || n > 6) return;
                        //std::cout << n;
                        menu.showGameTablePVP(n);
                    }
                    else if(currentState == GAME_VS_BOT) {
                        n = x.Count();
                        if (n < 2 || n > 6) return;
                        menu.showGameTablePVE(n);
                    }
                }
                else if (menu3.getText().getGlobalBounds().contains(mousepos.x, mousepos.y)) {
                    menuWindow.close();
                    ThreeCards menu;
                    int n = 0;
                    GameState currentState = MENU;

                    menu.showMenu(currentState);
                    CountNumberPlayers x;
                    if (currentState == GAME_VS_PLAYER) {
                        n = x.Count();
                        if (n < 2 || n > 6) return;
                        menu.showGameTablePVP(n);
                    }
                }
            }
        }
        menuWindow.clear();
        menuWindow.draw(visual);
        menuWindow.draw(menu1.getText());
        menuWindow.draw(menu2.getText());
        menuWindow.draw(menu3.getText());
        menuWindow.display();
    }
}