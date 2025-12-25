#include <iostream>
#include "board.h"
#include "solver.h"
#include <raylib.h>
#include <string>
#include <map>

using namespace std;

// Function Declarations
void draw(int numCells, int cellSize, Colour currentColour);
void updateResolution(int value, int &numCells, int &cellSize);
string displaySolution(vector<Movement> solution);

// Constants and Global Variables
const int WIDTH = 1200;
const int HEIGHT = 800;

const int MIN_CELLS = 3;
const int MAX_CELLS = 8;

const int NUM_COLOURS = 6;

int movesRemaining = 5;
int colours[NUM_COLOURS] = {    Colour::BLOCK, Colour::RED_BLOCK, Colour::YELLOW_BLOCK,
                                Colour::BLUE_BLOCK, Colour::ORANGE_BLOCK, Colour::LIGHT_BLUE_BLOCK};

Board board;
vector<Movement> solution;


map<Colour, Color> colourMap = {
    {Colour::BLOCK, DARKGRAY},
    {Colour::RED_BLOCK, RED},
    {Colour::YELLOW_BLOCK, YELLOW},
    {Colour::BLUE_BLOCK, BLUE},
    {Colour::ORANGE_BLOCK, ORANGE},
    {Colour::LIGHT_BLUE_BLOCK, SKYBLUE}
};

map<Movement, string> movementMap = {
    {LEFT, "LEFT"},
    {UP, "UP"},
    {RIGHT, "RIGHT"},
    {DOWN, "DOWN"}
};

int main()
{
    int numCells = MIN_CELLS;
    int cellSize = HEIGHT / numCells;

    board = Board(numCells, numCells);
    int currentColour = 0;


    InitWindow(WIDTH, HEIGHT, "Color Tiles Solver");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Handle Input

        // Change Resolution
        if (IsKeyPressed(KEY_UP) && IsKeyDown(KEY_LEFT_SHIFT))
            updateResolution(1, numCells, cellSize);

        if (IsKeyPressed(KEY_DOWN) && IsKeyDown(KEY_LEFT_SHIFT))
            updateResolution(-1, numCells, cellSize);

        // Change Current Tile Colour
        if (GetMouseWheelMove() > 0 )
            currentColour = (currentColour + 1) % NUM_COLOURS;

        if (GetMouseWheelMove() < 0 )
            currentColour = (currentColour - 1 + NUM_COLOURS) % NUM_COLOURS;

        // Place Tile on Grid
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos = GetMousePosition();
            int col = mousePos.x / cellSize;
            int row = mousePos.y / cellSize;

            if (row < numCells && col < numCells) 
                board.insert(Position(row, col), (Colour) colours[currentColour]);

            solution = {};
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mousePos = GetMousePosition();
            int col = mousePos.x / cellSize;
            int row = mousePos.y / cellSize;

            if (row < numCells && col < numCells) 
                board.removePosition(Position(row, col));

            solution = {};
        }

        // PLAY
        if (IsKeyPressed(KEY_UP) && !IsKeyDown(KEY_LEFT_SHIFT)) {
            board.move(UP);

            if (board.gameWon()) {
                board = Board(numCells, numCells);
                solution = {};
                movesRemaining += 1;
            }
        }

        if (IsKeyPressed(KEY_DOWN) && !IsKeyDown(KEY_LEFT_SHIFT)) {
            board.move(DOWN);

            if (board.gameWon()) {
                board = Board(numCells, numCells);
                solution = {};
                movesRemaining += 1;
            }
        }

        if (IsKeyPressed(KEY_LEFT)) {
            board.move(LEFT);

            if (board.gameWon()) {
                board = Board(numCells, numCells);
                solution = {};
                movesRemaining += 1;
            }
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            board.move(RIGHT);

            if (board.gameWon()) {
                board = Board(numCells, numCells);
                solution = {};
                movesRemaining += 1;
            }
        }


        // Change Moves Remaining for Solution
        if (IsKeyPressed(KEY_KP_ADD)) {
            movesRemaining = min(20, movesRemaining + 1);
            solution = {};
        }

        if (IsKeyPressed(KEY_KP_SUBTRACT)) {
            movesRemaining = max(1, movesRemaining - 1);
            solution = {};
        }

        // Get Solution
        if (IsKeyPressed(KEY_ENTER)) {
            Solver solver = Solver(board, movesRemaining); 
            solution = solver.solve();
        }

        // Update

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);

        draw(numCells, cellSize, (Colour) currentColour);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); 
    return 0;
}

void draw(int numCells, int cellSize, Colour currentColour)
{
    // DrawBackground
    DrawRectangle(0, 0, HEIGHT, HEIGHT, BROWN);

    // Draw Cells
    const int (*gridPtr)[8] = board.getGrid();

    for (int i = 0; i < numCells; i++) 
    {
        for (int j = 0; j < numCells; j++) 
        {
            Colour cellColour = static_cast<Colour>(gridPtr[i][j]);

            if (cellColour != Colour::EMPTY) 
                DrawRectangle(j * cellSize, i * cellSize, cellSize, cellSize, colourMap.at(cellColour));
        }
    }

    // Draw Grid
    for (int i = 0; i < numCells - 1; i++) 
    {
        int position = i * cellSize + cellSize;
        DrawLine(position, 0, position, HEIGHT, BLACK);
        DrawLine(0, position, HEIGHT, position, BLACK);
    }

    // Intructions Text
    DrawText("****  Settings  ****", 850, 40, 25, WHITE);
    
    string text = "Resolution: " + to_string(numCells) + "x" + to_string(numCells); 
    DrawText(text.c_str(), 850, 80, 20, WHITE);
    DrawText("** Use LSHIFT + UP/DOWN Arrow Keys to change **", 805, 110, 15, LIGHTGRAY);

    DrawLine(800, 130, WIDTH, 130, GRAY); // Separator Line

    DrawText("****  Place Tiles  ****", 820, 170, 25, WHITE);

    DrawText("Current tile:", 850, 230, 20, WHITE);
    DrawRectangle(1000, 215, 50, 50, colourMap.at((Colour)colours[currentColour]));
    DrawText("** Use MOUSE WHEEL to change tile **", 850, 290, 15, LIGHTGRAY); 
    DrawText("** LEFT Click to PLACE tiles on the grid **", 850, 320, 13, LIGHTGRAY);
    DrawText("** RIGHT Click to REMOVE tiles from the grid **", 850, 350, 13, LIGHTGRAY);

    DrawLine(800, 370, WIDTH, 370, GRAY); // Separator Line

    DrawText("****  Play  ****", 850, 410, 25, WHITE);
    DrawText("** Use Arrow Keys to move blocks **", 850, 450, 15, LIGHTGRAY);

    DrawLine(800, 470, WIDTH, 470, GRAY); // Separator Line

    DrawText("****  Solution  ****", 850, 510, 25, WHITE);
    text = "Moves remaining: " + to_string(movesRemaining); 
    DrawText(text.c_str(), 850, 550, 15, LIGHTGRAY);
    DrawText("** Use +/- keys to change **", 805, 580, 15, LIGHTGRAY);
    DrawText("** Press Enter to get solution  **", 850, 610, 15, LIGHTGRAY);
    DrawText(displaySolution(solution).c_str(), 800, 640, 15, LIGHTGRAY);
}

void updateResolution(int value, int &numCells, int &cellSize) {
    numCells = value > 0 ? min(MAX_CELLS, numCells + 1) : max(MIN_CELLS, numCells - 1);
    cellSize = HEIGHT / numCells;

    board = Board(numCells, numCells);
    solution = {};
}

string displaySolution(vector<Movement> solution) {
    string text = "Solution: ";

    if (solution.empty()) {
        text += "No solution found within the given move limit.";
    } else {
        for (Movement move : solution) {
            text += movementMap.at(move) + ", ";
        }
    }

    return text;
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