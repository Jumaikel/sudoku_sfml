#include <SFML/Graphics.hpp>
#include "StartScreen.h"
#include "SudokuGame.h"
// Aquí incluimos las otras clases de juego que tienes como `SudokuGrid`, etc.

int main() {
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Sudoku - Pantalla de Inicio");

    // Cargar fuente
    sf::Font font;
    if (!font.loadFromFile("resources/fonts/SpaceComics.ttf")) {
        return -1;
    }

    StartScreen startScreen(font);
    bool gameStarted = false;
    bool loadGame = false;

    // Bucle para la pantalla de inicio
    while (window.isOpen() && !gameStarted && !loadGame) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Manejo de clics en los botones
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (startScreen.isPlayButtonClicked(mousePos)) {
                    gameStarted = true;
                }
                else if (startScreen.isLoadButtonClicked(mousePos)) {
                    loadGame = true;
                }
                else if (startScreen.isExitButtonClicked(mousePos)) {
                    window.close(); // Cierra la ventana si se hace clic en "Salir"
                }
            }
        }

        window.clear();
        if (!gameStarted && !loadGame) {
            // Dibuja la pantalla de inicio si el juego no ha comenzado
            startScreen.draw(window);
        }
        window.display();
    }

    // Iniciar el juego si se seleccionó "Jugar"
    if (gameStarted) {
        try {
            SudokuGame game;
            game.run(); // Iniciar el bucle del juego dentro de `SudokuGame`
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    }

    // Cargar el juego si se seleccionó "Cargar Juego"
    if (loadGame) {
        // Aquí deberías cargar el estado del juego guardado y mostrarlo
        // Cargar el tablero desde el archivo
    }

    return 0;
}
