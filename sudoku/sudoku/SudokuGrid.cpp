#include "SudokuGrid.h"

SudokuGrid::SudokuGrid(sf::Font& font, float gridSize = 250.0f) : gridSize(gridSize) {
    // Inicializa cada MiniGrid en la matriz de 3x3
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            // Inicializa el MiniGrid en la posici�n especificada
            grids[row][col] = MiniGrid(font, gridSize / 3);
        }
    }
}

// Establece el valor en una posici�n espec�fica de la cuadr�cula 9x9
void SudokuGrid::setValue(int row, int col, int value) {
    int miniGridRow = row / 3;
    int miniGridCol = col / 3;
    int cellRow = row % 3;
    int cellCol = col % 3;
    grids[miniGridRow][miniGridCol].setValue(cellRow, cellCol, value);
}

// Obtiene el valor en una posici�n espec�fica de la cuadr�cula 9x9
int SudokuGrid::getValue(int row, int col) const {
    int miniGridRow = row / 3;
    int miniGridCol = col / 3;
    int cellRow = row % 3;
    int cellCol = col % 3;
    return grids[miniGridRow][miniGridCol].getValue(cellRow, cellCol);
}

void SudokuGrid::draw(sf::RenderWindow& window) {


    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            // Calcula la posici�n de cada MiniGrid
            float offsetX = (col) * gridSize;
            float offsetY = (row) * gridSize;
            grids[row][col].draw(window, offsetX + 300, offsetY + 10);
        }
    }
}

// M�todo para verificar si una entrada es v�lida
bool SudokuGrid::isValidMove(int row, int col, int value) const {
    // Comprueba si el valor ya est� en la misma fila o columna
    for (int i = 0; i < 9; ++i) {
        if (getValue(row, i) == value || getValue(i, col) == value) {
            return false;
        }
    }

    // Comprueba si el valor ya est� en la misma subcuadr�cula 3x3
    int miniGridRow = row / 3;
    int miniGridCol = col / 3;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (grids[miniGridRow][miniGridCol].getValue(r, c) == value) {
                return false;
            }
        }
    }
    return true;
}