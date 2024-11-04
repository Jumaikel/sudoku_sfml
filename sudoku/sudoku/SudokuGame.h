#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SudokuGrid.h"

using namespace std;

class SudokuGame {
private:
    sf::RenderWindow window;
    sf::Font font;
    SudokuGrid sudokuGrid;
    int selectedRow = -1;
    int selectedCol = -1;
    sf::RectangleShape backButton;
    sf::RectangleShape saveButton;
    sf::Text backText;
    sf::Text saveText;
    sf::Text nameLabel;
    sf::String nameInput;
    sf::RectangleShape nameInputBox;
    bool isHoveringBackButton = false;
    bool isHoveringSaveButton = false;
    bool isHoveringNameInputBox = false;
    sf::Clock gameClock;
    float elapsedTime;

    bool isNameInputSelected = false;

    string errorMessage;

public:
    SudokuGame();
    void run();
    void processEvents();
    void render();
    void saveGame();

private:
    void handleMouseClick(int x, int y);
    void handleKeyPress(sf::Keyboard::Key key);
    void handleTextInput(sf::Event& event);
};