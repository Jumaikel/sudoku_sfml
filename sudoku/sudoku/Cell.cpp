
#include "Cell.h"

Cell::Cell() : value(0), isEditable(false), isSelected(false), font(*(new sf::Font)) {
    if (!font.loadFromFile("resources/fonts/SpaceComics.ttf")) {
        return;
    }
    shape.setSize(sf::Vector2f(80.0f, 80.0f));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setString("");
}

Cell::Cell(int value, bool isEditable, sf::Font& pfont)
    : value(value), isEditable(isEditable), isSelected(false), font(pfont) {

    shape.setSize(sf::Vector2f(80.0f, 80.0f));
    shape.setFillColor(isEditable ? sf::Color::White : sf::Color(200, 200, 200));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    if (value > 0) {
        text.setString(std::to_string(value));
    }
}

void Cell::setValue(int newValue) {
    if (isEditable) {
        value = newValue;
        text.setString(value > 0 ? std::to_string(value) : "");
    }
}

int Cell::getValue() const {
    return value;
}

bool Cell::getIsEditable() const {
    return isEditable;
}

void Cell::setEditable(bool editable) {
    isEditable = editable;
    shape.setFillColor(isEditable ? sf::Color::White : sf::Color(200, 200, 200));
}

void Cell::setPosition(float x, float y) {
    shape.setPosition(x, y);
    text.setPosition(x + 80.0f / 3, y + 80.0f / 3);
}

void Cell::draw(sf::RenderWindow& window) {
    window.draw(shape);
    if (value > 0) {
        window.draw(text);
    }
}

void Cell::select() {
    if (isEditable) {
        isSelected = true;
		shape.setFillColor(sf::Color(6, 140, 210));
    }
}

void Cell::deselect() {
    if (isEditable) {
        isSelected = false;
        shape.setFillColor(sf::Color::White);
    }
}

bool Cell::contains(sf::Vector2f point) const {
    return shape.getGlobalBounds().contains(point);
}

void Cell::handleInput(sf::Event event) {
    if (isEditable && isSelected && event.type == sf::Event::TextEntered) {
        if (isdigit(event.text.unicode)) {
            int num = event.text.unicode - '0';
            setValue(num);
        }
        else if (event.text.unicode == 8) {
            setValue(0);
        }
    }
}