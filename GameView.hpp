#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <SFML/Graphics.hpp>
#include "GameModel.hpp"

class GameView {
public:
    GameView(GameModel& model, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void setInputText(const std::string& input);
    void updatePlayerIcons();
    void promptNumberOfPlayers();
    void initializeBoard(sf::RenderWindow& window);
    std::vector<sf::Sprite>& getPlayerIcons();
    std::vector<sf::Texture>& getPlayerTextures();
    void showMessage(const std::string& message); 
    

private:
    GameModel& model;
    const int boardSize = 11;
    std::vector<std::vector<sf::RectangleShape>> grid;
    std::vector<std::vector<sf::Sprite>> iconGrid;
    sf::Font font;
    sf::Text promptText;
    sf::Text inputText;
    sf::RectangleShape inputBox;
    std::vector<sf::Sprite> playerIcons;
    std::vector<sf::Texture> playerTextures;
    sf::Text messageText; 
    int numberOfPlayers = 0;
};

#endif 
