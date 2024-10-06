#include "Chance.hpp"

Chance::Chance() : Square("Default Chance Name"), wasInUse(false) {}
Chance::Chance(std::string name) : Square(name){ wasInUse =false;}

bool Chance::getWasInUse()
{
    return wasInUse;
}


void Chance::display(std::ostream& os) const
{
    os << "Chance: " << name << std::endl;
}

std::string Chance::display() const
{
    std::ostringstream os;
    os << "Chance: " << name << std::endl;
    return os.str();
}