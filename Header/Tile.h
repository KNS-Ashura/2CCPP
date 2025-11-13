//
// Created by tomgi on 09/11/2025.
//

#ifndef TILE_H
#define TILE_H

#include <vector>

class Tile {
    private:
        std::vector<std::vector< std::vector<int>>> tiles;
        std::vector<std::vector< std::vector<int>>> usedTiles;

        int tilesNb;
        int playerNb;

    public:
        Tile(int playerNb);
        ~Tile();

        void addUsedTiles();
        void shuffleTiles();

        std::vector<std::vector< std::vector<int>>> getTiles();
        std::vector<std::vector< std::vector<int>>> &getUsedTiles();
        int getPlayerNb() const;
        int getTilesNb() const;

};



#endif //TILE_H
