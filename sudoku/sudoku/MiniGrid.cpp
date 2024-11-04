#include "MiniGrid.h"

MiniGrid::MiniGrid() : cellSize(80.0f) {
    // Inicializa cada celda en la cuadrícula de 3x3
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            // Por defecto, cada celda empieza con valor 0 y es editable
            cells[row][col] = Cell(); // Aquí necesitas una referencia a 'font', por lo que esto no funcionará
            cells[row][col].setPosition(col * cellSize, row * cellSize);
        }
    }
}


MiniGrid::MiniGrid(sf::Font& font, float cellSize) : cellSize(cellSize) {
    // Inicializa cada celda en la cuadrícula de 3x3
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            // Por defecto, cada celda empieza con valor 0 y es editable
            cells[row][col] = Cell(0, true, font);
            cells[row][col].setPosition(col * cellSize, row * cellSize);
        }
    }
}

// Establece el valor de una celda específica
void MiniGrid::setValue(int row, int col, int value) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        cells[row][col].setValue(value);
    }
    else {
        // Manejo de error (puedes lanzar una excepción o imprimir un mensaje)
    }
}

// Obtiene el valor de una celda específica
int MiniGrid::getValue(int row, int col) const {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return cells[row][col].getValue();
    }
    return 0; // Retorna 0 si los índices están fuera de rango
}

// Dibuja el MiniGrid en la ventana de SFML, ajustando la posición de la subcuadrícula
void MiniGrid::draw(sf::RenderWindow& window, float offsetX, float offsetY) {
    drawFrame(window, offsetX, offsetY);

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            // Ajusta la posición de cada celda con el desplazamiento adicional
            cells[row][col].setPosition(offsetX + col * cellSize, offsetY + row * cellSize);
            cells[row][col].draw(window);
        }
    }
}

void MiniGrid::drawFrame(sf::RenderWindow& window, float offsetX, float offsetY) {
    // Crear un rectángulo para el marco
    sf::RectangleShape frame;
    frame.setSize(sf::Vector2f((cellSize - 1) * 3, (cellSize - 1) * 3)); // Ajusta el tamaño del marco
    frame.setPosition(offsetX, offsetY);
    frame.setFillColor(sf::Color::Transparent); // Relleno transparente
    frame.setOutlineColor(sf::Color(1, 93, 157)); // Color del borde
    frame.setOutlineThickness(4); // Grosor del borde

    // Dibujar el marco en la ventana
    window.draw(frame);
}

bool MiniGrid::isCellEditable(int row, int col) const {
    return cells[row][col].getIsEditable();
}