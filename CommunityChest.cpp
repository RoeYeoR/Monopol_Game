#include "CommunityChest.hpp"


CommunityChest::CommunityChest(): Square("Default CommunityChest") {wasInUse = false;}

CommunityChest::CommunityChest(std::string name):  Square(name) {wasInUse = false;} 

void CommunityChest::display(std::ostream& os) const
{
    os << "CommunityChest: " << name << std::endl;
}

std::string CommunityChest::display() const
{
    std::ostringstream os;
    os << "CommunityChest: " << name << std::endl;
     return os.str(); 
}