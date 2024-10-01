#pragma once

#include <iostream>
#include <sstream> 
#include "Square.hpp"

class Chance :public Square {
    private:
    bool wasInUse;

    public:
        Chance();
        Chance(std::string name);
        bool getWasInUse();
        void display(std::ostream& os) const override;
        std::string display(std::ostringstream& os) const override;
};