#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colour.h"
#include "movement.h"

using namespace std;

class Board
{
public:
    Board() {};
    Board(int rows, int cols);

    void initialize();
    void display();
    void insert(Position position, Colour colour);
    void move(Movement direction);
    bool gameWon();

private:
    int rows;
    int cols;
    int grid[4][4];
    int size;

    map<Colour, int> coloursInGrid;

    void left();
    void right();
    void up();
    void down();
    void match(Colour colour, int count);
    void deleteMatch(Colour colour, Position startingPos);
    void checkMatches();

    bool isValid(Position position);
    bool positionVisited(Position position, vector<Position> positions);
};
