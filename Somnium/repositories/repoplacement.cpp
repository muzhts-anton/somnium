#include "repoplacement.h"


RepoPlacement::RepoPlacement(unsigned short row, unsigned short column) {
    _row = static_cast<Row>(row);
    _column = column;
}

int RepoPlacement::getRow() {
    return static_cast<int>(_row);
}

int RepoPlacement::getColumn() {
    return static_cast<int>(_column);
}

RepoPlacement &RepoPlacement::operator++() {
    if(_row == Row::UP) {
        _row = Row::DOWN;
    } else {
        _row = Row::UP;
        ++_column;
    }

    return *this;
}
