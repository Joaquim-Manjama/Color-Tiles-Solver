#include <iostream>
#include "board.h"
#include "solver.h"
#include <raylib.h>

using namespace std;

void test_one();

int main()
{

    test_one();
    // const int screenWidth = 800;
    // const int screenHeight = 450;

    // InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // //--------------------------------------------------------------------------------------

    // // Main game loop
    // while (!WindowShouldClose())    // Detect window close button or ESC key
    // {
    //     // Update
    //     //----------------------------------------------------------------------------------
    //     // TODO: Update your variables here
    //     //----------------------------------------------------------------------------------

    //     // Draw
    //     //----------------------------------------------------------------------------------
    //     BeginDrawing();

    //         ClearBackground(RAYWHITE);

    //         DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    //     EndDrawing();
    //     //----------------------------------------------------------------------------------
    // }

    // // De-Initialization
    // //--------------------------------------------------------------------------------------
    // CloseWindow(); 
    return 0;
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