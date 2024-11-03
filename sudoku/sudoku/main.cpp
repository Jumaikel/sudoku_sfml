#include <iostream>
#include "SudokuGame.h"

using namespace std;

int main() {
    try {
        SudokuGame game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
