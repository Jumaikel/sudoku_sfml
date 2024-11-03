#include "SudokuGame.h"

SudokuGame::SudokuGame() : window(sf::VideoMode(1366, 768), "Sudoku Game"), sudokuGrid(font, 250.0f) {
    if (!font.loadFromFile("resources/fonts/SpaceComics.ttf")) {
        throw std::runtime_error("No se pudo cargar la fuente.");
    }
    sudokuGrid.generatePuzzle();
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
        if (event.type == sf::Event::Closed)
            window.close();

        // Detectar clics de mouse
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        // Detectar teclas presionadas
        if (event.type == sf::Event::KeyPressed) {
            handleKeyPress(event.key.code);
        }
    }
}
// Maneja los clics del mouse para seleccionar una celda
void SudokuGame::handleMouseClick(int x, int y) {
    // Convertir coordenadas de pantalla a índices de celda
    float cellSize = 80.0f; // Tamaño de la celda en píxeles, ajusta según tu configuración
    selectedRow = y / cellSize;
    selectedCol = x / cellSize;

    // Verificar si la selección está dentro de los límites
    if (selectedRow < 0 || selectedRow >= 9 || selectedCol < 0 || selectedCol >= 9) {
        selectedRow = -1;
        selectedCol = -1;
    }
}

// Maneja la entrada de teclas numéricas para ingresar valores en las celdas
void SudokuGame::handleKeyPress(sf::Keyboard::Key key) {
    if (selectedRow == -1 || selectedCol == -1) {
        return; // No hay celda seleccionada
    }

    int value = -1;
    if (key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num9) {
        value = key - sf::Keyboard::Num0;
    }
    else if (key >= sf::Keyboard::Numpad1 && key <= sf::Keyboard::Numpad9) {
        value = key - sf::Keyboard::Numpad0;
    }

    // Solo actualiza si la celda es editable y el valor es válido
    if (value != -1 && sudokuGrid.isCellEditable(selectedRow, selectedCol)) {
        sudokuGrid.setValue(selectedRow, selectedCol, value);
    }
}



// Renderiza el juego en la ventana
void SudokuGame::render() {
    window.clear(sf::Color::White);

    sudokuGrid.draw(window);

    // Dibujar un borde alrededor de la celda seleccionada
    if (selectedRow != -1 && selectedCol != -1) {
        sf::RectangleShape selection(sf::Vector2f(80.0f, 80.0f)); // Tamaño de la celda
        selection.setPosition(selectedCol * 80.0f, selectedRow * 80.0f);
        selection.setFillColor(sf::Color::Transparent);
        selection.setOutlineColor(sf::Color::Blue);
        selection.setOutlineThickness(2);
        window.draw(selection);
    }

    window.display();
}
