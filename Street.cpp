#include "Street.hpp"
using namespace std;


int Street::count = 0;

Street::Street(std::string name,float price,Color color,float housePrice): Square(name,price)
,color(color), housePrice(housePrice) ,id(count)
{ 
     hasHotel = false;
     count++;
}

int Street::getID()
{
     return id;
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

std::string Street::display() const
{
    std::ostringstream os;
     os <<  "Street name: " << name <<  "\n"<< "price:" << price << "\n"<<  "color group:" << color <<std::endl;
     return os.str();

}

bool Street::operator==(Street& other) const
{
     return id == other.getID(); 
}
