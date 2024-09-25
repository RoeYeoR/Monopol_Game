#include "ElectricCompany.hpp"

ElectricCompany::ElectricCompany() :Square("Default Electric Square") ,price(150) {}

ElectricCompany::ElectricCompany(std::string name) : Square(name) ,price(150) {}

void ElectricCompany::display(std::ostream& os) const
{
    os << name << std::endl;
}