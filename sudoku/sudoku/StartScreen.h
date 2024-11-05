#pragma once
#pragma once
#include <SFML/Graphics.hpp>

class StartScreen {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape playButton;
    sf::RectangleShape loadButton;
    sf::RectangleShape exitButton;
    sf::Text playText;
    sf::Text loadText;
    sf::Text exitText;
    sf::RenderWindow& window;
    sf::Font& font;

    bool isHoveringPlayButton = false;
    bool isHoveringLoadButton = false;
    bool isHoveringExitInputBox = false;

    bool startGame = false;
    bool loadGame = false;
    bool exitGame = false;

public:
    StartScreen( sf::RenderWindow& window, sf::Font& pfont);
    void draw();
    bool shouldStartGame() const;
    bool shouldLoadGame() const;
    bool shouldExit() const;
    void handleMouseClick(int x, int y);
    void processEvents();
   
};

