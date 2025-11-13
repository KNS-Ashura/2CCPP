//
// Created by tomgi on 30/10/2025.
//

#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"
#include <vector>
#include <string>

#include "Tile.h"

class Game {

    private:
        int playerNb;
        int round = 9;
        int tileIndex = 0;

        bool isNextToMe = false;
        std::vector<Player*> players;
        Board* board;
        Tile* tile;

    public:
        Game();
        ~Game();

        void launchGame();

        void initPlayer(int playerNb);
        void initBoard(int playerNb);
        void initTile(int playerNb);

        void displayBoard() const;
        void displayPlayers() const;
        void displayPlayerAtIndex(int index) const;

        void displayTilesList(int index) const;
        void displayTiles(int index) const;

        bool isPossiblePlace(int playerIndex, int index, int Y, int X);
        bool checkLeft(const std::vector<std::vector<std::string>> &b, int dx, int dy, const std::string &filled,
                       const std::string &filled2);
        bool checkRight(const std::vector<std::vector<std::string>> &b, int dx, int dy, const std::string &filled,
                        const std::string &filled2);
        bool checkUp(const std::vector<std::vector<std::string>> &b, int dx, int dy, const std::string &filled,
                     const std::string &filled2);
        bool checkDown(const std::vector<std::vector<std::string>> &b, int dx, int dy, const std::string &filled,
                       const std::string &filled2);

        bool isPossibleStart(int x, int y) const;

        void placeTile(int playerIndex, int index,int X, int Y);

        void askPlayerNumber();
        void askMove(int playerIndex);
        void askSartingCoord(int playerIndex);

        void flipTile(int index);
        void rotateTile(int index);
        void placeStone(int playerIndex);
        void removeStone(int playerIndex);

        std::string findColor(const std::string& colorName);

        int getPlayerNb() const;
        int getTileIndex() const;
        bool getNextToMe() const;

        void setTileIndex(int tileIndex);
        void setNextToMe(bool nexToMe);
        int getBiggestSquare(int playerIndex);

        int determineWinner();
        int countGrassTile(int playerIndex);
        void final1x1Tile(int playerIndex);
};



#endif //GAME_H
