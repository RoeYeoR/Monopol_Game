#pragma once

#include <iostream>
#include <sstream>
#include "Square.hpp"

class ElectricCompany :public Square {

    public:
        ElectricCompany();
        ElectricCompany(std::string name);
        void display(std::ostream& os) const override;
        std::string display(std::ostringstream& os) const override;
};