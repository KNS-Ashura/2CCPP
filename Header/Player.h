//
// Created by tomgi on 03/11/2025.
//

#ifndef TDP_PLAYER_H
#define TDP_PLAYER_H

#include <string>
#include <vector>


class Player {
    private:
        std::string playerName;
        std::string playerColor;
        std::string playerColorCode;
        int TileExchangeCoupon;

    public:

        Player(const std::string &name, const std::string &color, const std::string &colorCode, int &exchangeCoupon);

        ~Player();

        std::string getName();
        std::string getColor();
        std::string getColorCode();

        int getTileExchangeCoupon() const;
        void setExchangeCoupon(int exchangeCoupon);

};


#endif //TDP_PLAYER_H