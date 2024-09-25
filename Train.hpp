#pragma once

#include <iostream>
#include "Square.hpp"

class Train : public Square{

    private:
  
    float price;

    public:
      Train(std::string name); 
      float getPrice();
      virtual void display(std::ostream& os) const override;
      static int count;






};