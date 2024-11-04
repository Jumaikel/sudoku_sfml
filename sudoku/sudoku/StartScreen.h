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

public:
    StartScreen(sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isPlayButtonClicked(const sf::Vector2f& mousePos) const;
    bool isLoadButtonClicked(const sf::Vector2f& mousePos) const;
    bool isExitButtonClicked(const sf::Vector2f& mousePos) const;
};

