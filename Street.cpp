#include "Street.hpp"
using namespace std;

Street::Street(std::string name,float price,Color color,float housePrice): Square(name), price(price)
,color(color), housePrice(housePrice) {hasHotel = false;}


float Street::getPrice()
{
return price;
}
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
int Street::getNumfHouses()
{
 return numfHouses;
}
bool Street::getHasHotel()
{
 return hasHotel;
}
Color Street::getColor()
{
return color;
}


void Street::display(std::ostream& os) const
{
     os << "Street name: " << name << "," << "price:" << price <<  "," << "color group:" << color <<std::endl;
     
}
