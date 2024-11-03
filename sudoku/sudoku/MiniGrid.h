#pragma once
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include "Cell.h"

using namespace std;

class MiniGrid {
private:
    array<array<Cell, 3>, 3> cells;
    float cellSize;

public:
    MiniGrid();
    MiniGrid(sf::Font& font, float cellSize);
    void setValue(int row, int col, int value);
    int getValue(int row, int col) const;
    void draw(sf::RenderWindow& window, float offsetX, float offsetY);
    void drawFrame(sf::RenderWindow& window, float offsetX, float offsetY);
};


