#include <iostream>
#include <queue>
#include "board.h"

using namespace std;

Board::Board(int rows, int cols) : rows(rows), cols(cols) {

    // Get maximum size of grid
    size = sizeof(grid) / sizeof(grid[0]);
}   

void Board::initialize() { 

    // Iterate though whole grid
    for (int i = 0; i < size; i++) {
        
        for (int j = 0; j < size; j++) {

            // Only zero relevant part of grid
            if (i < rows && j < cols) {
                grid[i][j] = 0;
            
            // Avoid junk values
            } else {
                grid[i][j] = -2;
            } 

        }
    }
}

void Board::display() {

    cout << "[" << endl;
    
    for (int i = 0; i < rows; i++) {

        cout << " [ ";

        for (int j = 0; j < cols; j++) {
            cout << grid[i][j];

            if (j < cols - 1) {
                cout << ", ";
            }
        }

        cout << " ]" << endl;
    }

    cout << "]" << endl;
}

void Board::insert(Position position, int value) {
    grid[position.row][position.column] = value;
}

void Board::move(Movement direction) {
    // [ LEFT, UP, RIGHT, DOWN]

    switch(direction) {
        
        case LEFT:
            cout << "Move Left" << endl;
            left();
            break;

        case UP:
            cout << "Move Up" << endl;
            up();
            break;

        case RIGHT:
            cout << "Move Right" << endl;
            right();
            break;

        case DOWN:
            cout << "Move Down" << endl;
            down();
            break;
        
        default:
            break;
    }

    display();
}   

void Board::left() {
     bool space;

    for (int i = 0; i < rows; i++) {

        space = false;

        for (int j = 0; j < cols; j++) {
            
            if (space) {
                grid[i][j - 1] = grid[i][j];
                grid[i][j] = 0;
            }
            
            if (grid[i][j] == 0) {
                space = true;
            }
        }
    }
}

void Board::right() {

    bool space;

    for (int i = 0; i < rows; i++) {

        space = false;

        for (int j = cols - 1; j >= 0; j--) {
            
            if (space) {
                grid[i][j + 1] = grid[i][j];
                grid[i][j] = 0;
            }
            
            if (grid[i][j] == 0) {
                space = true;
            }
        }
    }
}

void Board::up() {
    bool space;

    for (int i = 0; i < cols; i++) {
        space = false;

        for (int j = 0; j < rows; j++) {

            if (space) {
                grid[j - 1][i] = grid[j][i];
                grid[j][i] = 0;
            }

            if (grid[j][i] == 0) {
                space = true;
            }

        }
    }
}

void Board::down() {

    bool space;

    for (int i = 0; i < cols; i++) {
        space = false;

        for (int j = rows - 1; j >= 0; j--) {

            if (space) {
                grid[j + 1][i] = grid[j][i];
                grid[j][i] = 0;
            }

            if (grid[j][i] == 0) {
                space = true;
            }

        }
    }
}

void Board::deleteMatch(Colour colour) {
    int nodeRow;
    int nodeColumn;
    queue<Position> queue;

    bool found = false;
    // Find the first node of the given colour
    for (nodeRow = 0; nodeRow < rows; nodeRow++) {
        
        for (nodeColumn = 0; nodeColumn < cols; nodeColumn++) {
            if (grid[nodeRow][nodeColumn] == colour) {
                found = true;
                break;
            } 
        }

        if (found) {
            break;
        }
    }

    // Use bfs to delete
     Position position = Position(nodeRow, nodeColumn);
    queue.push(position);

    while (!queue.empty()) {
        Position currentPosition = queue.front();
        queue.pop();

        grid[currentPosition.row][currentPosition.column] = 0;

        // LEFT
        Position possiblePosition = Position(currentPosition.row, currentPosition.column - 1);
        if (isValid(possiblePosition)) {
            
            if (grid[possiblePosition.row][possiblePosition.column] == colour) {
                queue.push(possiblePosition);
            }
        }

        // UP
        possiblePosition = Position(currentPosition.row - 1, currentPosition.column);
        if (isValid(possiblePosition)) {
            
            if (grid[possiblePosition.row][possiblePosition.column] == colour) {
                queue.push(possiblePosition);
            }
        }

        // RIGHT
        possiblePosition = Position(currentPosition.row, currentPosition.column + 1);
        if (isValid(possiblePosition)) {
            
            if (grid[possiblePosition.row][possiblePosition.column] == colour) {
                queue.push(possiblePosition);
            }
        }

        // DOWN
        possiblePosition = Position(currentPosition.row + 1, currentPosition.column);
        if (isValid(possiblePosition)) {
            
            if (grid[possiblePosition.row][possiblePosition.column] == colour) {
                queue.push(possiblePosition);
            }
        }
    }

    display();
}

bool Board::isValid(Position position) {
    return (position.row >= 0 && position.row < rows && position.column >= 0 && position.column < cols);
}