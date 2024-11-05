#pragma once
#include <vector>
#include <string>



struct GameState {
    std::vector<std::vector<int>> currentGrid;
    std::vector<std::vector<int>> solutionGrid;
    float elapsedTime;
    std::string name;

    GameState(std::vector<std::vector<int>> current, std::vector<std::vector<int>> solution, float time, const std::string& name);
};
