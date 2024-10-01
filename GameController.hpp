#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include "GameModel.hpp"
#include "GameView.hpp"

class GameController {
public:
    GameController(GameModel& model, GameView& view);
    void handleEvents(sf::RenderWindow& window,sf::Event event);
    void updateGame();
   

private:
    GameModel& model;
    GameView& view;
    std::string input; 
    void rollDice();
};

#endif 