#include "game.h"
#include <iostream>

using namespace std;

Game::Game()
{
    board = Board(3, 3);
    initialize();
    levelOne();
}

void Game::play()
{

    int option;

    do
    {

        cout << "*** Make a move ***" << endl;
        cout << "1. LEFT" << endl;
        cout << "2. UP" << endl;
        cout << "3. RIGHT" << endl;
        cout << "4. DOWN" << endl;
        cout << "5. Exit" << endl;
        cout << ": ";

        cin >> option;

        switch (option)
        {

        case 1:
            board.move(Movement::LEFT);
            break;

        case 2:
            board.move(Movement::UP);
            break;

        case 3:
            board.move(Movement::RIGHT);
            break;

        case 4:
            board.move(Movement::DOWN);
            break;

        case 5:
            cout << "BYE:(" << endl;
            break;

        default:
            cout << "Invalid Move!" << endl;
            break;
        }

        if (board.gameWon())
        {
            cout << "Congratulations! You have won the game!" << endl;
            break;
        }

    } while (option != 5);
}

void Game::levelOne()
{
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

    board.display();
}

void Game::initialize()
{
    // Initial Board
    cout << "Initial board " << endl;
    board.display();
}