//
// Created by danil on 8/22/2021.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Player.h"
#include "Move.h"

using std::shared_ptr;
using std::make_shared;

struct Board {
//=========================================== Constructors
    inline explicit Board(int _w = 8, int _h = 8,
          int _h_turn = 0, int _turn = 0) :
        width_(_w),
        height_(_h),
        half_turn_(_h_turn),
        turn_(_turn),
        castles_{false, false, false, false},
        passant_(Position()),
        player_white(make_shared<Player>(WHITE, false)),
        player_black(make_shared<Player>(BLACK, false)) {}
    // ALSO there should be board-construction by save-file, like with Forsyth-Edwards Notation
    inline ~Board(){
        player_black.reset();
        player_white.reset();
    }
//=========================================== Operators
    Board& operator=(const Board& right);
    std::vector<Piece*>& operator()(Color_t clr);
//=========================================== Methods
    int w() const;
    int h() const;
    int turn() const;
    int h_turn() const;
    bool castles(Color_t clr, int bool_if_castle_long) const;
    bool if_passant() const;
    Position passant() const;

    bool set_passant(Position pos);
    Board& reset_passant();
    Board& reset_castles();

    Board& FEN_decoding(std::string code);
    std::string FEN_encoding() const;
    Board& fill_board(GameMode_t gm);

    void create_moves();

    //============================ Interface



//=========================================== Members
    shared_ptr<Player> player_white;
    shared_ptr<Player> player_black;
private:
    int width_;
    int height_;
    int turn_;
    int half_turn_;
    bool castles_[4];
    Position passant_;
//=========================================== End
};


std::ostream& operator<<(std::ostream& os, Board& object);

#endif //CHESS_BOARD_H
