#include "LoadScreen.h"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream> // Para leer archivos

LoadScreen::LoadScreen(sf::RenderWindow& window, sf::Font& pfont) : window(window), font(pfont) {
    backButton.setSize(sf::Vector2f(240, 50));
    backButton.setFillColor(sf::Color(1, 93, 157));
    backButton.setOutlineThickness(6);
    backButton.setOutlineColor(sf::Color::Black);
    backButton.setPosition(30, 30);

    backText.setFont(font);
    backText.setString("VOLVER");
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(backButton.getPosition().x + 35, backButton.getPosition().y + 15);

    loadSavedGames();
}

bool LoadScreen::shouldStartGame() const {
    return startGame;
}
void LoadScreen::loadSavedGames() {
    savedGames.clear();
    buttons.clear();

    std::string path = "games";
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            savedGames.push_back(entry.path().filename().string());
        }
    }

    for (size_t i = 0; i < savedGames.size(); ++i) {
        sf::RectangleShape button;
        button.setSize(sf::Vector2f(307, 20));
        button.setPosition(529.5f, 20 + i * 30);
        button.setFillColor(sf::Color(200, 200, 200));
        buttons.push_back(button);
    }
}

void LoadScreen::drawSavedGames() {
    for (size_t i = 0; i < savedGames.size(); ++i) {
        if (buttons[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
            buttons[i].setFillColor(sf::Color(6, 140, 210));
        }
        else {
            buttons[i].setFillColor(sf::Color(200, 200, 200));
        }

        std::string upperCaseName = savedGames[i];
        std::transform(upperCaseName.begin(), upperCaseName.end(), upperCaseName.begin(), ::toupper);

        sf::Text text;
        text.setFont(font);
        text.setString(upperCaseName);
        text.setCharacterSize(10);
        text.setFillColor(sf::Color::Black);
        text.setPosition(buttons[i].getPosition().x + 4, buttons[i].getPosition().y + 5);

        window.draw(buttons[i]);
        window.draw(text);
    }
}



void LoadScreen::processEvents() {
    sf::Event event;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        isHoveringBackButton = backButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y);

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }
    }
}

void LoadScreen::handleMouseClick(int x, int y) {
    if (backButton.getGlobalBounds().contains(x, y)) {
        goBack = true;
    }

    for (size_t i = 0; i < savedGames.size(); ++i) {
        if (buttons[i].getGlobalBounds().contains(x, y)) {
            readSavedGame(savedGames[i]);
            break;
        }
    }
}

void LoadScreen::readSavedGame(const std::string& gameName) {
    std::ifstream file("games/" + gameName);
    if (file.is_open()) {

        std::vector<int> currentGridValues(81); 
        std::vector<int> solutionGridValues(81); 

        for (int i = 0; i < 81; ++i) {
            file >> currentGridValues[i];
        }

        for (int i = 0; i < 81; ++i) {
            file >> solutionGridValues[i];
        }

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                loadedGameState.currentGrid[row][col] = currentGridValues[row * 9 + col];
                loadedGameState.solutionGrid[row][col] = solutionGridValues[row * 9 + col];
            }
        }

        file >> loadedGameState.elapsedTime;

        file >> loadedGameState.name;

        startGame = true;
        std::cout << "Juego cargado desde " << gameName << std::endl;
    }
    else {
        std::cerr << "No se pudo abrir el archivo: " << gameName << std::endl;
    }
}





GameState LoadScreen::getLoadedGameState() const {
	return loadedGameState;
}


void LoadScreen::draw() {
    if (startGame) {
		startGame = false;
    }
    window.clear(sf::Color::White);
    processEvents();
    if (isHoveringBackButton) {
        backButton.setFillColor(sf::Color(6, 140, 210));
    }
    else {
        backButton.setFillColor(sf::Color(1, 93, 157));
    }
    window.draw(backButton);
    window.draw(backText);

    drawSavedGames();
    window.display();
}

bool LoadScreen::shouldGoBack() const {
    return goBack;
}
