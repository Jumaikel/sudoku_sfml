#include "GameState.h"

GameState::GameState(std::vector<std::vector<int>> current, std::vector<std::vector<int>> solution, float time, const std::string& name)
    : currentGrid(current), solutionGrid(solution), elapsedTime(time), name(name) {}