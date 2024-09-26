#pragma once

#include <iostream>
#include "Square.hpp"

class Tax :public Square {

    public:
       Tax(std::string desc, float price);
       void display(std::ostream& os) const override;

};