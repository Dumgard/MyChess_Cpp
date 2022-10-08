//
// Created by danila on 8/21/2021.
//

#include "Piece.h"

using namespace Chess;

// =================================================================================================
// Operators for Piece

Piece& Piece::operator=(Piece&& right) noexcept {
    this->pos = right.pos;
    this->turn = right.turn;
    this->piece_name = right.piece_name;
    this->piece_color = right.piece_color;
    return *this;
}

bool Piece::operator==(const Piece& right) const {
    if (this == &right) return true;
    return
    (   (this->pos == right.pos) and
        (this->turn == right.turn) and
        (this->piece_name == right.piece_name) and
        (this->piece_color == right.piece_color)    );
}

bool Piece::operator!=(const Piece& right) const {
    return !((*this) == right);
}

bool Piece::operator^(const Piece& right) const{
    return (this == &right);
}

Piece& Piece::operator++(){
    ++(this->turn);
    return *this;
}

const Piece Piece::operator++(int){
    Piece old = *this;
    operator++();
    return old;
}

std::ostream& operator<<(std::ostream& os, Piece& object){
    char s;
    switch (object.name()) {
        case PAWN:
            s = 'p';
            break;
        case KNIGHT:
            s = 'n';
            break;
        case BISHOP:
            s = 'b';
            break;
        case ROOK:
            s = 'r';
            break;
        case QUEEN:
            s = 'q';
            break;
        case KING:
            s = 'k';
            break;
        case BLANK_NAME:
            s = 'o';
            break;
    }
    if ((bool)object.color()) s += ('A' - 'a');
    os << s << object.get_pos();
    return os;
}

// =================================================================================================
// Methods for Piece

Name_t Piece::name() const{
    Name_t tmp = this->piece_name;
    return tmp;
}

Color_t Piece::color() const{
    Color_t tmp = this->piece_color;
    return tmp;
}

void Piece::set_pos(int _x, int _y){
    this->pos = Position(_x, _y);
}

Position Piece::get_pos() const{
    return Position(this->pos.x, this->pos.y);
}
