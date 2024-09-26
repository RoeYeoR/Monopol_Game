#pragma once

#include <iostream>
#include "Square.hpp"

class ElectricCompany :public Square {

    private:
       
        float price;

    public:
        ElectricCompany();
        ElectricCompany(std::string name);
        float getPrice();
        void display(std::ostream& os) const override;

};