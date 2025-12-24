#pragma once
#include <vector>
#include <map>
#include "movement.cpp"
#include "colour.cpp"
#include "position.h"

using namespace std;

class Board {
public:
    Board() {};
    Board(int rows, int cols);
    
    void initialize();
    void display();
    void insert(Position position, Colour colour);
    void move(Movement direction);
    void deleteMatch(Colour colour, Position startingPos);
    void checkMatches();

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
    
    bool isValid(Position position);
    bool gameWon();
    bool positionVisited(Position position, vector<Position> positions);

};
