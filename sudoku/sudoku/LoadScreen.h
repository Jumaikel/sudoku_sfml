#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class LoadScreen {
public:
    LoadScreen(sf::RenderWindow& window, sf::Font& font);
    void draw();
    bool shouldGoBack() const;

private:
    sf::RenderWindow& window;
    sf::RectangleShape backButton;
    sf::Text backText;
    std::vector<std::string> savedGames;
    void loadSavedGames();
    void drawSavedGames();
    void processEvents();
    void handleMouseClick(int x, int y);
    sf::Font& font;
    bool goBack = false;
    bool isHoveringBackButton = false;
};


