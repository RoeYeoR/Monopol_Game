#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <vector>
#include <memory>
#include <functional>
#include "Square.hpp"
#include "Player.hpp"

class GameModel {
public:
    GameModel();
    void addPlayer(std::shared_ptr<Player>& player);
    void movePlayer(int playerIndex, int diceResult);
    void buyProperty(int playerIndex, Point2D& square);
    std::vector<std::vector<std::shared_ptr<Square>>>& getBoard();
    std::vector<std::shared_ptr<Player>>& getPlayers();
    void nextTurn();  // Move to the next player's turn
    int getCurrentPlayerIndex() const;

    using NotifyFunc = std::function<void(const std::string&)>;
    
    void setNotifyFunction(NotifyFunc func) {
        notify = func;
    }

private:
    std::vector<std::vector<std::shared_ptr<Square>>> board;
    std::vector<std::shared_ptr<Player>> players;
    int currentPlayerIndex;
    NotifyFunc notify;
};

#endif 
