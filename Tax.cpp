#include "Tax.hpp"

Tax::Tax(std::string name, float price) : Square(name,price) {}


void Tax::display(std::ostream& os) const
{
    os << "Tax: " << name << std::endl;
}