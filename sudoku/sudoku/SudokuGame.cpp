#include "SudokuGame.h"
#include <sstream>
#include "StartScreen.h"

constexpr float GRID_OFFSET_X = 570.0f;
constexpr float GRID_OFFSET_Y = 10.0f;
constexpr float CELL_SIZE = 80.0f;

SudokuGame::SudokuGame() : window(sf::VideoMode(1366, 768), "Sudoku Game"), sudokuGrid(font, 250.0f) {
    if (!font.loadFromFile("resources/fonts/SpaceComics.ttf")) {
        throw std::runtime_error("No se pudo cargar la fuente.");
    }
    sudokuGrid.generatePuzzle();

    backButton.setSize(sf::Vector2f(240, 50));
    backButton.setFillColor(sf::Color(1, 93, 157));
    backButton.setOutlineThickness(6);
    backButton.setOutlineColor(sf::Color::Black);
    backButton.setPosition(165, 30);

    backText.setFont(font);
    backText.setString("VOLVER");
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(backButton.getPosition().x + 35, backButton.getPosition().y + 15);

    saveButton.setSize(sf::Vector2f(240, 50));
    saveButton.setFillColor(sf::Color(1, 93, 157));
    saveButton.setOutlineThickness(6);
    saveButton.setOutlineColor(sf::Color::Black);
    saveButton.setPosition(165, 688);

    saveText.setFont(font);
    saveText.setString("GUARDAR");
    saveText.setCharacterSize(24);
    saveText.setFillColor(sf::Color::White);
    saveText.setPosition(saveButton.getPosition().x + 20, saveButton.getPosition().y + 15);

    nameLabel.setFont(font);
    nameLabel.setString("NOMBRE");
    nameLabel.setCharacterSize(16);
    nameLabel.setFillColor(sf::Color::Black);
    nameLabel.setPosition(35, 595);

    nameInputBox.setSize(sf::Vector2f(510, 40));
    nameInputBox.setFillColor(sf::Color(255, 255, 255));
    nameInputBox.setOutlineThickness(2);
    nameInputBox.setOutlineColor(sf::Color::Black);
    nameInputBox.setPosition(30, 618);

    gameClock.restart();
}

void SudokuGame::run() {
    while (window.isOpen()) {
        elapsedTime = gameClock.getElapsedTime().asSeconds();
        processEvents();
        render();
    }
}

void SudokuGame::processEvents() {
    sf::Event event;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        isHoveringBackButton = backButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
        isHoveringSaveButton = saveButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
        isHoveringNameInputBox = nameInputBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y);

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        if (event.type == sf::Event::TextEntered) {
            handleTextInput(event);
        }

        if (event.type == sf::Event::KeyPressed) {
            handleKeyPress(event.key.code);
        }
    }
}

void SudokuGame::handleTextInput(sf::Event& event) {
    if (isNameInputSelected) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == '\b') {
                if (!nameInput.isEmpty()) {
                    nameInput.erase(nameInput.getSize() - 1, 1);
                }
            }
            else if (nameInput.getSize() < 21) {
                char upperChar = static_cast<char>(std::toupper(event.text.unicode));
                nameInput += upperChar;
            }
        }
    }
}

void SudokuGame::handleMouseClick(int x, int y) {
    if (nameInputBox.getGlobalBounds().contains(x, y)) {
        isNameInputSelected = true;
    }
    else {
        isNameInputSelected = false;
    }

    int localX = x - GRID_OFFSET_X;
    int localY = y - GRID_OFFSET_Y;

    selectedRow = localY / CELL_SIZE;
    selectedCol = localX / CELL_SIZE;

    if (selectedRow < 0 || selectedRow >= 9 || selectedCol < 0 || selectedCol >= 9) {
        selectedRow = -1;
        selectedCol = -1;
    }

    if (backButton.getGlobalBounds().contains(x, y)) {
        StartScreen startScreen(font);
        startScreen.draw(window);
        window.close();
    }
    else if (saveButton.getGlobalBounds().contains(x, y)) {
        saveGame();
    }
}

void SudokuGame::handleKeyPress(sf::Keyboard::Key key) {
    if (selectedRow == -1 || selectedCol == -1) {
        return;
    }

    int value = -1;
    if (key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num9) {
        value = key - sf::Keyboard::Num0;
    }
    else if (key >= sf::Keyboard::Numpad1 && key <= sf::Keyboard::Numpad9) {
        value = key - sf::Keyboard::Numpad0;
    }

    if (value != -1 && sudokuGrid.isCellEditable(selectedRow, selectedCol)) {
        sudokuGrid.setValue(selectedRow, selectedCol, value);
    }
}

void SudokuGame::render() {
    window.clear(sf::Color::White);

    sudokuGrid.draw(window, GRID_OFFSET_X, GRID_OFFSET_Y);

    if (selectedRow != -1 && selectedCol != -1) {
        sf::RectangleShape selection(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        selection.setPosition(GRID_OFFSET_X + selectedCol * CELL_SIZE, GRID_OFFSET_Y + selectedRow * CELL_SIZE);
        selection.setFillColor(sf::Color::Transparent);
        selection.setOutlineColor(sf::Color::Blue);
        selection.setOutlineThickness(2);
        window.draw(selection);
    }

    if (isHoveringBackButton) {
        backButton.setFillColor(sf::Color(6, 140, 210));
    }
    else {
        backButton.setFillColor(sf::Color(1, 93, 157));
    }
    window.draw(backButton);
    window.draw(backText);

    if (isHoveringSaveButton) {
        saveButton.setFillColor(sf::Color(6, 140, 210));
    }
    else {
        saveButton.setFillColor(sf::Color(1, 93, 157));
    }
    window.draw(saveButton);
    window.draw(saveText);

    window.draw(nameLabel);

    if (isHoveringNameInputBox || isNameInputSelected) {
        nameInputBox.setOutlineColor(sf::Color(0, 75, 130));
        nameInputBox.setFillColor(sf::Color(230, 230, 230));
    }
    else {
        nameInputBox.setOutlineColor(sf::Color::Black);
        nameInputBox.setFillColor(sf::Color(255, 255, 255));
    }
    window.draw(nameInputBox);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setString(nameInput);
    inputText.setCharacterSize(20);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(nameInputBox.getPosition().x + 5, nameInputBox.getPosition().y + 10);
    window.draw(inputText);

    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(160, 120);

    int minutes = static_cast<int>(elapsedTime) / 60;
    int seconds = static_cast<int>(elapsedTime) % 60;
    std::stringstream timeStream;
    timeStream << "TIEMPO= " << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
    timerText.setString(timeStream.str());

    window.draw(timerText);

    if (!errorMessage.empty()) {
        sf::Text errorText;
        errorText.setFont(font);
        errorText.setString(errorMessage);
        errorText.setCharacterSize(12);
        errorText.setFillColor(sf::Color::Red);
        errorText.setPosition(148, 665);
        window.draw(errorText);
    }

    window.display();
}



void SudokuGame::saveGame() {
    if (nameInput.getSize() == 0) {
        errorMessage = "SE NECESITA UN NOMBRE";
    }
    else {
     
        errorMessage.clear();
        std::cout << "Juego guardado con nombre: " << nameInput.toAnsiString() << std::endl;
    }
}
