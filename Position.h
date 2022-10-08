//
// Created by danila on 8/22/2021.
//

#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H

#include "iostream"

struct Position {
//=========================================== Constructors
    inline Position() :
            x(0),
            y(0) {}
    inline Position(int _x, int _y):
            x(_x),
            y(_y) {}
    inline Position(const Position& pos) = default;
    inline ~Position() = default;                                   // destructor is still UNDEFINED
//=========================================== Operators
    Position& operator=(const Position& right);
    Position operator+(const Position& right) const;
    Position operator-(const Position& right) const;
    Position& operator+=(const Position& right);
    Position& operator-=(const Position& right);
    bool operator==(const Position& right) const;
    bool operator!=(const Position& right) const;
//=========================================== Members
    int x;
    int y;
//=========================================== End
};

std::ostream& operator<<(std::ostream& os, const Position& object);
std::istream& operator>>(std::istream& is, Position& object);



#endif //CHESS_POSITION_H
