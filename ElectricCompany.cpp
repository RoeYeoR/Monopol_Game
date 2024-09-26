#include "ElectricCompany.hpp"

ElectricCompany::ElectricCompany() :Square("Default Electric Square",150) {}

ElectricCompany::ElectricCompany(std::string name) : Square(name,150) {}

void ElectricCompany::display(std::ostream& os) const
{
    os << name << std::endl;
}