#pragma once

#include "Square.hpp"

using namespace std;


class EdgeSquare : public Square {

    private:
        

    public:
        EdgeSquare( std::string name);
        std::string getDescription();
        virtual void display(std::ostream& os) const override;

};
