#include "MiniGrid.h"

MiniGrid::MiniGrid() : cellSize(80.0f) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            cells[row][col] = Cell();
            cells[row][col].setPosition(col * cellSize, row * cellSize);
        }
    }
}


MiniGrid::MiniGrid(sf::Font& font, float cellSize) : cellSize(cellSize) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            cells[row][col] = Cell(0, true, font);
            cells[row][col].setPosition(col * cellSize, row * cellSize);
        }
    }
}

void MiniGrid::setValue(int row, int col, int value) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        cells[row][col].setValue(value);
    }
    else {
		cout << "Índices de celda fuera de rango" << endl;
    }
}

int MiniGrid::getValue(int row, int col) const {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return cells[row][col].getValue();
    }
    return 0;
}

void MiniGrid::draw(sf::RenderWindow& window, float offsetX, float offsetY) {
    drawFrame(window, offsetX, offsetY);

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            cells[row][col].setPosition(offsetX + col * cellSize, offsetY + row * cellSize);
            cells[row][col].draw(window);
        }
    }
}

void MiniGrid::drawFrame(sf::RenderWindow& window, float offsetX, float offsetY) {
    sf::RectangleShape frame;
    frame.setSize(sf::Vector2f((cellSize - 1) * 3, (cellSize - 1) * 3));
    frame.setPosition(offsetX, offsetY);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color(1, 93, 157));
    frame.setOutlineThickness(4);

    window.draw(frame);
}

bool MiniGrid::isCellEditable(int row, int col) const {
    return cells[row][col].getIsEditable();
}