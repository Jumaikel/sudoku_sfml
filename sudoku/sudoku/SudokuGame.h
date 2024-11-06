#pragma once
#include <SFML/Graphics.hpp>
#include "SudokuGrid.h"

#include "StartScreen.h"
#include <string>
#include <fstream>
#include <ctime> 

using namespace std;

class SudokuGame {
public:
    SudokuGame(sf::RenderWindow& window, sf::Font& pfont);
    SudokuGame(sf::RenderWindow& window, sf::Font& pfont, vector<vector<int>> initialGrid, vector<vector<int>> grid, vector<vector<int>> solGrid, string name, float elapsedTime);
    void initialize();
    void drawSolutionGrid();
    void run();
    bool shouldGoBack() const;

private:
    int lastPressedNumber;
    sf::RenderWindow& window;
    sf::Font& font;
    SudokuGrid* sudokuGrid;
    sf::Clock clock;
    bool showWinScreen = false;
    bool goBack = false;
    vector<vector<int>> solutionGrid;
    vector<vector<int>> initialGrid;
    sf::Text solutionText;
    bool showSolution = false;
    sf::RectangleShape solutionButton;
    sf::Text solutionButtonText;


    int selectedRow = -1;
    int selectedCol = -1;

    sf::RectangleShape backButton;
    sf::Text backText;
    sf::RectangleShape saveButton;
    sf::Text saveText;
    sf::Text nameLabel;
    sf::RectangleShape nameInputBox;
    sf::String nameInput;
    sf::RectangleShape acceptButton;
    sf::Text acceptText;
    bool isNameInputSelected = false;

    sf::Clock gameClock;
    float elapsedTime = 0.0f;
    std::string message;

    sf::Text messageText;

    bool isHoveringBackButton = false;
    bool isHoveringSaveButton = false;
    bool isHoveringNameInputBox = false;
	bool isHoveringShowSolutionButton = false;  

    void processEvents();
    void render();
    void drawThickLines(sf::RenderWindow& window);
    void handleTextInput(sf::Event& event);
    void handleMouseClick(int x, int y);
    void handleKeyPress(sf::Keyboard::Key key);
    void saveGame();
    void showWindowWin();
    bool isSafe(int row, int col, int num);
    bool solveSudoku();
    void generateSudoku();
};
