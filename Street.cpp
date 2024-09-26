#include "Street.hpp"
using namespace std;

Street::Street(std::string name,float price,Color color,float housePrice): Square(name,price)
,color(color), housePrice(housePrice) {hasHotel = false;}


float Street::getRentPrice()
{
return rentPrice;
}
float Street::getHousePrice()
{
 return housePrice;
}
float Street::getRentPriceWithHouse()
{
 return rentPriceWithHouse;
}
float Street::getRentPriceWithHotel()
{
return rentPriceWithHotel;
}
int Street::getNumOfHouses()
{
 return numOfHouses;
}
bool Street::getHasHotel()
{
 return hasHotel;
}
Color Street::getColor()
{
return color;
}


void Street::addHouse()
{
     numOfHouses++;
}

void Street::addHotel()
{
     hasHotel =true;
}

void Street::display(std::ostream& os) const
{
     os << "Street name: " << name << "," << "price:" << price <<  "," << "color group:" << color <<std::endl;
    
}
