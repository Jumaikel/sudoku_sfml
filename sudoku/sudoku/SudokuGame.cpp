#include "SudokuGame.h"
#include "GameState.h"
#include <ctime> 
#include <iomanip>
#include <sstream>

constexpr float GRID_OFFSET_X = 600.0f;
constexpr float GRID_OFFSET_Y = 25.0f;
constexpr float CELL_SIZE = 80.0f;
static const int SIZE = 9;

SudokuGame::SudokuGame(sf::RenderWindow& window, sf::Font& pfont) : window(window), font(pfont) {
    initialize();
    generateSudoku();
    sudokuGrid = new SudokuGrid(initialGrid, solutionGrid, font);
	elapsedTime = 0.0f;
	gameClock.restart();
	clock.restart();
}

SudokuGame::SudokuGame(sf::RenderWindow& window, sf::Font& pfont, vector<vector<int>> grid, vector<vector<int>> solGrid, string name, float elapsedTime) : window(window), font(pfont) {
    initialize();
	this->nameInput = name;
	this->initialGrid = grid;
	this->solutionGrid = solGrid;
	this->elapsedTime = elapsedTime;
    sudokuGrid = new SudokuGrid(initialGrid, solutionGrid, font);
    gameClock.restart();
    clock.restart();
}

void SudokuGame::initialize() {
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

    solutionButton.setSize(sf::Vector2f(240, 20));
    solutionButton.setFillColor(sf::Color(1, 93, 157));
    solutionButton.setOutlineThickness(6);
    solutionButton.setOutlineColor(sf::Color::Black);
    solutionButton.setPosition(165, 540);

    solutionButtonText.setFont(font);
    solutionButtonText.setString("MOSTRAR SOLUCIÓN");
    solutionButtonText.setCharacterSize(10);
    solutionButtonText.setFillColor(sf::Color::White);
    solutionButtonText.setPosition(solutionButton.getPosition().x + 30, solutionButton.getPosition().y + 7);


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

    solutionText.setFont(font);
    solutionText.setCharacterSize(10);
    solutionText.setFillColor(sf::Color::Black);
    solutionText.setPosition(160, 150);

    messageText.setFont(font);
    messageText.setCharacterSize(12);
    messageText.setFillColor(sf::Color::Red);
    messageText.setPosition(148, 665);
    
}

void SudokuGame::drawSolutionGrid() {
    const int cellSize = 40;
    const int offsetX = 105;
    const int offsetY = 165;

    sf::RectangleShape gridFrame(sf::Vector2f(cellSize * SIZE, cellSize * SIZE));
    gridFrame.setPosition(offsetX, offsetY);
    gridFrame.setFillColor(sf::Color::Transparent);
    gridFrame.setOutlineThickness(3);
    gridFrame.setOutlineColor(sf::Color(1, 93, 157));
    window.draw(gridFrame);

    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(offsetX + col * cellSize, offsetY + row * cellSize);
            cell.setFillColor(sf::Color::White);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);
            window.draw(cell);

            if (showSolution) {
                if (solutionGrid[row][col] != 0) {
                    sf::Text numberText;
                    numberText.setFont(font);
                    numberText.setString(std::to_string(solutionGrid[row][col]));
                    numberText.setCharacterSize(24);
                    numberText.setFillColor(sf::Color::Black);
                    numberText.setPosition(
                        offsetX + col * cellSize + cellSize / 4 - 3,
                        offsetY + row * cellSize + cellSize / 8 + 3
                    );
                    window.draw(numberText);
                }
            }
        }
    }

    for (int row = 0; row < SIZE; row += 3) {
        for (int col = 0; col < SIZE; col += 3) {
            sf::RectangleShape subGridFrame(sf::Vector2f(cellSize * 3, cellSize * 3));
            subGridFrame.setPosition(offsetX + col * cellSize, offsetY + row * cellSize);
            subGridFrame.setFillColor(sf::Color::Transparent);
            subGridFrame.setOutlineThickness(2);
            subGridFrame.setOutlineColor(sf::Color(1, 93, 157));
            window.draw(subGridFrame);
        }
    }
}




void SudokuGame::run() {
    window.clear(sf::Color::White);
    if (goBack) {
        goBack = false;
    }
        if (gameClock.getElapsedTime().asSeconds() >= 1) {
        elapsedTime++;
        gameClock.restart();  }

        processEvents();
        render();
        if (showWinScreen) {
            if (clock.getElapsedTime().asSeconds() >= 0.5) {
                showWindowWin();
                showWinScreen = false; 
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
        isHoveringShowSolutionButton = solutionButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y);

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

    if (solutionButton.getGlobalBounds().contains(x, y)) {
        showSolution = !showSolution;
        solutionButtonText.setString(showSolution ? "OCULTAR SOLUCIÓN" : "MOSTRAR SOLUCIÓN");
    }

    if (backButton.getGlobalBounds().contains(x, y)) {
        goBack = true;
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
    sudokuGrid->draw(window);

    drawThickLines(window);


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

	if (isHoveringShowSolutionButton) {
		solutionButton.setFillColor(sf::Color(6, 140, 210));
	}
	else {
		solutionButton.setFillColor(sf::Color(1, 93, 157));
	}   

	window.draw(solutionButton);
	window.draw(solutionButtonText);

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
    drawSolutionGrid();
    window.draw(solutionButton);
    window.draw(solutionButtonText);


    messageText.setString(message);
    window.draw(messageText);

    window.display();
}

void SudokuGame::drawThickLines(sf::RenderWindow& window) {
    const float LINE_THICKNESS = 5.0f;

    for (int i = 1; i <= 2; ++i) {
        float x = GRID_OFFSET_X + i * 3 * CELL_SIZE;

        sf::RectangleShape verticalLine(sf::Vector2f(LINE_THICKNESS, SIZE * CELL_SIZE));
        verticalLine.setPosition(x, GRID_OFFSET_Y);
        verticalLine.setFillColor(sf::Color(1, 93, 157));

        window.draw(verticalLine);
    }

    for (int i = 1; i <= 2; ++i) {
        float y = GRID_OFFSET_Y + i * 3 * CELL_SIZE;

        sf::RectangleShape horizontalLine(sf::Vector2f(SIZE * CELL_SIZE, LINE_THICKNESS));
        horizontalLine.setPosition(GRID_OFFSET_X, y);
        horizontalLine.setFillColor(sf::Color(1, 93, 157));

        window.draw(horizontalLine);
    }

    sf::RectangleShape frame(sf::Vector2f(SIZE * CELL_SIZE, SIZE * CELL_SIZE));
    frame.setPosition(GRID_OFFSET_X - LINE_THICKNESS / 2 + 3, GRID_OFFSET_Y - LINE_THICKNESS / 2 + 3);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(LINE_THICKNESS);
    frame.setOutlineColor(sf::Color(1, 93, 157));

    window.draw(frame);
}


void SudokuGame::saveGame() {
    if (nameInput.getSize() == 0) {
        messageText.setPosition(148, 665);
        message = "SE NECESITA UN NOMBRE";
        return;
    }

    GameState gameState(sudokuGrid->getCurrentGrid(), solutionGrid, elapsedTime, nameInput);

    std::ostringstream fileNameStream;
    fileNameStream << nameInput.toAnsiString() << ".txt";
    std::ofstream outFile("games/" + fileNameStream.str());

    if (!outFile.is_open()) {
        messageText.setPosition(30, 665);
        message = "NO SE PUDO ABRIR EL ARCHIVO PARA GUARDAR";
        return;
    }

    for (const auto& row : gameState.currentGrid) {
        for (int value : row) {
            outFile << value << " ";
        }
    }
    outFile << "\n";

    for (const auto& row : gameState.solutionGrid) {
        for (int value : row) {
            outFile << value << " ";
        }
    }
    outFile << "\n";

    outFile << gameState.elapsedTime << "\n";
    outFile << gameState.name << "\n";

    outFile.close();
    messageText.setPosition(187, 665);
    message = "JUEGO GUARDADO";
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
				goBack = true;
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
                    goBack = true;
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
            if (solutionGrid[row][col] == 0) {
                for (int num = 1; num <= SIZE; num++) {
                    if (isSafe(row, col, num)) {
                        solutionGrid[row][col] = num;
                        if (solveSudoku()) {
                            return true;
                        }
                        solutionGrid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool SudokuGame::shouldGoBack() const {
    return goBack;
}

void SudokuGame::generateSudoku() {
    solutionGrid.assign(SIZE, std::vector<int>(SIZE, 0));
    solveSudoku();

    initialGrid = solutionGrid;

    int numToRemove = 40;
    while (numToRemove > 0) {
        int i = rand() % SIZE;
        int j = rand() % SIZE;
        if (initialGrid[i][j] != 0) {
            initialGrid[i][j] = 0;
            numToRemove--;
        }
    }
}

std::vector<std::vector<int>> SudokuGrid::getCurrentGrid() const {
    std::vector<std::vector<int>> currentGrid(9, std::vector<int>(9, 0));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            currentGrid[i][j] = cells[i][j].getValue();
        }
    }

    return currentGrid;
}
