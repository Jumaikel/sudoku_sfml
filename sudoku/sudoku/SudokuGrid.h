#pragma once
#include <iostream>
#include <array>
#include <random>
#include <SFML/Graphics.hpp>
#include "Cell.h"

class SudokuGrid {
public:
    SudokuGrid();
    SudokuGrid(vector<vector<int>> grid, vector<vector<int>> solGrid, sf::Font& font);
    void draw(sf::RenderWindow& window);
    Cell* getCellAt(float x, float y);
    void handleCellSelection(int x, int y);
    void setCellValue(int x, int y, int value); 
    bool isCompleted();
    std::vector<std::vector<int>> getCurrentGrid() const;

private:
    std::vector<std::vector<Cell>> cells;
    Cell* selectedCell;
    int selectedCellX;
    int selectedCellY;
    const float CELL_SIZE = 80.0f;
    int solutionGrid[9][9];
};