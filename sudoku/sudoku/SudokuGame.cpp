#include "SudokuGame.h"
#include <sstream>
#include "StartScreen.h"

constexpr float GRID_OFFSET_X = 600.0f;
constexpr float GRID_OFFSET_Y = 25.0f;
constexpr float CELL_SIZE = 80.0f;
static const int SIZE = 9;

SudokuGame::SudokuGame() : window(sf::VideoMode(1366, 768), "Sudoku Game") {
    if (!font.loadFromFile("resources/fonts/SpaceComics.ttf")) {
        throw std::runtime_error("No se pudo cargar la fuente.");
    }

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

    generateSudoku();

    sudokuGrid = new SudokuGrid(initialGrid, solutionGrid, font);
    gameClock.restart();
}

void SudokuGame::run() {
    while (window.isOpen()) {
        elapsedTime = gameClock.getElapsedTime().asSeconds();
        processEvents();
        render();
        if (showWinScreen) {
            if (clock.getElapsedTime().asSeconds() >= 1) {
                showWindowWin();
                showWinScreen = false; 
            }
        }
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

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
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

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
            lastPressedNumber = event.key.code - sf::Keyboard::Num1 + 1;
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

    selectedRow = localX / CELL_SIZE;
    selectedCol = localY / CELL_SIZE;

    if (selectedRow < 0 || selectedRow >= 9 || selectedCol < 0 || selectedCol >= 9) {
        selectedRow = -1;
        selectedCol = -1;
    }
	sudokuGrid->handleCellSelection(selectedRow, selectedCol);

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

    if (value != -1) {
        sudokuGrid->setCellValue(selectedRow, selectedCol, value);
        if (sudokuGrid->isCompleted()) {
            showWinScreen = true;
            clock.restart();
        }
    }
}


void SudokuGame::render() {
    window.clear(sf::Color::White);
    sudokuGrid->draw(window);
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

void SudokuGame::showWindowWin() {
    sf::RenderWindow winWindow(sf::VideoMode(1166, 568), "¡Felicidades!", sf::Style::None);
    winWindow.setPosition({ window.getPosition().x + 100, window.getPosition().y + 100 });
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    if (!backgroundTexture.loadFromFile("resources/imgs/winbackground.png")) {
        throw std::runtime_error("No se pudo cargar la imagen de fondo.");
    }

    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        1166.0f / backgroundTexture.getSize().x,
        568.0f / backgroundTexture.getSize().y
    );

    sf::Text winMessage;
    winMessage.setFont(font);
    winMessage.setCharacterSize(24);
    winMessage.setFillColor(sf::Color::Black);
    winMessage.setPosition(190, 225);

    int minutes = static_cast<int>(elapsedTime) / 60;
    int seconds = static_cast<int>(elapsedTime) % 60;
    std::stringstream timeStream;
    timeStream << "¡COMPLETASTE EL JUEGO EN " << minutes << ":" << seconds << " MIN!";
    winMessage.setString(timeStream.str());

    acceptButton.setSize(sf::Vector2f(200, 50));
    acceptButton.setFillColor(sf::Color(1, 93, 157));
    acceptButton.setOutlineThickness(3);
    acceptButton.setOutlineColor(sf::Color::Black);
    acceptButton.setPosition(483, 259);

    acceptText.setFont(font);
    acceptText.setString("ACEPTAR");
    acceptText.setCharacterSize(20);
    acceptText.setFillColor(sf::Color::White);
    acceptText.setPosition(acceptButton.getPosition().x + 20, acceptButton.getPosition().y + 15);

    bool isHoveringAcceptButton = false;

    while (winWindow.isOpen()) {
        sf::Event event;
        while (winWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                StartScreen startScreen(font);
                startScreen.draw(window);
                winWindow.close();
                return;
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(winWindow);
                isHoveringAcceptButton = acceptButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(winWindow);
                if (acceptButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    winWindow.close();
                    window.close();
                    StartScreen startScreen(font);
                    startScreen.draw(window);
                    return;
                }
            }
        }

        if (isHoveringAcceptButton) {
            acceptButton.setFillColor(sf::Color(6, 140, 210));
        }
        else {
            acceptButton.setFillColor(sf::Color(1, 93, 157));
        }

        winWindow.clear();
        winWindow.draw(backgroundSprite);
        winWindow.draw(winMessage);
        winWindow.draw(acceptButton);
        winWindow.draw(acceptText);
        winWindow.display();
    }
}

bool SudokuGame::isSafe(int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        if (solutionGrid[row][x] == num || solutionGrid[x][col] == num ||
            solutionGrid[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
            return false;
        }
    }
    return true;
}

bool SudokuGame::solveSudoku() {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (solutionGrid[row][col] == 0) { // Encuentra una celda vacía
                for (int num = 1; num <= SIZE; num++) {
                    if (isSafe(row, col, num)) {
                        solutionGrid[row][col] = num; // Coloca el número
                        if (solveSudoku()) {
                            return true; // Recursión
                        }
                        solutionGrid[row][col] = 0; // Deshacer
                    }
                }
                return false; // No se pudo colocar ningún número
            }
        }
    }
    return true; // Sudoku resuelto
}

// Genera un Sudoku válido y su solución
void SudokuGame::generateSudoku() {
    solutionGrid.assign(SIZE, std::vector<int>(SIZE, 0)); // Inicializa la solución
    solveSudoku(); // Resuelve el Sudoku para llenar la solución

    // Genera un puzzle a partir de la solución
    initialGrid = solutionGrid; // Copia la solución a initialGrid

    // Elimina algunos números para crear el puzzle
    int numToRemove = 40; // Puedes ajustar la dificultad
    while (numToRemove > 0) {
        int i = rand() % SIZE;
        int j = rand() % SIZE;
        if (initialGrid[i][j] != 0) {
            initialGrid[i][j] = 0; // Elimina el número
            numToRemove--;
        }
    }
}
