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
    void generatePuzzle();
    void setValue(int row, int col, int value);
    int getValue(int row, int col) const;
    void draw(sf::RenderWindow& window, float offsetX, float offsetY);
    bool isValidMove(int row, int col, int value) const;
    bool isSafe(int row, int col, int num);
    bool solveGrid();
    void removeCells(int numCells);
    bool isCellEditable(int row, int col) const;
};

