#include "SudokuGrid.h"

SudokuGrid::SudokuGrid(sf::Font& font, float gridSize = 250.0f) : gridSize(gridSize) {
    // Inicializa cada MiniGrid en la matriz de 3x3
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            // Inicializa el MiniGrid en la posición especificada
            grids[row][col] = MiniGrid(font, gridSize / 3);
        }
    }
}

// Establece el valor en una posición específica de la cuadrícula 9x9
void SudokuGrid::setValue(int row, int col, int value) {
    int miniGridRow = row / 3;
    int miniGridCol = col / 3;
    int cellRow = row % 3;
    int cellCol = col % 3;
    grids[miniGridRow][miniGridCol].setValue(cellRow, cellCol, value);
}

// Obtiene el valor en una posición específica de la cuadrícula 9x9
int SudokuGrid::getValue(int row, int col) const {
    int miniGridRow = row / 3;
    int miniGridCol = col / 3;
    int cellRow = row % 3;
    int cellCol = col % 3;
    return grids[miniGridRow][miniGridCol].getValue(cellRow, cellCol);
}

void SudokuGrid::draw(sf::RenderWindow& window) {
    float offsetX = 300.0f; // Desplazamiento horizontal
    float offsetY = 10.0f;  // Desplazamiento vertical

    // Dibuja cada MiniGrid en la posición con desplazamiento
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            grids[row][col].draw(window, offsetX + col * gridSize, offsetY + row * gridSize);
        }
    }
}


// Método para verificar si una entrada es válida
bool SudokuGrid::isValidMove(int row, int col, int value) const {
    // Comprueba si el valor ya está en la misma fila o columna
    for (int i = 0; i < 9; ++i) {
        if (getValue(row, i) == value || getValue(i, col) == value) {
            return false;
        }
    }

    // Comprueba si el valor ya está en la misma subcuadrícula 3x3
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

bool SudokuGrid::isSafe(int row, int col, int num) {
    // Verifica la fila y la columna
    for (int i = 0; i < 9; ++i) {
        if (getValue(row, i) == num || getValue(i, col) == num) {
            return false;
        }
    }

    // Verifica el bloque 3x3
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (getValue(startRow + i, startCol + j) == num) {
                return false;
            }
        }
    }
    return true;
}


bool SudokuGrid::solveGrid() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (getValue(row, col) == 0) { // Encuentra una celda vacía
                for (int num = 1; num <= 9; ++num) {
                    if (isSafe(row, col, num)) {
                        setValue(row, col, num); // Coloca el número
                        if (solveGrid()) {
                            return true;
                        }
                        setValue(row, col, 0); // Retrocede si no es válido
                    }
                }
                return false;
            }
        }
    }
    return true; // Retorna verdadero si la cuadrícula está completa
}

void SudokuGrid::generatePuzzle() {
    // Llenar la cuadrícula usando backtracking
    solveGrid();

    // Eliminar celdas para crear el rompecabezas
    int numCellsToRemove = 40; // Número de celdas a eliminar (dificultad ajustable)
    removeCells(numCellsToRemove);
}

void SudokuGrid::removeCells(int numCells) {
    int removed = 0;
    while (removed < numCells) {
        int row = rand() % 9;
        int col = rand() % 9;

        if (getValue(row, col) != 0) {
            setValue(row, col, 0); // Elimina el valor de la celda
            removed++;
        }
    }
}

bool SudokuGrid::isCellEditable(int row, int col) const {
    return grids[row / 3][col / 3].isCellEditable(row % 3, col % 3);
}
