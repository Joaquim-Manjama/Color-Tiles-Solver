#pragma once
#include <vector>
#include <map>
#include <string>
#include "position.h"
#include "colour.h"
#include "movement.h"

using namespace std;

class Board
{
public:
    Board() {};
    Board(int rows, int cols);

    void display();
    void insert(Position position, Colour colour);
    void move(Movement direction);
    
    bool gameWon();

    Board copy();
    std::string serialize() const;
    
private:
    int rows;
    int cols;
    int grid[4][4];
    int size;

    map<Colour, int> coloursInGrid;

    void initialize();
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
