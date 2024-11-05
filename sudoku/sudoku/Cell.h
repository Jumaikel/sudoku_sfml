#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Cell {
private:
    int value;
    bool isEditable;
    bool isSelected;
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font& font;

public:
    Cell();
    Cell(int value, bool isEditable, sf::Font& pfont);
    void setValue(int newValue);
    int getValue() const;
    bool getIsEditable() const;
    void setEditable(bool editable);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);

    void select();
    void deselect();
    bool contains(sf::Vector2f point) const;
    void handleInput(sf::Event event);
};