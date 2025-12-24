#include <iostream>
#include "board.h"
#include "solver.h"
#include <raylib.h>
#include <string>
#include <map>

using namespace std;

void test_one();

void draw(int numCells, int cellSize);
void updateResolution(int value, int &numCells, int &cellSize);

const int WIDTH = 1200;
const int HEIGHT = 800;

Board board;

map<Colour, Color> colourMap = {
    {Colour::BLOCK, DARKGRAY},
    {Colour::RED_BLOCK, RED},
    {Colour::YELLOW_BLOCK, YELLOW},
    {Colour::BLUE_BLOCK, BLUE}
};

int main()
{
    int numCells = 4;
    int cellSize = HEIGHT / numCells;

    board = Board(numCells, numCells);
    int colours[4] = {Colour::BLOCK, Colour::RED_BLOCK, Colour::YELLOW_BLOCK, Colour::BLUE_BLOCK};
    int currentColour = 0;

    InitWindow(WIDTH, HEIGHT, "Color Tiles Solver");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Handle Input
        if (IsKeyPressed(KEY_UP) )
            updateResolution(1, numCells, cellSize);

        if (IsKeyPressed(KEY_DOWN))
            updateResolution(-1, numCells, cellSize);

        // Update

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);

        draw(numCells, cellSize);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); 
    return 0;
}

void draw(int numCells, int cellSize)
{
    // DrawBackground
    DrawRectangle(0, 0, numCells * cellSize, numCells * cellSize, BROWN);

    // Draw Grid
    for (int i = 0; i <= numCells; i++) 
    {
        DrawLine(i * cellSize, 0, i * cellSize, HEIGHT, BLACK);
        DrawLine(0, i * cellSize, HEIGHT, i * cellSize, BLACK);
    }

    // Draw Cells

    // Intructions Text
    DrawText("****  Settings  ****", 850, 50, 30, WHITE);
    
    string text = "Resolution: " + to_string(numCells) + "x" + to_string(numCells); 
    DrawText(text.c_str(), 850, 110, 20, WHITE);
    DrawText("** Use UP/DOWN Arrow Keys to change **", 850, 140, 10, LIGHTGRAY);

    DrawText("****  Place Tiles  ****", 820, 230, 30, WHITE);
    DrawText("Current tile:", 850, 320, 20, WHITE);
    DrawText("** Click to place tiles on the grid **", 850, 350, 10, LIGHTGRAY);


}

void updateResolution(int value, int &numCells, int &cellSize) {
    numCells = value > 0 ? min(8, numCells + 1) : max(4, numCells - 1);
    cellSize = HEIGHT / numCells;

    board = Board(numCells, numCells);
}

void test_one()
{
    // Game game = Game();

    // game.play();

    Board board = Board(4, 4);

    // Level One Board
    //      1 1 2
    //      2 0 2
    //      1 1 2

    cout << "Level One" << endl;

    // Red blocks
    board.insert(Position(0, 2), Colour::RED_BLOCK);
    board.insert(Position(1, 2), Colour::RED_BLOCK);
    board.insert(Position(1, 3), Colour::RED_BLOCK);
    board.insert(Position(2, 1), Colour::RED_BLOCK);

    // Yellow Blocks
    board.insert(Position(0, 0), Colour::YELLOW_BLOCK);
    board.insert(Position(0, 1), Colour::YELLOW_BLOCK);
    board.insert(Position(0, 3), Colour::YELLOW_BLOCK);
    board.insert(Position(1, 0), Colour::YELLOW_BLOCK);

    // Blue Block
    board.insert(Position(1, 1), Colour::BLUE_BLOCK);
    board.insert(Position(2, 0), Colour::BLUE_BLOCK);
    board.insert(Position(2, 2), Colour::BLUE_BLOCK);
    board.insert(Position(3, 1), Colour::BLUE_BLOCK);

    // BLOCK
    board.insert(Position(2, 3), Colour::BLOCK);

    board.display();

    Solver solver = Solver(board, 2);

    vector<Movement> solution = solver.solve();

    if (solution.empty())
    {
        cout << "No solution found within the given move limit." << endl;
    }
    else
    {

        for (Movement move : solution)
        {
            cout << move << ",  ";
        }

        cout << endl;
    }
}