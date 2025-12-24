#pragma once
#include "board.h"
#include "movement.h"
#include <vector>

using namespace std;

class Solver
{
public:
    Solver();
    Solver(Board board, int maxMoves);

    vector<Movement> solve();

private:
    Board board;
    int maxMoves;
};