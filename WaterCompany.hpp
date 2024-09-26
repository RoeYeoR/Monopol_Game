#pragma once

#include <iostream>
#include "Square.hpp"

class WaterCompany :public Square {


    public:
        WaterCompany();
        WaterCompany(std::string name);
        void display(std::ostream& os) const override;

};