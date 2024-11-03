#include "SudokuGame.h"

SudokuGame::SudokuGame() : window(sf::VideoMode(1366, 768), "Sudoku Game"), sudokuGrid(font, 250.0f) {
    if (!font.loadFromFile("resources/fonts/SpaceComics.ttf")) {
        throw std::runtime_error("No se pudo cargar la fuente.");
    }
}

// Inicia el bucle principal del juego
void SudokuGame::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

// Procesa los eventos del usuario
void SudokuGame::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Detecta clics del mouse para seleccionar celdas
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }

        // Detecta la entrada de números
        if (event.type == sf::Event::KeyPressed) {
            handleKeyInput(event.key.code);
        }
    }
}

// Maneja los clics del mouse para seleccionar una celda
void SudokuGame::handleMouseClick(int mouseX, int mouseY) {
    int cellSize = 50;
    selectedRow = mouseY / cellSize;
    selectedCol = mouseX / cellSize;
}

// Maneja la entrada de teclas numéricas para ingresar valores en las celdas
void SudokuGame::handleKeyInput(sf::Keyboard::Key key) {
    if (selectedRow == -1 || selectedCol == -1) return;  // Si no hay celda seleccionada, no hace nada

    // Verifica si la tecla presionada es un número del 1 al 9
    if (key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num9) {
        int value = key - sf::Keyboard::Num0;
        if (sudokuGrid.isValidMove(selectedRow, selectedCol, value)) {
            sudokuGrid.setValue(selectedRow, selectedCol, value);
        }
    }
    // Si la tecla es 'Backspace', borra el valor
    else if (key == sf::Keyboard::BackSpace) {
        sudokuGrid.setValue(selectedRow, selectedCol, 0);
    }
}

// Renderiza el juego en la ventana
void SudokuGame::render() {
    window.clear(sf::Color::White);
    sudokuGrid.draw(window);  // Dibuja el tablero de Sudoku
    window.display();
}