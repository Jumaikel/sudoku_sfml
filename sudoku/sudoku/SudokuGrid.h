#pragma once
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include "MiniGrid.h"
using namespace std;

class SudokuGrid {
private:
    array<array<MiniGrid, 3>, 3> grids;
    float gridSize;

public:
    SudokuGrid(sf::Font& font, float gridSize);
    void setValue(int row, int col, int value);
    int getValue(int row, int col) const;
    bool isValidMove(int row, int col, int value) const;
    void draw(sf::RenderWindow& window);
};

