#include "Train.hpp"

  int Train::count = 0;  

  Train::Train(std::string name): Square(name,200) {
     
        count++;

  };

 void Train::display(std::ostream& os) const 
 {
      os << "Train Square: " << name << std::endl;

 }

 std::string Train::display(std::ostringstream& os) const
{
    
     os << "Train Square: " << name << std::endl;
     return os.str();

}

