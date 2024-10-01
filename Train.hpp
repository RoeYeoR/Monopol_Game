#pragma once

#include <iostream>
#include <sstream>
#include "Square.hpp"

class Train : public Square{


    public:
      Train(std::string name); 
      virtual void display(std::ostream& os) const override;
      std::string display(std::ostringstream& os) const;
      static int count;






};