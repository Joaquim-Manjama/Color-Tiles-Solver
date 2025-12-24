#include "solver.h"

#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

Solver::Solver() {}

Solver::Solver(Board board, int maxMoves) : board(board), maxMoves(maxMoves) {}

vector<Movement> Solver::solve()
{
    std::vector<Movement> empty;

    // Quick check
    if (board.gameWon()) return empty;

    // BFS queue stores board states and the moves to reach them
    using State = std::pair<Board, std::vector<Movement>>;
    std::queue<State> queue;
    std::unordered_set<std::string> visited;

    std::string start = board.serialize();
    visited.insert(start);
    queue.push({board.copy(), {}});

    while (!queue.empty()) {
        auto currentState = queue.front();
        queue.pop();
        
        Board currentBoard = currentState.first;
        std::vector<Movement> moves = currentState.second;

        // Don't expand past maxMoves
        if ((int)moves.size() >= maxMoves) continue;

        Movement directions[4] = {LEFT, UP, RIGHT, DOWN};
        for (Movement currentDirection : directions) {
            Board nextBoard = currentBoard.copy();
            std::string before = nextBoard.serialize();

            nextBoard.move(currentDirection);

            std::string after = nextBoard.serialize();

            // Skip moves that don't change the board
            if (after == before) continue;

            // Skip already visited states
            if (visited.find(after) != visited.end()) continue;

            // Build new move sequence
            std::vector<Movement> sequence = moves;
            sequence.push_back(currentDirection);

            // If solved, return sequence
            if (nextBoard.gameWon()) return sequence;

            // Mark visited and enqueue if we can still expand
            visited.insert(after);
            if ((int)sequence.size() < maxMoves) {
                queue.push({nextBoard, sequence});
            }
        }
    }

    // No solution within maxMoves
    return empty;
} 