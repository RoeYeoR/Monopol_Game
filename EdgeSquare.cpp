#include "EdgeSquare.hpp"


EdgeSquare::EdgeSquare(EdgeSquareType esType) : type(esType) {}


 EdgeSquareType EdgeSquare::getType()
 {
    return type;
 }

 void EdgeSquare::display(std::ostream& os) const 
 {
    os << "EdgeSquare: " << type << std::endl;

 }