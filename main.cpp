#include <iostream>
#include "board.h"

using namespace std;

int main() {

    Board board = Board(3, 3);

    // Initial Board
    cout << "Initial board " << endl;
    board.initialize();
    board.display();

    // Level One Board
    //      1 1 2
    //      2 0 2
    //      1 1 2

    cout << "Level One" << endl;

    // Red blocks
    board.insert(Position(0, 0), Colour::RED);
    board.insert(Position(0, 1), Colour::RED);
    board.insert(Position(2, 0), Colour::RED);
    board.insert(Position(2, 1), Colour::RED);

    //Yellow Blocks
    board.insert(Position(0, 2), Colour::YELLOW);
    board.insert(Position(1, 0), Colour::YELLOW);
    board.insert(Position(1, 2), Colour::YELLOW);
    board.insert(Position(2, 2), Colour::YELLOW);

    board.display();

    //Move Right
    board.move(Movement::RIGHT);
    board.deleteMatch(Colour::YELLOW);

    // Move UP
    board.move(Movement::UP);
    board.deleteMatch(Colour::RED);

	return 0;
}
