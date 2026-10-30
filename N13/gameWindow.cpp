#include "FrameEvents.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include "gameWindow.h"
#include <SFML/Audio.hpp>

using namespace std;


sf::Vector2f GameWindow::calculateDirection(sf::Vector2f start, sf::Vector2f end) 
{ 
    sf::Vector2f direction = end - start; 
    float length = sqrt(direction.x * direction.x + direction.y * direction.y); 
    if (length != 0) 
    { 
        direction /= length; 
    }
    return direction;
}
void GameWindow::move_playercard_5card(sf::RenderWindow& gameWindow, int count_player, sf::Sprite background)
{
    vector<sf::Vector2f> destinations =
    {
        {925.f,460.f},
        {515.0f, 770.0f},
        {605.0f, 770.0f},
        {695.0f, 770.0f},
        {785.0f, 770.0f},
        {875.0f, 770.0f},
        {1035.0f, 770.0f},
        {1125.0f, 770.0f},
        {1215.0f, 770.0f},
        {1305.0f, 770.0f},
        {1395.0f, 770.0f},
        {1574.0f, 540.0f + 120}, // rotation 90
        {1574.0f, 450.0f + 120}, //rotation 90
        {1574.0f, 360.0f + 120}, //rotation 90
        {1574.0f, 270.0f + 120}, //rotation 90
        {1574.0f, 180.0f + 120}, //rotation 90
        {1395.0f, 170.0f},
        {1305.0f, 170.0f},
        {1215.0f, 170.0f},
        {1125.0f, 170.0f},
        {1035.0f, 170.0f},
        {875.0f, 170.0f},
        {785.0f, 170.0f},
        {695.0f, 170.0f},
        {605.0f, 170.0f},
        {515.0f, 170.0f},
        {340.0f + 200, 540.0f + 120}, //rotation 90 
        {340.0f + 200, 450.0f + 120},  //rotation 90
        {340.0f + 200, 360.0f + 120},  //rotation 90
        {340.0f + 200, 270.0f + 120},  //rotation 90
        {340.0f + 200, 180.0f + 120}  //rotation 90

    };
    float speed = 100.0f;
    size_t currentIndex = 1;
    vector <sf::Sprite> sprite(5 * count_player + 1);
    sf::Texture texture;
    texture.loadFromFile("Back.png");
    sf::Texture carddeck;
    carddeck.loadFromFile("CardDeck.png");
    sprite[0].setTexture(carddeck);
    sprite[0].setPosition(destinations[0]);
    //sprite[0].setScale(0.75f, 0.75f);
    for (int i = 1; i <= 5 * count_player ; i++)
    {
        if ((i >= 11 && i <= 15) || (i >= 26 && i <= 30)) sprite[i].setRotation(90.f);
        sprite[i].setTexture(texture);
        sprite[i].setPosition(destinations[0]);
        //sprite[i].setScale(0.75f,0.75f);
    }
    sf::Vector2f position;
    sf::Vector2f destination;
    sf::Vector2f direction;
    //sf::Clock time;
    while (currentIndex <= count_player * 5 )
    {
        if (!continueCardAnimation(gameWindow)) return;
        bool check = 0;
        //time.restart();
        /*while (time.getElapsedTime().asSeconds() < 0.1f)
        {
            continue;
        }*/
        if (currentIndex <= count_player * 5)
        {
            position = sprite[currentIndex].getPosition();
            destination = destinations[currentIndex];
            direction = calculateDirection(position, destination);
            float distance = sqrt((position.x - destination.x) * (position.x - destination.x) + (position.y - destination.y) * (position.y - destination.y));
            //cout << currentIndex << " " << count_player <<" " << destinations.size() <<" " << distance <<" " << direction.x <<" " << direction.y << "\n";
            if (distance < speed)
            {
                sprite[currentIndex].setPosition(destinations[currentIndex]);
                position = destination;
                check = 1;
            }
            else
            {
                distance /= (direction.x * direction.x + direction.y * direction.y);
                position += (direction * speed) * 5.f / 100.f;
                sprite[currentIndex].setPosition(position);
            }
        }
        gameWindow.clear();
        gameWindow.draw(background);
        //gameWindow.draw(carddeck);
        for (int i = 0; i <= currentIndex; i++)
        {
            //cout << sprite[i].getPosition().x <<" " << sprite[i].getPosition().y << "\n";
            gameWindow.draw(sprite[i]);
        }
        gameWindow.display();
        if (check) ++currentIndex;
    }
    //while (true);
}
void GameWindow::move_playercard_3card(sf::RenderWindow& gameWindow, int count_player, sf::Sprite background)
{
    vector<sf::Vector2f> destinations =
    {
        {925.f,460.f},
        {605.0f, 770.0f},
        {695.0f, 770.0f},
        {785.0f, 770.0f},
        {1125.0f, 770.0f},
        {1215.0f, 770.0f},
        {1305.0f, 770.0f},
        {1574.0f, 450.0f + 120}, //rotation 90
        {1574.0f, 360.0f + 120}, //rotation 90
        {1574.0f, 270.0f + 120}, //rotation 90
        {1305.0f, 170.0f},
        {1215.0f, 170.0f},
        {1125.0f, 170.0f},
        {785.0f, 170.0f},
        {695.0f, 170.0f},
        {605.0f, 170.0f},
        {340.0f + 200, 450.0f + 120},  //rotation 90
        {340.0f + 200, 360.0f + 120},  //rotation 90
        {340.0f + 200, 270.0f + 120},  //rotation 90

    };
    float speed = 100.0f;
    size_t currentIndex = 1;
    vector <sf::Sprite> sprite(3 * count_player + 1);
    sf::Texture texture;
    texture.loadFromFile("Back.png");
    sf::Texture carddeck;
    carddeck.loadFromFile("CardDeck.png");
    sprite[0].setTexture(carddeck);
    sprite[0].setPosition(destinations[0]);
    //sprite[0].setScale(0.75f, 0.75f);
    for (int i = 1; i <= 3 * count_player ; i++)
    {
        if ((i >= 7 && i <= 9) || (i >= 16 && i <= 18)) sprite[i].setRotation(90.f);
        sprite[i].setTexture(texture);
        sprite[i].setPosition(destinations[0]);
        //sprite[i].setScale(0.75f,0.75f);
    }
    sf::Vector2f position;
    sf::Vector2f destination;
    sf::Vector2f direction;
    //sf::Clock time;
    while (currentIndex <= count_player * 3 )
    {
        if (!continueCardAnimation(gameWindow)) return;
        bool check = 0;
        //time.restart();
        /*while (time.getElapsedTime().asSeconds() < 0.1f)
        {
            continue;
        }*/
        if (currentIndex <= count_player * 3)
        {
            position = sprite[currentIndex].getPosition();
            destination = destinations[currentIndex];
            direction = calculateDirection(position, destination);
            float distance = sqrt((position.x - destination.x) * (position.x - destination.x) + (position.y - destination.y) * (position.y - destination.y));
            //cout << currentIndex << " " << count_player <<" " << destinations.size() <<" " << distance <<" " << direction.x <<" " << direction.y << "\n";
            if (distance < speed)
            {
                sprite[currentIndex].setPosition(destinations[currentIndex]);
                position = destination;
                check = 1;
            }
            else
            {
                distance /= (direction.x * direction.x + direction.y * direction.y);
                position += (direction * speed) * 5.f / 100.f;
                sprite[currentIndex].setPosition(position);
            }
        }
        gameWindow.clear();
        gameWindow.draw(background);
        //gameWindow.draw(carddeck);
        for (int i = 0; i <= currentIndex; i++)
        {
            //cout << sprite[i].getPosition().x <<" " << sprite[i].getPosition().y << "\n";
            gameWindow.draw(sprite[i]);
        }
        gameWindow.display();
        if (check) ++currentIndex;
    }
    //while (true);
}
void GameWindow::move_playercard(sf::RenderWindow& gameWindow, int count_player, sf::Sprite background)
{
    vector<sf::Vector2f> destinations = 
    {
        {925.0f, 160.0f},
        {780.0f, 460.0f},
        {865.0f, 460.0f},
        {950.0f, 460.0f},
        {1035.0f, 460.0f},
        {1120.0f, 460.0f},
        {615.0f, 770.0f},
        {705.0f, 770.0f},
        {1135.0f, 770.0f},
        {1225.0f, 770.0f},
        {1674.0f, 540.0f}, // rotation 90
        {1674.0f, 450.0f}, //rotation 90
        {1235.0f, 170.0f},
        {1145.0f, 170.0f},
        {710.0f, 170.0f},
        {620.0f, 170.0f},
        {440.0f, 435.0f}, //rotation 90 
        {440.0f, 525.0f}  //rotation 90
        
    };
    float speed = 100.0f;
    size_t currentIndex = 1 ;
    vector <sf::Sprite> sprite(2*count_player + 6);
    sf::Texture texture;
    texture.loadFromFile("Back.png");
    sf::Texture carddeck;
    carddeck.loadFromFile("CardDeck.png");
    sprite[0].setTexture(carddeck);
    sprite[0].setPosition(destinations[0]);
    //sprite[0].setScale(0.75f, 0.75f);
    for (int i = 1; i <= 2 * count_player + 5; i++)
    {
        if (i == 10 || i == 11 || i == 16 || i == 17) sprite[i].setRotation(90.f);
        sprite[i].setTexture(texture);
        sprite[i].setPosition(destinations[0]);
        //sprite[i].setScale(0.75f,0.75f);
    }
    sf::Vector2f position;
    sf::Vector2f destination;
    sf::Vector2f direction;
    //sf::Clock time;
    while (currentIndex <= count_player * 2 + 5)
    {
        if (!continueCardAnimation(gameWindow)) return;
        bool check = 0;
        //time.restart();
        /*while (time.getElapsedTime().asSeconds() < 0.1f)
        {
            continue;
        }*/
        if (currentIndex <= count_player * 2 + 5)
        {
            position = sprite[currentIndex].getPosition();
            destination = destinations[currentIndex];
            direction = calculateDirection(position, destination);
            float distance = sqrt((position.x - destination.x) * (position.x - destination.x) + (position.y - destination.y) * (position.y - destination.y));
            //cout << currentIndex << " " << count_player <<" " << destinations.size() <<" " << distance <<" " << direction.x <<" " << direction.y << "\n";
            if (distance < speed)
            {
                sprite[currentIndex].setPosition(destinations[currentIndex]);
                position = destination;
                check = 1;
            }
            else
            {
                distance /= (direction.x * direction.x + direction.y * direction.y);
                position += (direction * speed ) * 5.f/100.f;
                sprite[currentIndex].setPosition(position);
            }
        }
        gameWindow.clear();
        gameWindow.draw(background);
        for (int i = 0; i <= currentIndex; i++)
        {
            //cout << sprite[i].getPosition().x <<" " << sprite[i].getPosition().y << "\n";
            gameWindow.draw(sprite[i]);
        }
        gameWindow.display();
        if (check) ++currentIndex;
    }
    //while (true);
}

string GameWindow::flig1_player(int turn, vector<vector<Card>> playerHands, /*int count_player ,*/ int tmp)
{
    //sf::Texture test;
    //test.loadFromFile("Back.png");
    //sf::Vector2u textureSize = test.getSize(); // width, height của texture

    //// Kích thước mong muốn của sprit

    //// Tính toán tỷ lệ cần thiết
    //float scaleX =textureSize.x;
    //float scaleY =textureSize.y;

    // Áp dụng tỷ lệ vào sprite
    Card card = playerHands[turn][tmp];

    string rank;
    string suit;

    if(card.rank == 2)
    {
        rank = "2";
    }
    if(card.rank == 3)
    {
        rank = "3";
    }
    if(card.rank == 4)
    {
        rank = "4";
    }
    if(card.rank == 5)
    {
        rank = "5";
    }
    if(card.rank == 6)
    {
        rank = "6";
    }
    if(card.rank == 7)
    {
        rank = "7";
    }
    if(card.rank == 8)
    {
        rank = "8";
    }
    if(card.rank == 9)
    {
        rank = "9";
    }
    if(card.rank == 10)
    {
        rank = "10";
    }
    if(card.rank == 11)
    {
        rank = "jack";
    }
    if(card.rank == 12)
    {
        rank = "queen";
    }
    if(card.rank == 13)
    {
        rank = "king";
    }
    if(card.rank == 14)
    {
        rank = "ace";
    }
    if(card.suit == 'H')
    {
        suit = "hearts";
    }
    if(card.suit == 'D')
    {
        suit = "diamonds";
    }
    if(card.suit == 'C')
    {
        suit = "clubs";
    }
    if(card.suit == 'S')
    {
        suit = "spades";
    }


    string str = rank + "_of_" + suit + ".png";
    
    return str;

    // sf::Texture texture;
    // texture.loadFromFile(str);

    // sprite.setTexture(texture);
    // sprite.setScale(0.2f, 0.2f);
    // sprite.setPosition(destinations[cnt]);

}
string GameWindow::flig_comunitycard(vector < Card > playerHands, /*int count_player ,*/ int tmp )
{
    Card card = playerHands[tmp];
    //std::cout << card.rank << " " << card.suit << " " << tmp << "\n";
    string rank;
    string suit;

    if(card.rank == 2)
    {
        rank = "2";
    }
    if(card.rank == 3)
    {
        rank = "3";
    }
    if(card.rank == 4)
    {
        rank = "4";
    }
    if(card.rank == 5)
    {
        rank = "5";
    }
    if(card.rank == 6)
    {
        rank = "6";
    }
    if(card.rank == 7)
    {
        rank = "7";
    }
    if(card.rank == 8)
    {
        rank = "8";
    }
    if(card.rank == 9)
    {
        rank = "9";
    }
    if(card.rank == 10)
    {
        rank = "10";
    }
    if(card.rank == 11)
    {
        rank = "jack";
    }
    if(card.rank == 12)
    {
        rank = "queen";
    }
    if(card.rank == 13)
    {
        rank = "king";
    }
    if(card.rank == 14)
    {
        rank = "ace";
    }
    if(card.suit == 'H')
    {
        suit = "hearts";
    }
    if(card.suit == 'D')
    {
        suit = "diamonds";
    }
    if(card.suit == 'C')
    {
        suit = "clubs";
    }
    if(card.suit == 'S')
    {
        suit = "spades";
    }

    string str = rank + "_of_" + suit + ".png";
    //std::cout << rank <<" " << str << "\n";
    return str;

    // sf::Texture texture;

    // texture.loadFromFile(str);

    // sprite.setTexture(texture);

    // sprite.setPosition(destinations[tmp]);
    // sprite.setScale(0.5f, 0.5f);
}

//sf::Sprite GameWindow::flig2_player(int turn, vector<sf::Vector2f> destinations, vector<vector<Card>> playerHands, int count_player)
//{
//    Card card = playerHands[turn][1];
//
//    string str = card.rank + "_of_" + card.suit + ".png";
//
//    sf::Texture texture;
//
//    texture.loadFromFile(str);
//
//    sf::Sprite sprite;
//
//    sprite.setTexture(texture);
//
//    sprite.setPosition(destinations[18 - 2 * (count_player - turn) + 1]);
//    sprite.setScale(0.2f, 0.2f);
//    
//    return sprite;
//}


//void flig_comunitycard()
//{
//    
//}

