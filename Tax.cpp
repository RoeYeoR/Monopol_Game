#include "Tax.hpp"

Tax::Tax(std::string desc, float price) : Square(name) , price(price) {}


 float Tax::getPrice()
 {

    return price;
 }


void Tax::display(std::ostream& os) const
{
    os << "Tax Desc: " << name << std::endl;
}