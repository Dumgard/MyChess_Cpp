//
// Created by danila on 8/22/2021.
//

#include "Move.h"
#include "map"

std::map<const char, const int> Notation {
        {'a', 0},   {'A', 0},
        {'b', 1},   {'B', 1},
        {'c', 2},   {'C', 2},
        {'d', 3},   {'D', 3},
        {'e', 4},   {'E', 4},
        {'f', 5},   {'F', 5},
        {'g', 6},   {'G', 6},
        {'h', 7},   {'H', 7},

};
std::map<const char, const int>& N_ = Notation;
using namespace Chess;

// =================================================================================================
// Operators for Move



// =================================================================================================
// Methods for Move

Position Move::from() const{
    return this->from_;
}

Position Move::to() const{
    return this->to_;
}

Move_t Move::type() const{
    return this->type_;
}