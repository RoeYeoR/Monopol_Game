#pragma once

#include "Square.hpp"

using namespace std;


enum EdgeSquareType {

    Start,
    VisitNearJail,
    FreeParking,
    GoToJail
   
};



class EdgeSquare : public Square {

    private:
        EdgeSquareType type;

    public:
        EdgeSquare(std::string name,EdgeSquareType esType);
        EdgeSquareType getType();
        virtual void display(std::ostream& os) const override;

};
