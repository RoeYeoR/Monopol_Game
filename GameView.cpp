#include "GameView.hpp"

GameView::GameView(GameModel& model, sf::RenderWindow& window) : model(model) {

    if (!font.loadFromFile("Fonts\\GameFont2.ttf")) {
        // Handle error
         std::cerr << "Error: Failed to load font 'GameFont2.ttf'" << std::endl;
    }

    messageText.setFont(font);
    messageText.setCharacterSize(24); 
    messageText.setFillColor(sf::Color::White); 
    messageText.setPosition(50.f, 50.f); 


    promptText.setFont(font);
    promptText.setString("Enter number of players (2-8):");
    promptText.setCharacterSize(24);
    promptText.setFillColor(sf::Color::White);

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::White);
    
    inputBox.setSize(sf::Vector2f(200, 30)); 
    inputBox.setFillColor(sf::Color::Black);
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setOutlineThickness(2);

    for (int i = 0; i < 8; i++)
    {
        sf::Texture playerTexture;
        if(!playerTexture.loadFromFile("Icons\\Player" + std::to_string(i+1) + ".png"))
        {
            std::cerr << "Error: Failed to load texture 'Player" << (i+1) << ".png'" << std::endl;
            //handle error
        }
        playerTextures.push_back(playerTexture);
    }
    

    initializeBoard(window);
   
}

void GameView::initializeBoard(sf::RenderWindow& window)
{
   // Get window size
    sf::Vector2u windowSize = window.getSize();

    grid.resize(boardSize, std::vector<sf::RectangleShape>(boardSize));
    iconGrid.resize(boardSize, std::vector<sf::Sprite>(boardSize));

     // Calculate cell size dynamically based on window dimensions
    const float cellWidth = windowSize.x / static_cast<float>(boardSize);
    const float cellHeight = windowSize.y / static_cast<float>(boardSize);

    if (cellWidth <= 0 || cellHeight <= 0) {
    showMessage("Cell size is zero or negative!");
    // Handle error
    }
        // Draw square logic
        for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
           
            sf::RectangleShape square(sf::Vector2f(cellWidth, cellHeight));
            square.setPosition(col * cellWidth, row * cellHeight);
            square.setFillColor(sf::Color(241, 231, 254)); // Default color

            // Assign a different color based on the type of square
            const std::vector<std::vector<std::shared_ptr<Square>>>& board = model.getBoard();
            auto squarePtr =  board[row][col];

         if (row == 0 || row == boardSize - 1 || col == 0 || col == boardSize - 1)
         {
            if (dynamic_cast<EdgeSquare*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Green); // Edge squares
                MonopolManager::getInstance().CheckEdgeSquareType(squarePtr);
            
            }
            else if (auto street = dynamic_cast<Street*>(squarePtr.get())) {
                sf::Color streetColor;
                switch(street->getColor())
                {
                    case Color::Azure:
                        streetColor = sf::Color(0, 127, 255);
                        break;
                    case Color::Blue:
                        streetColor = sf::Color(40, 67, 135);  
                         break;
                    case Color::Brown:
                        streetColor = sf::Color(130, 94, 92);  
                         break;  
                    case Color::Green:
                        streetColor = sf::Color(195, 255, 104); 
                         break;
                    case Color::Orange:
                        streetColor = sf::Color(251, 192, 147);  
                         break;
                    case Color::Pink:
                        streetColor = sf::Color(227, 61, 148);
                         break;  
                    case Color::Red:
                        streetColor = sf::Color(210, 77, 87);
                         break;  
                    case Color::Yellow:
                        streetColor = sf::Color(254, 241, 96);
                         break; 
                    default:
                        streetColor= sf::Color::White;
                         break;

                }
                square.setFillColor(streetColor); // Streets
            }
            else if (dynamic_cast<Train*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Red); // Train stations
                 MonopolManager::getInstance().SetIcon(squarePtr,"Train");
            }
            else if (dynamic_cast<Chance*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Cyan); // Chance
                MonopolManager::getInstance().SetIcon(squarePtr,"ChanceCard");
            }
            else if (dynamic_cast<CommunityChest*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Blue); // Community Chest
                MonopolManager::getInstance().SetIcon(squarePtr,"TreasureChestCard");
            }
            else if (dynamic_cast<Tax*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Magenta); // Taxes
                MonopolManager::getInstance().SetIcon(squarePtr,"Tax");
            }
              else if (dynamic_cast<ElectricCompany*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Magenta); // Taxes
                MonopolManager::getInstance().SetIcon(squarePtr,"Electric");
            }
             else if (dynamic_cast<WaterCompany*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Magenta); // Taxes
                MonopolManager::getInstance().SetIcon(squarePtr,"Water");
            }

         }
            // Store the square
            grid[row][col] = square;

          sf::Sprite iconSprite = squarePtr->getIcon();
          if (iconSprite.getTexture()) 
          {
            float iconSize = cellWidth * 0.5f; // Adjust the size of the icon as needed
            iconSprite.setScale(iconSize / iconSprite.getTexture()->getSize().x,
                                iconSize / iconSprite.getTexture()->getSize().y);

            // Center the icon within the square
            iconSprite.setPosition(
                col * cellWidth + (cellWidth - iconSprite.getGlobalBounds().width) / 2,
                row * cellHeight + (cellHeight - iconSprite.getGlobalBounds().height) / 2);

            // Store the sprite in the icon grid
            iconGrid[row][col] = iconSprite;
          }
        
        }
    }

}

void GameView::render(sf::RenderWindow& window) {
    window.clear();
   
    for (int i = 0; i < boardSize; i++)
    {
      for (int j = 0; j < boardSize; j++)
        {
            window.draw(grid[i][j]);
            if(iconGrid[i][j].getTexture())
            {
                window.draw(iconGrid[i][j]);
            }            
        }       
    }   
    for (int i = 0; i < model.getPlayers().size(); ++i) {
        // Update and draw each player's icon based on their position
        // Use playerIcons[i].setPosition(...);
        if(playerIcons[i].getTexture())
        {
            window.draw(playerIcons[i]);
        }
    }

    window.draw(promptText);
    window.draw(inputBox);
    window.draw(inputText);
    window.draw(messageText); 
    window.display(); // Display everything in the window
 }

        

void GameView::setInputText(const std::string& input) {
    inputText.setString(input);
}

void GameView::updatePlayerIcons() {

    // // Update player icon positions based on model's player positions
    // for (int i = 0; i < model.getPlayers().size(); i++)
    // {
    //     //playerIcons[i].setPosition(
    // }
    
}

void GameView::promptNumberOfPlayers() {
    // Display prompt
    promptText.setPosition(50, 50); // Set position for prompt
    inputBox.setPosition(50, 100);   // Set position for input box
}

std::vector<sf::Sprite>& GameView::getPlayerIcons()
{
  return playerIcons;
}

std::vector<sf::Texture>& GameView::getPlayerTextures()
{
    return playerTextures;

}

void GameView::showMessage(const std::string& message) {
    messageText.setString(message); 
}



