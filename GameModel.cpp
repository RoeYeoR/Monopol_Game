#include "GameModel.hpp"
#include "Player.hpp"



GameModel::GameModel() : currentPlayerIndex(0) {
    
    board = Board::getInstance().getBoard();
    
}

void GameModel::addPlayer(std::shared_ptr<Player>& player) {
    players.push_back(player);
}

void GameModel::movePlayer(int playerIndex, int diceResult) {
    // Logic to move the player on the board
    // Update player position and check for landing on properties
    players[playerIndex]->MoveOnBoard(diceResult);
}

void GameModel::buyProperty(int playerIndex, Point2D& square) {
    // Logic for a player to buy a property
    std::shared_ptr<Player>* p =  Board::getInstance().checkSquareOwnerShip(board[square.getX()][square.getY()]);
    if( p == nullptr)
    {   
        notify("No ownership found. Offering player options.");   
        Board::getInstance().offerPlayerOptions(board[square.getX()][square.getY()]);
    }
    else if( *p != players[currentPlayerIndex])
    {
        std::shared_ptr<Square>& currentSquare =  board[square.getX()][square.getY()];
        //currentSquare->display(std::cout);
        std::string ownerName = (*p)->getName();
        notify("This Square is owned by " + ownerName);
        float calculatedPrice = MonopolManager::getInstance().getActuallBillOfSquare(currentSquare,p);  
      
       if(!MonopolManager::getInstance().ChargePlayer(players[currentPlayerIndex],*p,calculatedPrice))
       {
           notify(players[currentPlayerIndex]->getName() + " went bankrupt ... All its properties were passed to " + ownerName);
       }
       else
       {
            notify("Transfer of " + std::to_string(currentSquare->getPrice()) + "₪ was done Successfully!");
       }
    }
    else
    {
         notify("Offering player upgrades.");
        Board::getInstance().offerPlayerUpgrades(board[square.getX()][square.getY()]);

    }
}

 std::vector<std::vector<std::shared_ptr<Square>>>& GameModel::getBoard() {
    return board;
}

 std::vector<std::shared_ptr<Player>>& GameModel::getPlayers()  {
    return players;
}

void GameModel::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

int GameModel::getCurrentPlayerIndex() const {
    return currentPlayerIndex;
}
