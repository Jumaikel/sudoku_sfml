#include "SudokuGame.h"

// Posición de desplazamiento de la cuadrícula en la ventana
constexpr float GRID_OFFSET_X = 300.0f;
constexpr float GRID_OFFSET_Y = 10.0f;
constexpr float CELL_SIZE = 80.0f;

SudokuGame::SudokuGame() : window(sf::VideoMode(1366, 768), "Sudoku Game"), sudokuGrid(font, 250.0f) {
    if (!font.loadFromFile("resources/fonts/SpaceComics.ttf")) {
        throw std::runtime_error("No se pudo cargar la fuente.");
    }
    sudokuGrid.generatePuzzle();
}

void SudokuGame::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

void SudokuGame::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            handleKeyPress(event.key.code);
        }
    }
}

void SudokuGame::handleMouseClick(int x, int y) {
    // Ajustar las coordenadas para que coincidan con el desplazamiento de la cuadrícula
    int localX = x - GRID_OFFSET_X;
    int localY = y - GRID_OFFSET_Y;

    // Convertir coordenadas de pantalla a índices de celda, con el desplazamiento ajustado
    selectedRow = localY / CELL_SIZE;
    selectedCol = localX / CELL_SIZE;

    if (selectedRow < 0 || selectedRow >= 9 || selectedCol < 0 || selectedCol >= 9) {
        selectedRow = -1;
        selectedCol = -1;
    }
}

void SudokuGame::handleKeyPress(sf::Keyboard::Key key) {
    if (selectedRow == -1 || selectedCol == -1) {
        return;
    }

    int value = -1;
    if (key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num9) {
        value = key - sf::Keyboard::Num0;
    }
    else if (key >= sf::Keyboard::Numpad1 && key <= sf::Keyboard::Numpad9) {
        value = key - sf::Keyboard::Numpad0;
    }

    if (value != -1 && sudokuGrid.isCellEditable(selectedRow, selectedCol)) {
        sudokuGrid.setValue(selectedRow, selectedCol, value);
    }
}

void SudokuGame::render() {
    window.clear(sf::Color::White);

    // Dibujar la cuadrícula en la posición deseada
    sudokuGrid.draw(window, GRID_OFFSET_X, GRID_OFFSET_Y);

    // Dibujar el borde de la celda seleccionada si hay una selección válida
    if (selectedRow != -1 && selectedCol != -1) {
        sf::RectangleShape selection(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        selection.setPosition(GRID_OFFSET_X + selectedCol * CELL_SIZE, GRID_OFFSET_Y + selectedRow * CELL_SIZE);
        selection.setFillColor(sf::Color::Transparent);
        selection.setOutlineColor(sf::Color::Blue);
        selection.setOutlineThickness(2);
        window.draw(selection);
    }

    window.display();
}
