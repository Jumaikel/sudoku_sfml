#include "LoadScreen.h"
#include <iostream>
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

void LoadScreen::loadSavedGames() {
    //savedGames.clear();
    std::ifstream dir("games/");
    std::string fileName;

    while (std::getline(dir, fileName)) {
        if (fileName.find(".txt") != std::string::npos) {
            savedGames.push_back(fileName);
            std::cout << fileName << "/n";
        }
    }
}

void LoadScreen::drawSavedGames() {
    for (size_t i = 0; i < savedGames.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(savedGames[i]);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(50, 50 + i * 30);

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
}

void LoadScreen::draw() {
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

bool LoadScreen::shouldGoBack() const
{
    return goBack;
}
