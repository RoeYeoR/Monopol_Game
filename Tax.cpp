#include "Tax.hpp"

Tax::Tax(std::string desc, float price) : Square(name,price) {}


void Tax::display(std::ostream& os) const
{
    os << "Tax: " << name << std::endl;
}