#pragma once

#include <iostream>
#include "Square.hpp"

class WaterCompany :public Square {

    private:
    
         float price;

    public:
        WaterCompany();
        WaterCompany(std::string name);
        void display(std::ostream& os) const override;

};