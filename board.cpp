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

void Board::insert(Position position, Colour colour) {
    grid[position.row][position.column] = colour;

    int newValue = 1;

    for (const auto& currentColour : coloursInGrid) {

        if (currentColour.first == colour) {
            newValue = currentColour.second + 1;
        }
    }

    coloursInGrid.insert_or_assign(colour, newValue);
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

    checkMatches();

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
    int nodeRow, nodeColumn;
    queue<Position> queue;

    const int rowDirections[4] = {0, -1, 0, 1};
    const int columnDirections[4] = {-1, 0, 1, 0};
    const int numOfDirections = 4;

    bool found = false;
    
    // Find the first node of the given colour
    for (nodeRow = 0; nodeRow < rows; nodeRow++) {
        
        for (nodeColumn = 0; nodeColumn < cols; nodeColumn++) {
            if (grid[nodeRow][nodeColumn] == colour) {
                found = true;
                break;
            } 
        }

        if (found) break;
    }

    if (!found) return;

    // Use bfs to delete
    Position position = Position(nodeRow, nodeColumn);
    queue.push(position);

    while (!queue.empty()) {
        Position currentPosition = queue.front();
        grid[currentPosition.row][currentPosition.column] = 0;
        
        queue.pop();

        for (int i = 0; i < numOfDirections; i++) {
            
            Position possiblePosition = Position(currentPosition.row + rowDirections[i], currentPosition.column + columnDirections[i]);
            
            if (isValid(possiblePosition)) {
                
                if (grid[possiblePosition.row][possiblePosition.column] == colour) queue.push(possiblePosition);
            }
        }
    }

    coloursInGrid.erase(colour);

    display();

    if (gameWon()) {
        cout << "You Completed the Puzzle!";
    }
}

void Board::checkMatches() {

    for (const auto& currentColour: coloursInGrid) {
        match(currentColour.first, currentColour.second);
    }
}

void Board::match(Colour colour, int requiredCount) {
    std::queue<Position> q;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    const int dRow[4] = {0, -1, 0, 1};
    const int dCol[4] = {-1, 0, 1, 0};

    // 1️⃣ Find a starting position
    Position start{-1, -1};
    for (int r = 0; r < rows && start.row == -1; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == colour) {
                start = {r, c};
                break;
            }
        }
    }

    // 2️⃣ If no matching colour exists, stop
    if (start.row == -1) return;

    // 3️⃣ BFS
    int matchCount = 0;
    q.push(start);
    visited[start.row][start.column] = true;

    while (!q.empty()) {
        Position cur = q.front();
        q.pop();
        matchCount++;

        for (int i = 0; i < 4; i++) {
            Position next{
                cur.row + dRow[i],
                cur.column + dCol[i]
            };

            if (isValid(next) &&
                !visited[next.row][next.column] &&
                grid[next.row][next.column] == colour) {

                visited[next.row][next.column] = true;
                q.push(next);
            }
        }
    }

    // 4️⃣ Check match condition
    if (matchCount >= requiredCount) {
        std::cout << "BOOM!" << std::endl;
        deleteMatch(colour);
    }
}


bool Board::isValid(Position position) {
    return (position.row >= 0 && position.row < rows && position.column >= 0 && position.column < cols);
}

bool Board::gameWon() {

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            if (grid[i][j] != 0) {
                return false;
            }
        }
    }

    return true;
}