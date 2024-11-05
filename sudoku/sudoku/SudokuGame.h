#pragma once
#include <SFML/Graphics.hpp>
#include "SudokuGrid.h"

class SudokuGame {
public:
    SudokuGame();
    void run();

private:
    int lastPressedNumber;
    sf::RenderWindow window;
    sf::Font font;
    SudokuGrid* sudokuGrid;

    int selectedRow = -1;
    int selectedCol = -1;

    sf::RectangleShape backButton;
    sf::Text backText;
    sf::RectangleShape saveButton;
    sf::Text saveText;
    sf::Text nameLabel;
    sf::RectangleShape nameInputBox;
    sf::String nameInput;
    bool isNameInputSelected = false;

    sf::Clock gameClock;
    float elapsedTime = 0.0f;
    std::string errorMessage;

    bool isHoveringBackButton = false;
    bool isHoveringSaveButton = false;
    bool isHoveringNameInputBox = false;

    void processEvents();
    void render();
    void handleTextInput(sf::Event& event);
    void handleMouseClick(int x, int y);
    void handleKeyPress(sf::Keyboard::Key key);
    void saveGame();
};
