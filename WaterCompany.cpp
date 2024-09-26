#include "WaterCompany.hpp"

WaterCompany::WaterCompany() :Square("Default waterSquare",150) {}
WaterCompany::WaterCompany(std::string name) : Square(name,150) {}


void WaterCompany::display(std::ostream& os) const
{
    os << name << std::endl;
}