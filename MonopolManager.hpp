#pragma once

#include <iostream>
#include "Board.hpp"
#include "Chance.hpp"
#include "Square.hpp" 
#include "Tax.hpp" 
#include "WaterCompany.hpp" 
#include "ElectricCompany.hpp" 
#include "EdgeSquare.hpp" 
#include <ctime> 
#include <cstdlib>  // For rand() and srand()
#include "Player.hpp"

class Player;  // Forward declaration


using namespace std;

class MonopolManager{

    private:
        //Board board; 
        std::vector<std::shared_ptr<Player>> players;
        std::vector<Chance> chanceCards;
        std::vector<std::string> chanceStrings;
        std::shared_ptr<Player> currentPlayer; 
        MonopolManager();

    public:
         // Deleted copy constructor and assignment operator
        MonopolManager(const MonopolManager&) = delete;
        MonopolManager& operator=(const MonopolManager&) = delete;

        // Static method to get the instance of the singleton
        static MonopolManager& getInstance() {
            static MonopolManager instance; // Guaranteed to be destroyed, instantiated on first use
            return instance;
        }

        std::vector<std::shared_ptr<Player>>& getPlayers();
        std::shared_ptr<Player>& getCurrentPlayer();
        void setCurrentPlayer(std::shared_ptr<Player> p);
        std::vector<Chance>& getChanceCards();
        int RollDice();
        const std::shared_ptr<Player>* CheckStreetOwner(const std::shared_ptr<Square>& square);
        const std::shared_ptr<Player>* CheckTrainOwner(const std::shared_ptr<Square>& square);
        const std::shared_ptr<Player>* CheckWaterCompanyOwner(const std::shared_ptr<Square>& square);
        const std::shared_ptr<Player>* CheckElectricCompanyOwner(const std::shared_ptr<Square>& square);
        void CheckTaxPrice(Tax* tax);
        void AddChance();
        void AddCommunityChest();
        
        void BuyStreet(Street* street);
        void BuyTrain(Train* train);
        void BuyWaterCompany(WaterCompany* waterCompany);
        void BuyElectricCompanyOwner(ElectricCompany* electricCompany);
        void CheckEdgeSquare(EdgeSquare* edgeSquare);

};