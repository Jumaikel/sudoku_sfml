#include "MiniGrid.h"

MiniGrid::MiniGrid() : cellSize(10.0f) {

}

MiniGrid::MiniGrid(sf::Font& font, float cellSize = 30.0f) : cellSize(cellSize) {
    // Inicializa cada celda en la cuadr�cula de 3x3
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            // Por defecto, cada celda empieza con valor 0 y es editable
            cells[row][col] = Cell(0, true, font);
            cells[row][col].setPosition(col * cellSize, row * cellSize);
        }
    }
}

// Establece el valor de una celda espec�fica
void MiniGrid::setValue(int row, int col, int value) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        cells[row][col].setValue(value);
    }
}

// Obtiene el valor de una celda espec�fica
int MiniGrid::getValue(int row, int col) const {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return cells[row][col].getValue();
    }
    return 0; // Retorna 0 si los �ndices est�n fuera de rango
}

// Dibuja el MiniGrid en la ventana de SFML, ajustando la posici�n de la subcuadr�cula
void MiniGrid::draw(sf::RenderWindow& window, float offsetX, float offsetY) {
    drawFrame(window, offsetX, offsetY);

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            // Ajusta la posici�n de cada celda dentro de la subcuadr�cula
            cells[row][col].setPosition((offsetX + col * cellSize)+1, (offsetY + row * cellSize)+1);
            cells[row][col].draw(window);
        }
    }
}

void MiniGrid::drawFrame(sf::RenderWindow& window, float offsetX, float offsetY) {
    // Crear un rect�ngulo para el marco
    sf::RectangleShape frame;
    frame.setSize(sf::Vector2f(cellSize * 3, cellSize * 3)); // Ajusta el tama�o del marco
    frame.setPosition(offsetX, offsetY);
    frame.setFillColor(sf::Color::Transparent); // Relleno transparente
    frame.setOutlineColor(sf::Color::Red); // Color del borde
    frame.setOutlineThickness(2.0f); // Grosor del borde

    // Dibujar el marco en la ventana
    window.draw(frame);
}