#include "Chance.hpp"

Chance::Chance() : Square("Default Chance Name"), wasInUse(false) {}
Chance::Chance(std::string name) :Square(name) ,wasInUse(false) {}
Chance::Chance(int id,std::string name) : Square(name), id(id){ wasInUse =false;}

int Chance::getID()
{
    return id;
}

bool Chance::getWasInUse()
{
    return wasInUse;
}

 void Chance::setWasInUse(bool var)
 {

    wasInUse = var;
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