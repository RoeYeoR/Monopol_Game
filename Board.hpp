#pragma once

#include <iostream>
#include <vector>
#include <memory>  // For std::shared_ptr
#include "Point2D.hpp"
#include "Street.hpp"
#include "Chance.hpp"
#include "CommunityChest.hpp"
#include "Train.hpp"
#include "Tax.hpp"
#include "WaterCompany.hpp"
#include "ElectricCompany.hpp"
#include "Square.hpp"
#include "EdgeSquare.hpp"

class Player;  // Forward declaration

class Board {
  private:
    const int rows = 11;
    const int cols = 11;
    //std::vector<std::vector<Square>> board;
    std::vector<std::vector<std::shared_ptr<Square>>> board;
    std::vector<Street> totalStreets;
    Board();

  public:
     // Deleted copy constructor and assignment operator
        Board(const Board&) = delete;
        Board& operator=(const Board&) = delete;

        // Static method to get the instance of the singleton
        static Board& getInstance() {
            static Board instance; // Guaranteed to be destroyed, instantiated on first use
            return instance;
        }

    std::vector<Street>& getTotalStreets();
    void setSquare(int row, int col, std::shared_ptr<Square> square);
    std::vector<std::vector<std::shared_ptr<Square>>>& getBoard();

    std::shared_ptr<Player>* checkSquareOwnerShip(const std::shared_ptr<Square>& square);
    void offerPlayerOptions(const std::shared_ptr<Square>& square,sf::Text& gameMessage);
    void offerPlayerUpgrades(const std::shared_ptr<Square>& square,sf::Text& gameMessage);

};
