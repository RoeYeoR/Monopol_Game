#pragma once

#include <iostream>
#include <vector>
#include "Street.hpp"
#include "Chance.hpp"
#include "Train.hpp"
#include "CommunityChest.hpp"
#include "Point2D.hpp"
#include "MonopolManager.hpp"



class Player{

    private:
        string name;
        float money;
        Point2D currentPosition;
        bool hasOwnElectricCompany,hasOwnWaterCompany;
        std::vector<Street> streets;
        std::vector<Train> trains;
        std::vector<Chance> ChanceCards;
        std::vector<CommunityChest> CommunityChestCards;

    public:
        Player(std::string name); 
        void MoveOnBoard(int diceResult);  
        std::string getName();
        float getMoney();
        float setMoney(float newMoney);
        Point2D& getCurrentPosition();
        const std::vector<Street>& getStreets() const;
        const std::vector<Train>& getTrains() const;
        const std::vector<Chance>& getChanceCards() const;
        const bool gethasOwnWaterCompany() const;
        const bool gethasOwnElectricCompany() const;
        bool AddChance();
        bool PurchaseStreet(Street* street);
        bool PurchaseTrain(Train* train);
        void displayShort(std::ostream& os) const;
        void displayLong(std::ostream& os) const;
};