#pragma once
#include "board.h"

class Game
{
public:
    Game();
    void play();

private:
    Board board;
    void initialize();
    void levelOne();
};