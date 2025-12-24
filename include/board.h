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
    void removePosition(Position position);
    void move(Movement direction);
    
    bool gameWon();

    // Returns a pointer to rows of the internal grid: caller should treat as `const int (*)[16]`
    const int (*getGrid() const)[8];

    Board copy();
    std::string serialize() const;
    
private:
    int rows;
    int cols;
    int grid[8][8];
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
