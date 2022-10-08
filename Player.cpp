//
// Created by danil on 8/22/2021.
//

#include "Player.h"

// =================================================================================================
// Operators for Player

Player& Player::operator=(const Player& right) {
    if (this == &right) return *this;
    reset();

    player_pieces = new std::vector<Piece*> {};
    for (auto & item : *right.player_pieces){
        (*player_pieces).emplace_back(new Piece(*item));
    }
    search_for_king();
    return *this;
}

Player& Player::operator=(Player&& right) noexcept {
    this->player_color = right.player_color;
    this->i_am_bot = right.i_am_bot;
    this->king_ = right.king_;
    this->player_pieces = right.player_pieces;

    right.player_pieces = nullptr;
    right.king_ = nullptr;
    return *this;
}

Player& Player::operator+=(Piece&& piece) {
    (*(this->player_pieces)).push_back(&piece);
    return *this;
}

Player& Player::operator-=(Piece* piece) {
    int index = Chess::find(*(this->player_pieces), piece);
    if (index != -1){
        delete (*this->player_pieces)[index];
        (*this->player_pieces).erase((*this->player_pieces).begin() + index);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, std::vector<Piece*>& object) {
    int i = 0;
    for (auto & piece : object){
        std::cout << *piece << "  ";
        ++i;
        if (!(i%8)) std::cout << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, Player& object) {
    std::string clr = "BLACK";
    if ((bool)object.color()) clr = "WHITE";
    std::cout << "Player " << clr << ':' << std::endl;
    std::cout << '\t' << "I am bot: " << object.is_bot() << '\t' << "King is: " << *(object.king()) << std::endl;
    std::cout << object.pieces() << std::endl;
    return os;
}

// =================================================================================================
// Methods for Player

Color_t Player::color() const {
    return this->player_color;
}

bool Player::is_bot() const {
    return this->i_am_bot;
}

Piece* Player::king() {
    /*  This method provides get-function for player's king pointer.
     *  If king is nullptr then function calls search_for_king() and,
     *  after that - returns the pointer. If king is absent - method returns nullptr.        */
    search_for_king();
    return this->king_;
}

Player& Player::search_for_king() {
    /*  This function searches for KING in player's vector of Pieces,
     *  then give the pointer to king to this->king_.              */
    this->king_ = nullptr;
    for (Piece*& item : this->pieces()){
        if ((item->color() == this->color()) and (item->name() == KING)){
            this->king_ = item;
            break;
        }
    }
    return *this;
}

std::vector<Piece*>& Player::pieces() {
    return *(this->player_pieces);
}



Player& Player::reset() {
    v_deepDelete(pieces());
    delete player_pieces;
    player_pieces = nullptr;
    king_ = nullptr;
    return *this;
}