#pragma once
#include <SFML/Graphics.hpp>
#include "Database.h"
class Register {
public:
    Register();
    void run();
    void import();

private:
    sf::RenderWindow Window;
    sf::Font font;
    void processEvents();
    void update();
    void render();

   // bool verifyUser(const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password);

    sf::RectangleShape registerButton;
    sf::Text registerButtonText;
    sf::RectangleShape showPasswordBox;
    sf::Text showPasswordText;

    sf::Text usernameLabel;
    sf::Text passwordLabel;
    sf::Text confirmPasswordLabel;
    sf::RectangleShape usernameBox;
    sf::RectangleShape passwordBox;
    sf::RectangleShape confirmPasswordBox;
    sf::Text usernameString;
    sf::Text passwordString;
    sf::Text confirmPasswordString;
    sf::Text errorMessage; 
    sf::Texture image;
    sf::Sprite visual; 

    sf::RectangleShape loginButton;
    sf::Text loginButtonText;
    std::string usernameInput;
    std::string passwordInput;
    std::string confirmPasswordInput;
    std::unordered_map<std::string, std::string> users;
    //Database db;

    bool isUsernameActive;
    bool isPasswordActive;
    bool isConfirmPasswordActive;
    bool isRegisterMode;
    bool isMainScreen;
    bool showPassword;

    sf::Clock cursorClock;
};
