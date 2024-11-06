#include <SFML/Graphics.hpp>
#include "StartScreen.h"
#include "SudokuGame.h"
#include "LoadScreen.h"

enum class ScreenState {
    StartScreen,
    SudokuGame,
    LoadScreen
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Sudoku Game");
    sf::Font font;
    if (!font.loadFromFile("resources/fonts/SpaceComics.ttf")) {
        return -1;
    }

    sf::Image icon;
    if (!icon.loadFromFile("resources/icons/icon.png")) {
        return -1;
    }


    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    ScreenState currentState = ScreenState::StartScreen;

    StartScreen* startScreen = new StartScreen(window, font);
    SudokuGame* sudokuGame = new SudokuGame(window, font);
    LoadScreen* loadScreen = new LoadScreen(window, font);

    while (window.isOpen()) {
        switch (currentState) {
            case ScreenState::StartScreen:
                startScreen->draw();

                if (startScreen->shouldStartGame()) {
                    sudokuGame = new SudokuGame(window, font);
                    currentState = ScreenState::SudokuGame;
                }
                else if (startScreen->shouldLoadGame()) {
                    loadScreen = new LoadScreen(window, font);
                    currentState = ScreenState::LoadScreen;
                }
                else if (startScreen->shouldExit()) {
                    window.close();
                }
                break;

            case ScreenState::SudokuGame:
                sudokuGame->run();

                if (sudokuGame->shouldGoBack()) {
                    currentState = ScreenState::StartScreen;
                }
                break;

            case ScreenState::LoadScreen:
                loadScreen->draw();

				if (loadScreen->shouldStartGame()) {
                    
					string name = loadScreen->getLoadedGameState().name;
                    vector<vector<int>> initialGrid = loadScreen->getLoadedGameState().initialGrid;
					vector<vector<int>> grid = loadScreen->getLoadedGameState().currentGrid;
					vector<vector<int>> solution = loadScreen->getLoadedGameState().solutionGrid;
					float time = loadScreen->getLoadedGameState().elapsedTime;

					sudokuGame = new SudokuGame(window, font, initialGrid, grid, solution, name, time);
					currentState = ScreenState::SudokuGame;
				}
				else

                if (loadScreen->shouldGoBack()) {
                    currentState = ScreenState::StartScreen;
                }
                break;
        }
    }
    return 0;
}
