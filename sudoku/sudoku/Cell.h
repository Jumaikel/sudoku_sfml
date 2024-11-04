#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Cell {
private:
    int value;
    bool isEditable;
    sf::RectangleShape shape;
    sf::Text text;

public:
    Cell();
    Cell(int value, bool isEditable, sf::Font& font);
    void setValue(int newValue);
    int getValue() const;
    bool getIsEditable() const;
    void setEditable(bool editable);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
};
