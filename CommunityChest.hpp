#pragma once

#include <iostream>
#include "Square.hpp"

class CommunityChest :public Square {

    private:
      bool wasInUse;

    public:
        CommunityChest();
        CommunityChest(std::string name);
        void display(std::ostream& os) const override;

};