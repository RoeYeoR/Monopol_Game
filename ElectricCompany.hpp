#pragma once

#include <iostream>
#include "Square.hpp"

class ElectricCompany :public Square {

    public:
        ElectricCompany();
        ElectricCompany(std::string name);
        void display(std::ostream& os) const override;

};