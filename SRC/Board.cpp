//
// Created by tomgi on 03/11/2025.
//

#include "../Header/Board.h"
#include "cmath"
#include <cstdlib>
#include <ctime>

using namespace std;

Board::Board(int playerNb) {
    this->playerNumber = playerNb;
    if (playerNb < 5) {
        this->boardSize = 20;
    }else if (playerNb > 5) {
        this->boardSize = 30;
    }
}

vector<vector<std::string>> Board::createNewBoard() const {
    vector<vector<std::string>> newBoard(getBoardSize(), vector<std::string>(getBoardSize(), "."));
    return newBoard;
}

void Board::placeBonusSquares() {
    srand(time(0)); // initialise la graine aléatoire une seule fois

    int min = 0;
    int max = getBoardSize() - 1;

    int robery = static_cast<int>(ceil(1.5 * getPlayerNumber()));
    int stone = static_cast<int>(ceil(0.5 * getPlayerNumber()));
    int tileEx = getPlayerNumber();

    for (int i = 0; i < robery; i++) {
        int a = rand() % (max - min + 1) + min;
        int b = rand() % (max - min + 1) + min;
        board[a][b] = 'R';
    }

    for (int i = 0; i < stone; i++) {
        int c = rand() % (max - min + 1) + min;
        int d = rand() % (max - min + 1) + min;
        board[c][d] = 'S';
    }

    for (int i = 0; i < tileEx; i++) {
        int e = rand() % (max - min + 1) + min;
        int f = rand() % (max - min + 1) + min;
        board[e][f] = 'E';
    }
}

vector<vector<std::string>>& Board::getBoard() {
    return this->board;
}

int Board::getBoardSize() const {
    return this->boardSize;
}

int Board::getPlayerNumber() const {
    return this->playerNumber;
}

void Board::setBoard(vector<vector<std::string>> newBoard) {
    this->board = newBoard;
}









