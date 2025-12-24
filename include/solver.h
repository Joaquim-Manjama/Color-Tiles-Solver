#pragma once
#include "board.h"

class Solver
{
public:
    Solver();
    Solver(Board board, int maxMoves);

    int[] solve();

private:
    Board board;
    int maxMoves;
};