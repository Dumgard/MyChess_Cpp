//
// Created by danil on 8/22/2021.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include "Tools.h"
#include "Piece.h"

#include <utility>

using namespace Chess;

struct Player {
//=========================================== Constructors
    inline Player() :
        player_color(BLANK_COLOR),
        i_am_bot(false),
        king_(nullptr),
        player_pieces(nullptr) {}
    inline explicit Player(Color_t _clr, bool _is_bot = false,
                  std::vector<Piece*>* _pieces = new std::vector<Piece*> {}, Piece* _king = nullptr) :
        player_color(_clr),
        i_am_bot(_is_bot),
        king_(_king),
        player_pieces(_pieces) {}
    inline Player(const Player& right) :
        player_color(right.player_color),
        i_am_bot(right.i_am_bot),
        king_(right.king_),
        player_pieces(new std::vector<Piece*>) {*player_pieces = *(right.player_pieces);}
    inline ~Player(){
        reset();
    }
//=========================================== Operators
    Player& operator=(const Player& right);
    Player& operator=(Player&& right) noexcept;
    Player& operator+=(Piece&& piece);
    Player& operator-=(Piece* piece);
//=========================================== Methods
    Color_t color() const;
    bool is_bot() const;
    inline Player& bot_on(){this->i_am_bot = true; return *this;}
    inline Player& bot_off(){this->i_am_bot = false; return *this;}

    Piece* king();                         // get-function for POINTER to king
    Player& search_for_king();              // search for king in player_pieces
    std::vector<Piece*>& pieces();                           // get-function for REFERENCE to player_pieces
    //=========================================== RAII
    Player& reset();
//=========================================== Members
    std::vector<Piece*>* player_pieces;
private:
    Color_t player_color;
    bool i_am_bot;
    Piece* king_;                         // It may be used in "if"-statements : if (p.king_idx()+1) { ... } since there is no king if king_index is -1
//=========================================== End
};


std::ostream& operator<<(std::ostream& os, std::vector<Piece>& object);
std::ostream& operator<<(std::ostream& os, Player& object);



#endif //CHESS_PLAYER_H
