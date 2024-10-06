#pragma once

#include <iostream>
#include <vector>
#include <sstream>
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
        std::vector<int> diceResults;
        int countTurns;
        bool isInJail;
        bool isBankrupt; // don't have enough money to pay his bills

    public:
        Player(std::string name); 
        void MoveOnBoard(int diceResult);  
        void GoToSquare(Point2D& p);
        std::string getName();
        float getMoney();
        bool getIsInJail();
        bool getIsBankrupt();
        void changeMoney(float newMoney);
        void setMoney(float newMoney);
        void setIsBankrupt(bool var);
        void setHasOwnWaterCompany(bool var);
        void setHasOwnElectricCompany(bool var);
        void setIsInJail(bool var);
        Point2D& getCurrentPosition();
        std::vector<Street>& getStreets();
        std::vector<Train>& getTrains();
        std::vector<Chance>& getChanceCards();
        const bool gethasOwnWaterCompany() const;
        const bool gethasOwnElectricCompany() const;
        Chance* getChance();
       Chance* getCommunityChest();
        bool PurchaseStreet(Street* street);
        bool PurchaseTrain(Train* train);
        bool PurchaseHouse(Street* street);
        bool PurchaseHotel(Street* street);
        bool PurchaseWaterCompany(WaterCompany* waterCompany);
        bool PurchaseElectricCompany(ElectricCompany* electricCompany);
        void displayShort(std::ostream& os) const;
        void displayLong(std::ostream& os) const;
        std::string displayLong() const;
};