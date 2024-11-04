#include <SFML/Graphics.hpp>
#include "StartScreen.h"
#include "SudokuGame.h"

int main() {
    bool running = true;
    while (running) {
        sf::RenderWindow window(sf::VideoMode(1366, 768), "Sudoku - Pantalla de Inicio");

        sf::Font font;
        if (!font.loadFromFile("resources/fonts/SpaceComics.ttf")) {
            return -1;
        }

        StartScreen startScreen(font);
        bool gameStarted = false;
        bool loadGame = false;

        while (window.isOpen() && !gameStarted && !loadGame) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    running = false;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (startScreen.isPlayButtonClicked(mousePos)) {
                        gameStarted = true;
                    }
                    else if (startScreen.isLoadButtonClicked(mousePos)) {
                        loadGame = true;
                    }
                    else if (startScreen.isExitButtonClicked(mousePos)) {
                        window.close();
                        running = false;
                    }
                }
            }

            window.clear();
            if (!gameStarted && !loadGame) {
                startScreen.draw(window);
            }
            window.display();
        }

        if (gameStarted) {
            try {
                SudokuGame game;
                game.run();
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return -1;
            }
        }

        if (loadGame) {

        }
    }

    return 0;
}

