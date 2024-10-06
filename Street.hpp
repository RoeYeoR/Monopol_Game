#pragma once

#include <iostream>
#include <sstream>
#include "ColorEnum.hpp"
#include "Square.hpp"

using namespace std;




class Street : public Square{

private:
    int id;
    float rentPrice;
    float housePrice;
    float rentPriceWithHouse;
    float rentPriceWithHotel;

    int numOfHouses;
    bool hasHotel;
    Color color;

public:
    Street(std::string name,float price,Color color,float housePrice);
    int getID();
    float getRentPrice();
    float getHousePrice();
    float getRentPriceWithHouse();
    float getRentPriceWithHotel();
    int getNumOfHouses();
    bool getHasHotel();
    Color getColor();
    void addHouse();
    void addHotel();
    void display(std::ostream& os) const override;
    std::string display() const;
    bool operator==(Street& other) const ;
    
    static int count;
       
    

};