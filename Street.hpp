#pragma once

#include <iostream>
#include "ColorEnum.hpp"
#include "Square.hpp"

using namespace std;


class Street : public Square{

private:
   
    float price;
    float rentPrice;
    float housePrice;
    float rentPriceWithHouse;
    float rentPriceWithHotel;

    int numfHouses;
    bool hasHotel;
    Color color;

public:
    Street(std::string name,float price,Color color,float housePrice);
     // Override display method
   
    float getPrice();
    float getRentPrice();
    float getHousePrice();
    float getRentPriceWithHouse();
    float getRentPriceWithHotel();
    int getNumfHouses();
    bool getHasHotel();
    Color getColor();

    void display(std::ostream& os) const override;

       
    

};