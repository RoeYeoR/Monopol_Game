#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

 class Square {
    private:
        sf::Sprite iconSprite; // Sprite to hold the icon
       
    public:
        std::string name;
        float price;
        Square() {}
        Square(const std::string& name) : name(name) {}
        Square(const std::string& name,float  price) : name(name) , price(price) {}

        std::string getName() {return name;}
        float getPrice() { return price;}
        
        virtual void display(std::ostream& os) const = 0;  // Pure virtual function for polymorphism
        virtual ~Square() = default;       // Virtual destructor for proper cleanup

        void setIcon(const sf::Texture& texture) { iconSprite.setTexture(texture);}
        sf::Sprite getIcon() {return iconSprite;}

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