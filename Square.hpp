#pragma once

#include <iostream>


 class Square {
   
       
    public:
        std::string name;
        Square() {}
        Square(const std::string& name) : name(name) {}
        virtual void display(std::ostream& os) const = 0;  // Pure virtual function for polymorphism
        virtual ~Square() = default;       // Virtual destructor for proper cleanup

        bool operator==(const Square& other) const
        {
            return name == other.name;
        }

        friend std::ostream& operator<<(std::ostream& os, const Square& square) 
        {
            square.display(os);  // Call the polymorphic display method
            return os;
        }
};