#include "SudokuGrid.h"

SudokuGrid::SudokuGrid() {
    for (int i = 0; i < 9; ++i) {
        std::vector<Cell> row;
        for (int j = 0; j < 9; ++j) {
            row.emplace_back();
            row.back().setPosition(600 + j * CELL_SIZE, 25 + i * CELL_SIZE);
        }
        cells.push_back(row);
    }
    selectedCell = nullptr;
}

SudokuGrid::SudokuGrid(int grid[9][9], sf::Font& font) {
    for (int i = 0; i < 9; ++i) {
        std::vector<Cell> row;
        for (int j = 0; j < 9; ++j) {
            row.emplace_back(grid[i][j], (grid[i][j] == 0), font);
            row.back().setPosition(600 + j * CELL_SIZE, 25 + i * CELL_SIZE);
        }
        cells.push_back(row);
    }
    selectedCell = nullptr;
}

void SudokuGrid::draw(sf::RenderWindow& window) {
    for (auto& row : cells) {
        for (auto& cell : row) {
            cell.draw(window);
        }
    }
}

Cell* SudokuGrid::getCellAt(float x, float y) {
    for (auto& row : cells) {
        for (auto& cell : row) {
            if (cell.contains(sf::Vector2f(x, y))) {
                return &cell;
            }
        }
    }
    return nullptr;
}

void SudokuGrid::handleCellSelection(int x, int y) {
	cells[selectedCellY][selectedCellX].deselect();
    if (x >= 0 && x < 9 && y >= 0 && y < 9) {
		selectedCellX = x;
		selectedCellY = y;
        cells[selectedCellY][selectedCellX].select();
    }
}


void SudokuGrid::setCellValue(int x, int y, int value) {
    if (x >= 0 && x < 9 && y >= 0 && y < 9) {
        cells[y][x].setValue(value);
    }
}

