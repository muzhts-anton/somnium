#ifndef REPOPLACEMENT_H
#define REPOPLACEMENT_H


class RepoPlacement
{
public:
    RepoPlacement(unsigned short row, unsigned short column);

    RepoPlacement &operator++();

    int getRow();
    int getColumn();

    ~RepoPlacement() = default;

private:
    enum class Row {
        UP = 0,
        DOWN,
    };

    Row _row;
    unsigned short _column;
};

#endif // REPOPLACEMENT_H
