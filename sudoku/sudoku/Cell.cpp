#include "Cell.h"

Cell::Cell() : value(0), isEditable(false) {
	shape.setSize(sf::Vector2f(80.0f, 80.0f));
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(1.0f);

	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setString("");
}

Cell::Cell(int value, bool isEditable, sf::Font& font)
    : value(value), isEditable(isEditable) {

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

void  Cell::setEditable(bool editable) {
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

