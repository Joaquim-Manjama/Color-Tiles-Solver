#pragma once
#include <vector>
#include "movement.cpp"
#include "colour.cpp"
#include "position.h"

class Board {
public:
    Board(int rows, int cols);
    
    void initialize();
    void display();
    void insert(Position position, int value);
    void move(Movement direction);
    void deleteMatch(Colour colour);

    bool matched(Colour colour, int count);

private:
    int rows;
    int cols;
    int grid[4][4];
    int size;

    void left();
    void right();
    void up();
    void down();
    
    bool isValid(Position position);

};
