#include <SFML/Graphics.hpp>
#include "StartScreen.h"
#include "SudokuGame.h"
#include "LoadScreen.h"

StartScreen::StartScreen(sf::RenderWindow& window, sf::Font& pfont) : window(window), font(pfont) {

    if (!backgroundTexture.loadFromFile("resources/imgs/background.png")) {
        throw std::runtime_error("No se pudo cargar la imagen de fondo.");
    }

    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        1366.0f / backgroundTexture.getSize().x,
        768.0f / backgroundTexture.getSize().y
    );

    playButton.setSize(sf::Vector2f(185, 50));
    playButton.setFillColor(sf::Color(1, 93, 157));
    playButton.setOutlineThickness(6);
    playButton.setOutlineColor(sf::Color::Black);
    playButton.setPosition(590.5, 450);

    playText.setFont(font);
    playText.setString("JUGAR");
    playText.setCharacterSize(24);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(playButton.getPosition().x + 20, playButton.getPosition().y + 15);

    loadButton.setSize(sf::Vector2f(365, 50));
    loadButton.setFillColor(sf::Color(1, 93, 157));
    loadButton.setOutlineThickness(6);
    loadButton.setOutlineColor(sf::Color::Black);
    loadButton.setPosition(500.5, 540);

    loadText.setFont(font);
    loadText.setString("CARGAR JUEGO");
    loadText.setCharacterSize(24);
    loadText.setFillColor(sf::Color::White);
    loadText.setPosition(loadButton.getPosition().x + 20, loadButton.getPosition().y + 15);

    exitButton.setSize(sf::Vector2f(165, 50));
    exitButton.setFillColor(sf::Color(1, 93, 157));
    exitButton.setOutlineThickness(6);
    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setPosition(1171, 30);

    exitText.setFont(font);
    exitText.setString("SALIR");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(exitButton.getPosition().x + 20, exitButton.getPosition().y + 15);
}

void StartScreen::draw() {
    if (startGame || loadGame) {
		startGame = false;
		loadGame = false;
    }
	    window.clear();
        processEvents();
        if (isHoveringPlayButton) {
            playButton.setFillColor(sf::Color(6, 140, 210));
        }
        else {
            playButton.setFillColor(sf::Color(1, 93, 157));
        }

        if (isHoveringLoadButton) {
            loadButton.setFillColor(sf::Color(6, 140, 210));
        }
        else {
            loadButton.setFillColor(sf::Color(1, 93, 157));
        }

        if (isHoveringExitInputBox) {
            exitButton.setFillColor(sf::Color(6, 140, 210));
        }
        else {
            exitButton.setFillColor(sf::Color(1, 93, 157));
        }

        window.draw(backgroundSprite);
        window.draw(playButton);
        window.draw(playText);
        window.draw(loadButton);
        window.draw(loadText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
}

bool StartScreen::shouldStartGame() const {
    return startGame;
}

bool StartScreen::shouldLoadGame() const {
    return loadGame;
}

bool StartScreen::shouldExit() const {
    return exitGame;
}

void StartScreen::handleMouseClick(int x, int y) {
    if (playButton.getGlobalBounds().contains(x, y)) {
        startGame = true;
    }
    else if (loadButton.getGlobalBounds().contains(x, y)) {
        loadGame = true;
    }
    else if (exitButton.getGlobalBounds().contains(x, y)) {
        exitGame = true;
    }
}

void StartScreen::processEvents() {
    sf::Event event;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            exitGame = true;
        }

        isHoveringPlayButton = playButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
        isHoveringLoadButton = loadButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
        isHoveringExitInputBox = exitButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y);

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }
    }
}
