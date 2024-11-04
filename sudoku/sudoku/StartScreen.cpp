#include <SFML/Graphics.hpp>
#include "StartScreen.h"

StartScreen::StartScreen(sf::Font& font) {
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

void StartScreen::draw(sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (playButton.getGlobalBounds().contains(mousePos)) {
        playButton.setFillColor(sf::Color(6, 140, 210));
    }
    else {
        playButton.setFillColor(sf::Color(1, 93, 157));
    }

    if (loadButton.getGlobalBounds().contains(mousePos)) {
        loadButton.setFillColor(sf::Color(6, 140, 210));
    }
    else {
        loadButton.setFillColor(sf::Color(1, 93, 157));
    }

    if (exitButton.getGlobalBounds().contains(mousePos)) {
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
}

bool StartScreen::isPlayButtonClicked(const sf::Vector2f& mousePos) const {
    return playButton.getGlobalBounds().contains(mousePos);
}

bool StartScreen::isLoadButtonClicked(const sf::Vector2f& mousePos) const {
    return loadButton.getGlobalBounds().contains(mousePos);
}

bool StartScreen::isExitButtonClicked(const sf::Vector2f& mousePos) const {
    return exitButton.getGlobalBounds().contains(mousePos);
}
