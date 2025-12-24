#include "position.h"

Position::Position() {}

Position::Position(int row, int column) : row(row), column(column) {}

bool Position::equals(Position position) {
    return (this->row == position.row && this->column == position.column);
}