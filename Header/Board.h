//
// Created by tomgi on 03/11/2025.
//

#ifndef TDP_BOARD_H
#define TDP_BOARD_H

#include <vector>
#include <string>

class Board {

    private:
        std::vector<std::vector<std::string>> board;
        int playerNumber;
        int boardSize;


    public:
        Board(int playerNb);
        ~Board();

        std::vector<std::vector<std::string>> createNewBoard() const;
        void placeBonusSquares();

        std::vector<std::vector<std::string>>& getBoard();
        int getBoardSize() const;
        int getPlayerNumber() const;

        void setBoard(std::vector<std::vector<std::string>> newBoard);
};


#endif //TDP_BOARD_H