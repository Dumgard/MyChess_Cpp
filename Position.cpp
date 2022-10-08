//
// Created by danila on 8/22/2021.
//

#include "Position.h"
#include "iostream"

// =================================================================================================
// Operators for Position

Position& Position::operator=(const Position& right){
    if (this == &right) return *this;                               // In case of self-assignment
    this->x = right.x;
    this->y = right.y;
    return *this;
}

Position Position::operator+(const Position& right) const{
    return Position(this->x + right.x, this->y + right.y);
}

Position Position::operator-(const Position& right) const{
    return Position(this->x - right.x, this->y - right.y);
}

Position& Position::operator+=(const Position& right){
    *this = *this + right;
    return *this;
}

Position& Position::operator-=(const Position& right){
    *this = *this - right;
    return *this;
}

bool Position::operator==(const Position& right) const{
    return ((this->x == right.x) and (this->y == right.y));
}

bool Position::operator!=(const Position& right) const{
    return !((*this) == right);
}

std::ostream& operator<<(std::ostream& os, const Position& object){
    os << '(' << object.x << ',' << object.y << ')';
    return os;
}

std::istream& operator>>(std::istream& is, Position& object){
    is >> object.x >> object.y;
    // if(  ) is.setstate(std::ios::failbit);                           Something to implement in case of errors
    return is;
}

// =================================================================================================
// Methods for Position
