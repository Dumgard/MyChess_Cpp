//
// Created by danil on 8/22/2021.
//

#ifndef CHESS_TOOLS_H
#define CHESS_TOOLS_H

#include "vector"
#include "xutility"

namespace Chess {

    enum Color_t {
        BLACK,
        WHITE,
        BLANK_COLOR = -1,
    };
    enum Name_t {
        PAWN, KNIGHT,
        BISHOP,ROOK,
        QUEEN, KING,
        BLANK_NAME = -1,
    };
    enum Move_t {
        FORWARD, CAPTURE,
        CASTLE_SHORT, CASTLE_LONG,
        PASSANT, PROMOTION,
    };
    enum GameMode_t {
        CLASSIC_MODE,
        FISHER_MODE,
        SAVE_FILE_MODE,
        CUSTOM_MODE,
    };

    template<typename T>
    inline int find(const std::vector<T>& arr, const T& item){
        auto iterator = std::find(arr.begin(), arr.end(), item);
        if (iterator != arr.end())
            return distance(arr.begin(), iterator);
        return -1;
    }

    template<typename T>
    inline bool in(const std::vector<T>& arr, const T& item){
        auto iterator = std::find(arr.begin(), arr.end(), item);
        if (iterator != arr.end())
            return true;
        return false;
    }

    template<typename T>
    void v_deepDelete(std::vector<T*>& vector_){
        for (T* & item : vector_) {
            delete item;
            item = nullptr;
        }
        vector_.clear();
    }

    template<typename T>
    inline void v_deepCopy(std::vector<T*>& vector_to, std::vector<T*>& vector_from){
        v_deepDelete(vector_to);
        for (T* & item : vector_from) vector_to.emplace_back(new T(*item));
    }

}


#endif //CHESS_TOOLS_H
