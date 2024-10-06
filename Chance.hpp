#pragma once

#include <iostream>
#include <sstream> 
#include "Square.hpp"

class Chance :public Square {
    private:
    int id;
    bool wasInUse;


    public:
        Chance();
        Chance(std::string name);
        Chance(int id,std::string name);
        int getID();
        bool getWasInUse();
        void setWasInUse(bool var);
        void display(std::ostream& os) const override;
        std::string display() const override;
};