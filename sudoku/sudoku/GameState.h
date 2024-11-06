#pragma once
#include <vector>
#include <string>

using namespace std;

struct GameState {
    vector<vector<int>> currentGrid;
    vector<vector<int>> initialGrid;
    vector<vector<int>> solutionGrid;
    float elapsedTime;
    string name;

    GameState(vector<vector<int>> current, vector<vector<int>> initialGrid, vector<vector<int>> solution, float time, const string& name);
	GameState();
};
