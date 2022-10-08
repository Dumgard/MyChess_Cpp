//
// Created by danil on 8/22/2021.
//

#include "Board.h"

using namespace Chess;
using std::string;
using std::pair;

std::map<const char, const pair<Color_t, Name_t>> Name_dict {
        {'p', pair<Color_t, Name_t>(BLACK, PAWN)},
            {'P', pair<Color_t, Name_t>(WHITE, PAWN)},
        {'n', pair<Color_t, Name_t>(BLACK, KNIGHT)},
            {'N', pair<Color_t, Name_t>(WHITE, KNIGHT)},
        {'b', pair<Color_t, Name_t>(BLACK, BISHOP)},
            {'B', pair<Color_t, Name_t>(WHITE, BISHOP)},
        {'r', pair<Color_t, Name_t>(BLACK, ROOK)},
            {'R', pair<Color_t, Name_t>(WHITE, ROOK)},
        {'q', pair<Color_t, Name_t>(BLACK, QUEEN)},
            {'Q', pair<Color_t, Name_t>(WHITE, QUEEN)},
        {'k', pair<Color_t, Name_t>(BLACK, KING)},
            {'K', pair<Color_t, Name_t>(WHITE, KING)},

};

extern std::map<const char, const int> Notation;
extern std::map<const char, const int>& N_;

// =================================================================================================
// Operators for Board

Board& Board::operator=(const Board& right){
    /*  This operator copies all of ints: width, height, turn, half_turn, castles.
     *  Then it calls make_shared<Player> for both players, with same parameters
     *  as in the right ones.
     *  After successful making of both players we copy Pieces-vectors from
     *  players of right board to the our ones.                                               */
    if (this == &right) return *this;
    this->width_ = right.width_;
    this->height_ = right.height_;
    this->turn_ = right.turn_;
    this->half_turn_ = right.half_turn_;
    for (int i = 4; i < 4; ++i) this->castles_[i] = right.castles_[i];

    this->player_white = std::make_shared<Player>(
            WHITE, right.player_white->is_bot(), nullptr, nullptr);
    this->player_black = std::make_shared<Player>(
            BLACK, right.player_black->is_bot(), nullptr, nullptr);

    v_deepCopy(*(this->player_white->player_pieces), *(right.player_white->player_pieces));
    v_deepCopy(*(this->player_black->player_pieces), *(right.player_black->player_pieces));

    right.player_white->search_for_king();
    right.player_black->search_for_king();

    return *this;
}

std::vector<Piece*>& Board::operator()(Color_t clr){
    if ((bool)clr) return this->player_white->pieces();
    else return this->player_black->pieces();
}

std::ostream& operator<<(std::ostream& os, Board& object){
    using std::cout;    using std::endl;
    cout << "Shape of the board:" << '\t' << object.w() << 'x' << object.h() << endl;
    cout << "How much moves done:" << '\t' << object.turn() << endl;
    cout << "How much half-turns:" << '\t' << object.h_turn() << endl;
    cout << "Is en-passant move possible:" << '\t' << object.if_passant() << ',' << '\t' << object.passant() << endl;
    cout << "Castles:" << endl;
    cout << '\t' << "White (short):" << '\t' << object.castles(WHITE, 0) << endl;
    cout << '\t' << "White (long):" << '\t' << object.castles(WHITE, 1) << endl;
    cout << '\t' << "Black (short):" << '\t' << object.castles(BLACK, 0) << endl;
    cout << '\t' << "Black (long):" << '\t' << object.castles(BLACK, 1) << endl;

    cout << *(object.player_black) << *(object.player_white);

    return os;
}

// =================================================================================================
// Methods for Board
    // =================================================================================================
    // Set-get-reset-functions

int Board::w() const {
    return this->width_;
}
int Board::h() const {
    return this->height_;
}
int Board::turn() const {
    return this->turn_;
}
int Board::h_turn() const {
    return this->half_turn_;
}
bool Board::castles(Color_t clr, int bool_if_castle_long) const {
    if (bool_if_castle_long > 1 or bool_if_castle_long < 0)
        throw std::exception("There is only two types of castles, short = 0 and long = 1");
    return this->castles_[(1 - (int)clr)*2 + bool_if_castle_long];
}
bool Board::if_passant() const {
    return ((this->passant_.y == 2 or this->passant_.y == 5)
        and (this->passant_.x >= 0 and this->passant_.x < 8));
}
Position Board::passant() const {
    return this->passant_;
}


bool Board::set_passant(Position pos) {
    // Sets the pos to this->passant_ and returns TRUE if passant-position is legal;
    // else, returns FALSE without changing this->passant_
    if ((pos.y == 2 or pos.y == 5) and (pos.x >= 0 and pos.x < 8)){
        this->passant_ = pos;
        return true;
    } return false;
}

Board& Board::reset_passant() {
    this->passant_ = Position(-1, -1);
    return *this;
}

Board& Board::reset_castles() {
    for (bool& castle : this->castles_) castle = false;
    return *this;
}

    // =================================================================================================
    // Functionality-methods

Board& Board::FEN_decoding(string code) {
    // game_mode_classic_fe_notation = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    /*  This function is universal method of filling the board using FEN (Forsyth–Edwards Notation).
     *  Starting from field "a8" we go through all the remain fields giving players a piece with its according
     *  position on board. Then method fills castles, an opportunity of 'en passant' move,
     *  numbers of turns and half-turns.                                                                    */
    string nums = "12345678";
    int x = 0;
    int y = 7;
    int ind = 0;
                                                            // At this point we fill players' pieces according to FEN.
    while (code[ind] != ' '){
        if (code[ind] == '/'){
            x = 0;
            --y;
        } else if (nums.find(code[ind]) != string::npos){
            x += (int)(code[ind] - '0');
        } else {
            if (Name_dict[code[ind]].first)                 // The same as ( Name_dict[code[ind]].first == WHITE )
                this->player_white->pieces().emplace_back(new Piece(WHITE, Name_dict[code[ind]].second, Position(x, y)));
            else
                this->player_black->pieces().emplace_back(new Piece(BLACK, Name_dict[code[ind]].second, Position(x, y)));
            ++x;
        }
        ++ind;
    }
    ++ind;
                                                            // If white to move, then there were even number of turns
    if (code[ind] == 'w') this->turn_ = 0;
    else this->turn_ = 1;
                                                            // Skip until Castles-part of code
    ind += 2;
    this->castles_[0] = (code[ind++] == 'K');
    this->castles_[1] = (code[ind++] == 'Q');
    this->castles_[2] = (code[ind++] == 'k');
    this->castles_[3] = (code[ind] == 'q');     ind += 2;
                                                            // This is a 'en passant' part of FEN-code
    if (code[ind] != '-'){
        this->set_passant(Position(N_[code[ind]], (int)(code[ind + 1] - '1')));
        ind += 3;
    } else ind += 2;

    this->half_turn_ = (int)(code[ind++] - '0');
    if (code[ind] != ' ') {                                 // We have to be sure that if number of half-turns is
        this->half_turn_ *= 10;                             // more then 9 that we will process it correctly.
        this->half_turn_ += (int)(code[ind++] - '0');
    }   ++ind;
                                                            // Then just add (num - 1)*2 to turns, and we'll obtain exactly
                                                            // how much moves there have been
    if (code.size() == ind + 1){
        this->turn_ += ((int)(code[ind] - '0') - 1) * 2;
    } else {
        int dec = (int)(code[ind++] - '0');
        this->turn_ += (dec * 10 + (int)(code[ind] - '0') - 1) * 2;
    }

    return *this;
}

string Board::FEN_encoding() const {
                                                // COMING SOON
                                                // ==================11111111111111111111111333333333333333333333333
                                                // ==================11111111111111111111111333333333333333333333333
    return "BLANK";
}

Board& Board::fill_board(GameMode_t gm) {
    Player& wp = *(this->player_white);
    Player& bp = *(this->player_black);

    wp.bot_off();
    bp.bot_off();
    wp.reset();
    bp.reset();

    wp.player_pieces = new std::vector<Piece*> {};
    bp.player_pieces = new std::vector<Piece*> {};
    this->reset_passant().reset_castles();

    string game_mode_code = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";     // FOR NOW - let it be by default
    switch (gm) {
        case CLASSIC_MODE:
            game_mode_code = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
            break;
        case FISHER_MODE:
            break;
        case SAVE_FILE_MODE:
            break;
        case CUSTOM_MODE:
            break;
    }
    Board::FEN_decoding(game_mode_code);
    this->player_white->search_for_king();
    this->player_black->search_for_king();
    return *this;
}



void Board::create_moves() {

}