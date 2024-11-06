#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "GameState.h"

using namespace std;

class LoadScreen {
public:
    LoadScreen(sf::RenderWindow& window, sf::Font& font);
    bool shouldStartGame() const;
    void draw();
    bool shouldGoBack() const;
    GameState getLoadedGameState() const;

private:
    sf::RenderWindow& window;
    sf::RectangleShape backButton;
    sf::Text backText;
    std::vector<std::string> savedGames;
    void loadSavedGames();
    void drawSavedGames();
    void processEvents();
    void handleMouseClick(int x, int y);
    void readSavedGame(const std::string& gameName);
    sf::Font& font;
    bool goBack = false;
	bool startGame = false;
    bool isHoveringBackButton = false;
    std::vector<sf::RectangleShape> buttons;
    GameState loadedGameState;
};


