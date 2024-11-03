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
    int selectedRow = -1;  // Fila seleccionada por el usuario
    int selectedCol = -1;  // Columna seleccionada por el usuario

public:
    SudokuGame();
    void run();
    void processEvents();
    void update();
    void render();

private:
    void handleMouseClick(int x, int y);
    void handleKeyPress(sf::Keyboard::Key key);
};


