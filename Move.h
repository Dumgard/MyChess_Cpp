//
// Created by danila on 8/22/2021.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "Piece.h"
#include "Tools.h"
#include "map"

using namespace Chess;

extern std::map<const char, const int> Notation;
extern std::map<const char, const int>& N_;

struct Move {
//=========================================== Constructors
    inline Move() = delete;                                                     // <------ No way we gonna need trivial
    inline Move(const Position& _from, const Position& _to,                     // constructor for any move
                Move_t _type = FORWARD, Piece* actor_ = nullptr) :
        from_(_from),
        to_(_to),
        type_(_type),
        actor(actor_),
        captured(nullptr),
        permuted_to(nullptr) {}
    inline Move(const Move& right) = default;
    inline ~Move() = default;
//=========================================== Operators
    Move& operator=(const Move& right) = default;
    bool operator==(const Move& right) const = default;                         // MAY BE A PROBLEM IN FUTURE, if I add some more members to Move
    bool operator!=(const Move& right) const = default;
//=========================================== Methods
    Position from() const;
    Position to() const;
    Move_t type() const;
//=========================================== Members
    Piece* actor;
    Piece* captured;
    Piece* permuted_to;
private:
    Position from_;
    Position to_;
    Move_t type_;
//=========================================== End
};


#endif //CHESS_MOVE_H
