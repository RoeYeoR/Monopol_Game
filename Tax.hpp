#pragma once

#include <iostream>
#include "Square.hpp"

class Tax :public Square {

    private:
       
        float price;

    public:
       Tax(std::string desc, float price);
       float getPrice();
       void display(std::ostream& os) const override;

};