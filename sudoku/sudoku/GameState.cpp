#include "GameState.h"

    GameState::GameState(std::vector<std::vector<int>> current, std::vector<std::vector<int>> solution, float time, const std::string& name)
        : currentGrid(std::move(current)), solutionGrid(std::move(solution)), elapsedTime(time), name(name) {
        if (currentGrid.size() != 9 || currentGrid[0].size() != 9) {
            currentGrid.resize(9, std::vector<int>(9, 0));
        }
        if (solutionGrid.size() != 9 || solutionGrid[0].size() != 9) {
            solutionGrid.resize(9, std::vector<int>(9, 0));
        }
    }

    GameState::GameState() : currentGrid(9, std::vector<int>(9, 0)), solutionGrid(9, std::vector<int>(9, 0)), elapsedTime(0), name("") {}