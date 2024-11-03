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

private:
    void processEvents();
    void handleMouseClick(int mouseX, int mouseY);
    void handleKeyInput(sf::Keyboard::Key key);
    void update();
    void render();
};


