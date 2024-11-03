#include "Cell.h"

Cell::Cell() : value(0), isEditable(true) {
    
}

Cell::Cell(int value, bool isEditable, sf::Font& font)
    : value(value), isEditable(isEditable) {

    // Configuración del rectángulo de la celda
    shape.setSize(sf::Vector2f(80.0f, 80.0f)); // Tamaño de la celda (ajustable)
    shape.setFillColor(isEditable ? sf::Color::White : sf::Color(200, 200, 200)); // Color de fondo según si es editable o no
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);

    // Configuración del texto de la celda
    text.setFont(font);
    text.setCharacterSize(24);   // Tamaño de la fuente
    text.setFillColor(sf::Color::Black);
    if (value > 0) {             // Solo mostrar texto si el valor es mayor que 0
        text.setString(std::to_string(value));
    }
}

// Establece el valor de la celda si es editable
void Cell::setValue(int newValue) {
    if (isEditable) {
        value = newValue;
        text.setString(value > 0 ? std::to_string(value) : ""); // Actualiza el texto si es un número válido
    }
}

// Devuelve el valor de la celda
int Cell::getValue() const {
    return value;
}

// Indica si la celda es editable
bool Cell::getIsEditable() const {
    return isEditable;
}

// Establece la posición de la celda (para colocación en el tablero)
void Cell::setPosition(float x, float y) {
    shape.setPosition(x, y);
    text.setPosition(x + 15.0f, y + 10.0f); // Ajusta la posición del texto dentro de la celda
}

// Dibuja la celda en la ventana
void Cell::draw(sf::RenderWindow& window) {
    window.draw(shape);   // Dibuja el fondo de la celda
    if (value > 0) {      // Dibuja el texto solo si tiene un valor asignado
        window.draw(text);
    }
}
