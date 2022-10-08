//
// Created by danila on 8/21/2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "Position.h"
#include "Tools.h"
#include "iostream"

using namespace Chess;

struct Piece {
//=========================================== Constructors
    inline Piece() :
        piece_color(BLANK_COLOR),
        piece_name(BLANK_NAME),
        pos(Position()),
        turn(0) {}
    inline Piece(Color_t _clr, Name_t _nm, const Position& _pos = Position()) :
        piece_color(_clr),
        piece_name(_nm),
        pos(_pos),
        turn(0) {}
    inline Piece(const Piece& right) = default;
    inline ~Piece() = default;                                      // destructor is still UNDEFINED
//=========================================== Operators
    Piece& operator=(const Piece& right) = default;
    Piece& operator=(Piece&& right) noexcept;
    bool operator==(const Piece& right) const;
    bool operator!=(const Piece& right) const;
    bool operator^(const Piece& right) const;                       // BE CAREFUL: this is comparison BY ADDRESS OF PIECE
    Piece& operator++();
    const Piece operator++(int);
//=========================================== Methods
    Name_t name() const;
    Color_t color() const;
    Position get_pos() const;
    void set_pos(int _x, int _y);
//=========================================== Members
private:
    Color_t piece_color;
    Name_t piece_name;
    Position pos;
    int turn;
//=========================================== End
};


std::ostream& operator<<(std::ostream& os, Piece& object);



#endif //CHESS_PIECE_H
