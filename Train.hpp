#pragma once

#include <iostream>
#include "Square.hpp"

class Train : public Square{


    public:
      Train(std::string name); 
      virtual void display(std::ostream& os) const override;
      static int count;






};