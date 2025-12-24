#include <iostream>
#include <queue>
#include "board.h"

using namespace std;

// Main constructor
Board::Board(int rows, int cols) : rows(rows), cols(cols)
{

    // Get maximum size of grid
    size = sizeof(grid) / sizeof(grid[0]);
}

// Set all relevant grid positions to zero
void Board::initialize()
{

    // Iterate though whole grid
    for (int i = 0; i < size; i++)
    {

        for (int j = 0; j < size; j++)
        {

            // Only zero relevant part of grid
            if (i < rows && j < cols)
            {
                grid[i][j] = 0;

                // Avoid junk values
            }
            else
            {
                grid[i][j] = -2;
            }
        }
    }
}

// Display the relevant grid to console
void Board::display()
{

    cout << "[" << endl;

    for (int i = 0; i < rows; i++)
    {

        cout << " [ ";

        for (int j = 0; j < cols; j++)
        {
            cout << grid[i][j];

            if (j < cols - 1)
            {
                cout << ", ";
            }
        }

        cout << " ]" << endl;
    }

    cout << "]" << endl;
}

// Insert a colour at a given position
void Board::insert(Position position, Colour colour)
{
    grid[position.row][position.column] = colour;

    int newValue = 1;

    for (const auto &currentColour : coloursInGrid)
    {

        if (currentColour.first == colour)
        {
            newValue = currentColour.second + 1;
            break;
        }
    }

    coloursInGrid.insert_or_assign(colour, newValue);
}

// Move the board in a given direction
void Board::move(Movement direction)
{
    switch (direction)
    {

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

// Move functions for each direction
void Board::left()
{
    bool space;

    for (int i = 0; i < rows; i++)
    {
        space = false;

        for (int j = 0; j < cols; j++)
        {

            if (space)
            {
                grid[i][j - 1] = grid[i][j];
                grid[i][j] = 0;
            }

            if (grid[i][j] == 0)
                space = true;
        }
    }
}

void Board::right()
{
    bool space;

    for (int i = 0; i < rows; i++)
    {
        space = false;

        for (int j = cols - 1; j >= 0; j--)
        {

            if (space)
            {
                grid[i][j + 1] = grid[i][j];
                grid[i][j] = 0;
            }

            if (grid[i][j] == 0)
                space = true;
        }
    }
}

void Board::up()
{
    bool space;

    for (int i = 0; i < cols; i++)
    {
        space = false;

        for (int j = 0; j < rows; j++)
        {

            if (space)
            {
                grid[j - 1][i] = grid[j][i];
                grid[j][i] = 0;
            }

            if (grid[j][i] == 0)
                space = true;
        }
    }
}

void Board::down()
{
    bool space;

    for (int i = 0; i < cols; i++)
    {
        space = false;

        for (int j = rows - 1; j >= 0; j--)
        {

            if (space)
            {
                grid[j + 1][i] = grid[j][i];
                grid[j][i] = 0;
            }

            if (grid[j][i] == 0)
                space = true;
        }
    }
}

// Delete matched colours starting from a given position
void Board::deleteMatch(Colour colour, Position startingPos)
{
    queue<Position> queue;

    const int rowDirections[4] = {0, -1, 0, 1};
    const int columnDirections[4] = {-1, 0, 1, 0};
    const int numOfDirections = 4;

    bool found = false;

    // Use bfs to delete
    Position position = startingPos;
    queue.push(position);

    while (!queue.empty())
    {
        Position currentPosition = queue.front();
        grid[currentPosition.row][currentPosition.column] = 0;

        queue.pop();

        for (int i = 0; i < numOfDirections; i++)
        {

            Position possiblePosition = Position(currentPosition.row + rowDirections[i], currentPosition.column + columnDirections[i]);

            if (isValid(possiblePosition))
            {

                if (grid[possiblePosition.row][possiblePosition.column] == colour)
                    queue.push(possiblePosition);
            }
        }
    }

    coloursInGrid.erase(colour);

    if (gameWon())
        cout << "You Completed the Puzzle!";
}

// Check for matches on the board
void Board::checkMatches()
{

    // Iterate over a copy to avoid modifying the map while iterating it (erase in deleteMatch)
    vector<pair<Colour, int>> coloursCopy;
    for (const auto &p : coloursInGrid)
    {
        coloursCopy.push_back(p);
    }

    for (const auto &currentColour : coloursCopy)
    {
        match(currentColour.first, currentColour.second);
    }
}

// Match function to find and delete matches of a given colour
void Board::match(Colour colour, int count)
{
    int matchCount = count;
    int nodeRow, nodeColumn;

    queue<Position> queue;
    vector<Position> visited;

    const int rowDirections[4] = {0, -1, 0, 1};
    const int columnDirections[4] = {-1, 0, 1, 0};
    const int numOfDirections = 4;

    bool found = false;

    // Find the first node of the given colour
    for (nodeRow = 0; nodeRow < rows; nodeRow++)
    {

        for (nodeColumn = 0; nodeColumn < cols; nodeColumn++)
        {
            if (grid[nodeRow][nodeColumn] == colour)
            {
                found = true;
                break;
            }
        }

        if (found)
            break;
    }

    if (!found)
        return;

    // Use bfs to delete
    Position position = Position(nodeRow, nodeColumn);
    queue.push(position);
    visited.push_back(position);
    matchCount--;

    while (!queue.empty())
    {
        Position currentPosition = queue.front();
        queue.pop();

        for (int i = 0; i < numOfDirections; i++)
        {

            Position possiblePosition = Position(currentPosition.row + rowDirections[i], currentPosition.column + columnDirections[i]);

            if (isValid(possiblePosition) && !positionVisited(possiblePosition, visited))
            {

                if (grid[possiblePosition.row][possiblePosition.column] == colour)
                {
                    queue.push(possiblePosition);
                    visited.push_back(possiblePosition);
                    matchCount--;
                }
            }
        }
    }

    if (matchCount == 0)
        deleteMatch(colour, position);
}

// Check if a position has already been visited
bool Board::positionVisited(Position position, vector<Position> positions)
{

    for (Position currentPosition : positions)
    {

        if (currentPosition.equals(position))
            return true;
    }

    return false;
}

// Check if a position is valid on the board
bool Board::isValid(Position position)
{
    return (position.row >= 0 && position.row < rows && position.column >= 0 && position.column < cols);
}

// Check if the game has been won
bool Board::gameWon()
{

    for (int i = 0; i < rows; i++)
    {

        for (int j = 0; j < cols; j++)
        {

            if (grid[i][j] != 0)
            {
                return false;
            }
        }
    }

    return true;
}