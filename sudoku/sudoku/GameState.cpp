#include "GameState.h"

    GameState::GameState(vector<vector<int>> current, vector<vector<int>> initialGrid, vector<vector<int>> solution, float time, const string& name)
        : currentGrid(move(current)), initialGrid(move(initialGrid)), solutionGrid(move(solution)), elapsedTime(time), name(name) {
        if (currentGrid.size() != 9 || currentGrid[0].size() != 9) {
            currentGrid.resize(9, vector<int>(9, 0));
        }
        if (initialGrid.size() != 9 || initialGrid[0].size() != 9) {
            initialGrid.resize(9, vector<int>(9, 0));
        }
        if (solutionGrid.size() != 9 || solutionGrid[0].size() != 9) {
            solutionGrid.resize(9, vector<int>(9, 0));
        }
    }

    GameState::GameState() : currentGrid(9, vector<int>(9, 0)), initialGrid(9, vector<int>(9, 0)), solutionGrid(9, vector<int>(9, 0)), elapsedTime(0), name("") {}