#include "SudokuGrid.h"
#include <set>

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

SudokuGrid::SudokuGrid(vector<vector<int>> grid, vector<vector<int>> solGrid, sf::Font& font) {
    for (int i = 0; i < 9; ++i) {
        std::vector<Cell> row;
        for (int j = 0; j < 9; ++j) {
            row.emplace_back(grid[i][j], (grid[i][j] == 0), font);
            row.back().setPosition(600 + j * CELL_SIZE, 25 + i * CELL_SIZE);
			solutionGrid[i][j] = solGrid[i][j];
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

bool SudokuGrid::isCompleted() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
			cout << solutionGrid[i][j] << " " << cells[i][j].getValue() << endl;
            if (solutionGrid[i][j] != cells[i][j].getValue()) {
                return false;
            }
        }
    }
    return true;
}

void SudokuGrid::fillEmptyCells(const std::vector<std::vector<int>>& fillValues) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (cells[i][j].getValue() == 0 && i < fillValues.size() && j < fillValues[i].size() && fillValues[i][j] != 0) {
                cells[i][j].setValue(fillValues[i][j]);
            }
        }
    }
}

