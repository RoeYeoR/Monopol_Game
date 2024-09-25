#include "Train.hpp"

  int Train::count = 0;  

  Train::Train(std::string name): Square(name), price(200) {
        count++;

  };

  float Train::getPrice()
  {
     return price;
  }

 void Train::display(std::ostream& os) const 
 {
      os << "Train Square: " << name << std::endl;

 }

