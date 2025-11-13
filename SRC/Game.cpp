//
// Created by tomgi on 30/10/2025.
//

#include "../Header/Game.h"

#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

Game::Game() {

    this->playerNb = 0;
    this->round = 9;

}

Game::~Game() {

}

void Game::launchGame() {

    askPlayerNumber();

    //initialisation
    initPlayer(getPlayerNb());
    initBoard(getPlayerNb());
    initTile(getPlayerNb());

    for (int i = 0; i < playerNb; i++) {
        askSartingCoord(i);
        displayBoard();
    }


    for (int rounds = 0; rounds < 2; rounds++) {
        cout << endl << "Round : " << rounds << endl;
        for (int i = 0; i < getPlayerNb(); i++) {
            askMove(i);
        }
    }

    cout << endl << endl;
    cout << "Last round ended starting the last part : " << endl;
    cout << endl <<endl;

    for (int i = 0; i < playerNb; i++) {
         final1x1Tile(i);
    }
    determineWinner();
}

void Game::initPlayer(int playerNb) {

    vector<string> colors = {
        "Blue",
        "Green",
        "Red",
        "Yellow",
        "Black",
        "Orange",
        "Purple",
        "Brown",
        "White"
    };

    for (int i = 0; i < playerNb; i++) {

        string playerName;
        cout << "Enter the player : " << i+1 << " Name -> ";
        cin >> playerName;

        for (int j = 0; j < colors.size(); ++j) {
            cout << colors[j] << " -> " << j+1 << endl;
        }
        cout << endl;

        string playerColor;
        int inputNb;
        cout << "Enter the player : " << i+1 << " Color -> ";
        while (true) {
            cin >> inputNb;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please enter a number -> ";
            }
            else if (inputNb < 1 || inputNb > colors.size()) {
                cout << "Number out of range, please try again -> ";
            }
            else {
                break;
            }
        }


        playerColor = colors[inputNb - 1];
        colors.erase(colors.begin() + inputNb - 1);

        string code = findColor(playerColor);
        cout << code << playerName << " -> " << playerColor << "\033[0m" << endl;

        int exchangecoupon = 1;

        players.push_back(new Player(playerName, playerColor, code, exchangecoupon));

    }
    displayPlayers();
}

void Game::initBoard(int playerNb) {
    board = new Board(playerNb);
    cout << endl << endl;
    cout << endl << "Displaying Board : " << endl;

    board->setBoard(board->createNewBoard());
    board->placeBonusSquares();
    displayBoard();
}

void Game::initTile(int playerNb) {

    cout << "Adding tiles in the game" << endl;

    tile = new Tile(playerNb);

    tile->addUsedTiles();
}

void Game::displayBoard() const {
    int size = board->getBoardSize();

    cout << "   ";
    for (int j = 0; j < size; j++) {
        if (j < 10)
            cout << j << "  ";
        else
            cout << j << " ";
    }
    cout << endl;

    cout << "  ";
    for (int j = 0; j < size; j++) {
        cout << "---";
    }
    cout << endl;

    for (int i = 0; i < size; i++) {
        if (i < 10)
            cout << i << " |";
        else
            cout << i << "|";

        for (int j = 0; j < size; j++) {
            cout << board->getBoard()[i][j] << "  ";
        }
        cout << endl;
    }

}

void Game::displayPlayers() const {
    cout << endl << endl;
    cout << endl << "Displaying Players : " << endl;
    cout << endl <<endl;

    for (int i = 0; i < playerNb; i++) {
        cout << players[i]->getColorCode() << i+1 << " -> " << players[i]->getName() << " -> " << players[i]->getColor() << "\033[0m" << endl;
    }
}

void Game::displayPlayerAtIndex(int index) const {
    cout << players[index]->getColorCode()  << "it's your turn : "<< players[index]->getName() << "\033[0m" << endl;
}

void Game::displayTilesList(int index) const {
    for (int i = 0; i < 5; i++) {
        cout << "tile nb : " << i+1 << endl;
        displayTiles(index + i);
    }
}

void Game::displayTiles(int index) const{    vector<vector<string>> displayer(10, vector<string>(10, "."));
    const auto currentTile = tile->getUsedTiles()[index];

    bool first = true;

    for (const auto& pos : currentTile) {
        int x = pos[0];
        int y = pos[1];

        if (first) {
            displayer[5 + x][5 + y] = "\033[31mX\033[0m"; // Rouge
            first = false;
        } else {
            displayer[5 + x][5 + y] = "X";
        }
    }

    for (int i = 0; i < displayer.size(); i++) {
        for (int j = 0; j < displayer.size(); j++) {
            cout << displayer[i][j] <<  "  ";
        }
        cout << endl;
    }
}

bool Game::isPossiblePlace(int playerIndex, int index,int X, int Y) {
    const auto currentTile = tile->getUsedTiles()[index];
    auto& b = board->getBoard();
    const string& color = players[playerIndex]->getColorCode();
    constexpr const char* RESET = "\033[0m";
    const string filled = color + "+" + RESET;
    const string filled2 = color + "*" + RESET;
    setNextToMe(false);

    if (b[X][Y]!="." && b[X][Y]!="E" && b[X][Y]!="R" && b[X][Y]!= "S" && b[X][Y]!= filled) {
        return false;
    }

    for (const auto & cell : currentTile) {


        int dy = cell[0] + Y;
        int dx = cell[1] + X;

        if (b[dy][dx]!="." && b[dy][dx]!="E" && b[dy][dx]!="R" && b[dy][dx]!= "S") {
            cout << "coucou" << endl;
            return false;
        }if (X == 0) {
            if (!checkRight(b, dx, dy, filled, filled2)) return false;
        }if (X == b.size()-1) {
            if (!checkLeft(b, dx, dy, filled, filled2)) return false;
        }if (Y == 0) {
            if (!checkDown(b, dx, dy, filled, filled2)) return false;
        }if (Y == b.size()-1){
            if (!checkUp(b, dx, dy, filled, filled2)) return false;
        }if (Y >= 1 && Y < b.size()-1) {
            if (!checkUp(b, dx, dy, filled, filled2)) return false;
            if (!checkDown(b, dx, dy, filled, filled2)) return false;
        }if (X >= 1 && X < b.size()-1) {
            if (!checkRight(b, dx, dy, filled, filled2)) return false;
            if (!checkLeft(b, dx, dy, filled, filled2)) return false;
        }
    }

    if (getNextToMe()) {
        return true;
    } else {
        return false;
    }
}

bool Game::checkLeft(const vector<vector<string>>& b,
                     int dx, int dy, const string& filled, const string& filled2){
    if (b[dy][dx - 1] == filled || b[dy][dx - 1] == filled2) {
        setNextToMe(true);
        return true;
    } else if (b[dy][dx - 1] == "." || b[dy][dx - 1]=="E" || b[dy][dx -1 ]=="R" || b[dy][dx - 1]== "S") {
        return true;
    } else {
        return false;
    }
}

bool Game::checkRight(const vector<vector<string>>& b,
                      int dx, int dy, const string& filled, const string& filled2){
    if (b[dy][dx + 1] == filled || b[dy][dx + 1] == filled2) {
        setNextToMe(true);
        return true;
    } else if (b[dy][dx + 1] == "." || b[dy][dx + 1]=="E" || b[dy][dx + 1 ]=="R" || b[dy][dx + 1]== "S") {
        return true;
    } else {
        return false;
    }
}

bool Game::checkUp(const vector<vector<string>>& b,
                   int dx, int dy, const string& filled, const string& filled2){
    if (b[dy - 1][dx] == filled || b[dy - 1][dx] == filled2) {
        setNextToMe(true);
        return true;
    } else if (b[dy - 1][dx] == "." || b[dy - 1][dx] == "E" || b[dy - 1][dx] == "S" || b[dy - 1][dx] == "R") {
        return true;
    } else {
        return false;
    }
}

bool Game::checkDown(const vector<vector<string>>& b,
                     int dx, int dy, const string& filled, const string& filled2){
    if (b[dy + 1][dx] == filled || b[dy + 1][dx] == filled2) {
        setNextToMe(true);
        return true;
    } else if (b[dy + 1][dx] == "." || b[dy + 1][dx] == "R" || b[dy + 1][dx] == "E" || b[dy + 1][dx] == "S") {
        return true;
    } else {
        return false;
    }
}

bool Game::isPossibleStart(int X, int Y) const {
    auto& b = board->getBoard();
    if (b.size() == 20) {
        if (X != 0 && Y != 0 && X != 19 && Y != 19) {
            if (b[X+1][Y] != "." || b[X][Y+1] != "." || b[X][Y] != "." || b[X-1][Y] != "." || b[X][Y-1] != ".") {
                return false;
            }else {
                return true;
            }
        }
    }else if (b.size() == 30) {
        if (X == 0 || Y == 0 || X == 29 || Y == 29) {
            if (b[X+1][Y] != "." || b[X][Y+1] != "." || b[X][Y] != "." || b[X-1][Y] != "." || b[X][Y-1] != ".") {
                return false;
            }else {
                return true;
            }
        }else {
            return false;
        }
    }
    return false;
}

void Game::placeTile(int playerIndex, int index,int X, int Y){
    const auto currentTile = tile->getUsedTiles()[index];
    auto& b = board->getBoard();
    const std::string& color = players[playerIndex]->getColorCode();
    constexpr const char* RESET = "\033[0m";

    for (const auto & i : currentTile) {
        for (int j = 0; j < i.size(); j++) {
            b[X + i[0]][Y + i[1]] = color + "+" + RESET;
        }
    }
    setTileIndex(getTileIndex()+1);
}

void Game::askPlayerNumber() {
    int inputNb;
    while (true) {
        cout << "Enter the number of players for this new game ->  ";
        cin >> inputNb;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number between 2 and 9" << endl;
        }
        else if (inputNb < 2 || inputNb > 9) {
            cout << "Please enter a number between 2 and 9" << endl;
        }
        else {
            playerNb = inputNb;
            break;
        }
    }


}

void Game::askMove(int playerIndex) {
    int y;
    int x;
    int newTileChosen;
    char chosenOption;
    bool notFinished = true;

    displayPlayerAtIndex(playerIndex);
    while (notFinished) {
        cout << "Take Tile (T)" << endl;
        cout << "Exchange Tile - "<< players[playerIndex]->getTileExchangeCoupon() <<" available (E)" << endl;
        cout << "Display Queue (D)" << endl;
        cout << "Place Tile (P)" << endl;
        cout << "Remove Stone (S)" << endl;
        cin >> chosenOption;

        switch (chosenOption) {
            case 'T':
                cout << "Tile to place : " << endl;
                displayTiles(getTileIndex());
                cout << "Flip tile (F)" << endl;
                cout << "Rotate tile (R)" << endl;
                cout << "Place tile (P)" << endl;
                break;
            case 'E':
                if (players[playerIndex]->getTileExchangeCoupon() > 0) {
                    cout << "List of next tiles : " << endl;
                    displayTilesList(getTileIndex());
                    cout << "Choose the number of the tile you want to exchange with : " << endl;
                    cin >> newTileChosen;
                    setTileIndex(getTileIndex()+newTileChosen-1);
                    players[playerIndex]->setExchangeCoupon(players[playerIndex]->getTileExchangeCoupon() - 1);
                    cout << "Chosen tile : " << endl;
                    displayTiles(getTileIndex());
                }
                else {
                    cout << "You don't have exchange coupon ! " << endl;
                }
                break;
            case 'D':
                cout << "List of next tiles : " << endl;
                displayTilesList(getTileIndex());
                break;
            case 'F':
                cout << "Tile to place : " << endl;
                flipTile(getTileIndex());
                displayTiles(getTileIndex());
                break;
            case 'R':
                cout << "Tile to place : " << endl;
                rotateTile(getTileIndex());
                displayTiles(getTileIndex());
                break;
            case 'P':
                while (true) {
                    cout << "Ligne of the RED \033[31mX\033[0m : ";
                    cin >> x;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input, please enter a valid number." << endl;
                        continue;
                    }

                    cout << "Column of the RED \033[31mX\033[0m : ";
                    cin >> y;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input, please enter a valid number." << endl;
                        continue;
                    }

                    if (isPossiblePlace(playerIndex,getTileIndex(), y, x)) {
                        placeTile(playerIndex, getTileIndex(), x, y);
                        break;
                    }
                    else {
                        cout << "You can't place a tile here. Try again." << endl;
                    }
                }

                displayBoard();
                notFinished = false;
                break;
            case 'S':
                cout << "You can use an exchange ticket to remove a stone on the board (X)" << endl;
                removeStone(playerIndex);
                break;
            default :
                cout << "Wrong input" << endl;
                break;
    }

    }
}

void Game::askSartingCoord(int playerIndex) {
    int x;
    int y;
    auto& b = board->getBoard();
    const std::string& color = players[playerIndex]->getColorCode();
    constexpr const char* RESET = "\033[0m";

    displayPlayerAtIndex(playerIndex);

    while (true) {
        cout << "Enter starting coord X : ";
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a valid number." << endl;
            continue;
        }

        cout << "Enter starting coord Y : ";
        cin >> y;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a valid number." << endl;
            continue;
        }
        break;
    }


    if (isPossibleStart(x,y)) {
        b[x][y] = color + "*" + RESET;
    }else {
        cout << "You can't start at coordinate " << x << ", " << y << endl;
    }
}

void Game::flipTile(int index) {

    auto &usedTile = tile->getUsedTiles();
    auto &currentTile = usedTile[index];
    for (auto &cell : currentTile) {
        cell[0] = -cell[0];
    }
}

void Game::rotateTile(int index) {
    auto &usedTile = tile->getUsedTiles();
    auto &currentTile = usedTile[index];
    for (auto &cell : currentTile) {
        int oldX = cell[0];
        int oldY = cell[1];
        cell[0] = oldY;
        cell[1] = -oldX;
    }
}

void Game::placeStone(int playerIndex) {
    int x;
    int y;
    auto& b = board->getBoard();
    const std::string& color = players[playerIndex]->getColorCode();
    constexpr const char* RESET = "\033[0m";
    cout << "You can place a stone, please choose where you want to place it :" << endl;
    while (true) {
        cout << "Enter starting coord X : ";
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a valid number." << endl;
            continue;
        }

        cout << "Enter starting coord Y : ";
        cin >> y;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a valid number." << endl;
            continue;
        }
        break;
    }
    b[x][y] = color + "X" + RESET;
    cout << "Stone placed !!" << endl;
    displayBoard();
}

void Game::removeStone(int playerIndex) {
    int x;
    int y;
    auto& b = board->getBoard();
    const std::string& color = players[playerIndex]->getColorCode();
    constexpr const char* RESET = "\033[0m";
    cout << "You can remove a stone using an exchange ticket, please choose which stone you want to remove :" << endl;
    while (true) {
        cout << "Enter starting coord X : ";
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a valid number." << endl;
            continue;
        }

        cout << "Enter starting coord Y : ";
        cin >> y;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a valid number." << endl;
            continue;
        }
        if (players[playerIndex]->getTileExchangeCoupon() > 0) {
            b[x][y] = color + "." + RESET;
            cout << "Stone removed !" << endl;
            displayBoard();
        }
        else {
            cout << "You don't have exchange coupon ! " << endl;
        }
        break;
    }
}

string Game::findColor(const string& colorName) {
    if (colorName == "Blue")   return "\033[34m";
    if (colorName == "Green")  return "\033[32m";
    if (colorName == "Red")    return "\033[31m";
    if (colorName == "Yellow") return "\033[33m";
    if (colorName == "Black")  return "\033[30m";
    if (colorName == "Orange") return "\033[38;5;208m";
    if (colorName == "Purple") return "\033[35m";
    if (colorName == "Brown")  return "\033[38;5;94m";
    if (colorName == "White")  return "\033[37m";
    return "\033[0m";
}

int Game::getPlayerNb() const {
    return playerNb;
}

int Game::getTileIndex() const {
    return tileIndex;
}

bool Game::getNextToMe() const {
    return this->isNextToMe;
}

void Game::setTileIndex(int newValue) {
    this->tileIndex = newValue;
}

void Game::setNextToMe(bool nexToMe) {
    this->isNextToMe = nexToMe;
}




int Game::getBiggestSquare(int playerIndex) {
    auto& b = board->getBoard();
    const string& color = players[playerIndex]->getColorCode();

    vector<vector<int>> dp(b.size(), vector<int>(b[0].size(), 0));
    int biggestSquare = 0;

    for (int i = 0; i < b.size(); ++i) {
        for (int j = 0; j < b[0].size(); ++j) {
            if (b[i][j].find(color) != string::npos) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
                biggestSquare = max(biggestSquare, dp[i][j]);
            }
        }
    }

    return biggestSquare;
}

int Game::determineWinner() {
    int winner = 0;
    int maxSquareSize = getBiggestSquare(0);

    for (int i = 1; i < players.size(); ++i) {
        int squareSize = getBiggestSquare(i);
        if (squareSize > maxSquareSize) {
            maxSquareSize = squareSize;
            winner = i;
        }
    }

    //égalité
    for (int i = 0; i < players.size(); ++i) {
        if (i != winner && getBiggestSquare(i) == maxSquareSize) {
            if (countGrassTile(i) > countGrassTile(winner)) {
                winner = i;
            }
        }
    }
    cout << "The winner is " << winner << endl;
    return winner;
}

int Game::countGrassTile(int playerIndex) {
    auto& b = board->getBoard();
    const string& color = players[playerIndex]->getColorCode();
    int grassCount = 0;

    for (int i = 0; i < b.size(); ++i) {
        for (int j = 0; j < b[0].size(); ++j) {
            if (b[i][j].find(color) != string::npos && b[i][j].find("+") != string::npos) {
                grassCount++;
            }
        }
    }

    return grassCount;
}



void Game::final1x1Tile(int playerIndex) {
    int x;
    int y;
    auto& b = board->getBoard();
    const std::string& color = players[playerIndex]->getColorCode();
    constexpr const char* RESET = "\033[0m";

    displayPlayerAtIndex(playerIndex);

    while (players[playerIndex]->getTileExchangeCoupon() > 0) {
        cout << "You can place a 1x1 tile using your Exchange coupon, please choose where you want to place it :" << endl;
        while (true) {
            cout << "Enter coord X: ";
            cin >> x;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please enter a valid number." << endl;
                continue;
            }

            cout << "Enter coord Y: ";
            cin >> y;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please enter a valid number." << endl;
                continue;
            }

            break;
        }
        if (isPossiblePlace(playerIndex, tile->getUsedTiles().size()-1, x, y)) {
            b[x][y] = color + "+" + RESET;
            cout << "1x1  tile placed !" << endl;
            players[playerIndex]->setExchangeCoupon(players[playerIndex]->getTileExchangeCoupon() - 1);
            displayBoard();
            break;
        }
        else {
            cout << "You can't place a tile here. Try again." << endl;
        }


    }


}









