#pragma once

#include <iostream>
#include "ColorEnum.hpp"
#include "Square.hpp"

using namespace std;


class Street : public Square{

private:
    float rentPrice;
    float housePrice;
    float rentPriceWithHouse;
    float rentPriceWithHotel;

    int numOfHouses;
    bool hasHotel;
    Color color;

public:
    Street(std::string name,float price,Color color,float housePrice);
     // Override display method
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

       
    

};