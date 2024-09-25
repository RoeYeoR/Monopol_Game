#include "EdgeSquare.hpp"


EdgeSquare::EdgeSquare( std::string name) : Square(name) {}


 std::string EdgeSquare::getDescription()
 {
    return name;
 }

 void EdgeSquare::display(std::ostream& os) const 
 {
    os << "EdgeSquare: " << name << std::endl;

 }