#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MonopolManager.hpp"
#include "Board.hpp" 
#include "EdgeSquare.hpp" 


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "MonopolGame");

     // Get window size
    sf::Vector2u windowSize = window.getSize();

     const int boardSize = 11;

     // Calculate cell size dynamically based on window dimensions
    const float cellWidth = windowSize.x / static_cast<float>(boardSize);
    const float cellHeight = windowSize.y / static_cast<float>(boardSize);

    if (cellWidth <= 0 || cellHeight <= 0) {
    std::cerr << "Cell size is zero or negative!" << std::endl;
    return -1; // Handle error
    }

    //  // Create a music object
    // sf::Music music;

    // // Load music from a file (WAV, OGG, or FLAC)
    // if (!music.openFromFile("C:\\Users\\Roi\\Desktop\\ComputerScience\\YearB\\SemesterB\\Systems2\\Systems2_FinalProject\\Audio\\GameMusic.ogg"))
    // {
    //     std::cerr << "Error loading music file\n";
    //     return -1;
    // }

    // // Play the music
    // music.play();

    // // Set music properties (optional)
    // music.setLoop(true); // Set the music to loop


    //Get Font
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Roi\\Desktop\\ComputerScience\\YearB\\SemesterB\\Systems2\\Systems2_FinalProject\\Fonts\\GameFont2.ttf")) 
    { 
        std::cerr << "Error loading font\n"; // Print error message
        return -1; // Handle error
    }
    // //Get Textures
    // sf::Texture iconTexture;
    // if (!iconTexture.loadFromFile("C:\\Users\\Roi\\Desktop\\ComputerScience\\YearB\\SemesterB\\Systems2\\Systems2_FinalProject\\Icons\\Start.png")) { // Update with your icon path
    //     std::cerr << "Error loading icon texture\n";
    //     return -1; // Handle error
    // }


       // Instruction text
    sf::Text instructionText;
    instructionText.setFont(font);
    instructionText.setCharacterSize(24);
    instructionText.setFillColor(sf::Color::Yellow);
    instructionText.setString("Welcome to Monopoly! Press SPACE to roll the dice.");
    
   
    sf::FloatRect textBounds = instructionText.getLocalBounds();
    instructionText.setOrigin(textBounds.width / 2, textBounds.height / 2); // Center the origin
    instructionText.setPosition(windowSize.x / 2, windowSize.y / 2); // Position it in the center of the window

   
    std::vector<std::vector<sf::RectangleShape>> grid(boardSize, std::vector<sf::RectangleShape>(boardSize));
    std::vector<std::vector<sf::Text>> textGrid(boardSize, std::vector<sf::Text>(boardSize));
    std::vector<std::vector<sf::Sprite>> iconGrid(boardSize, std::vector<sf::Sprite>(boardSize)); // Grid for icons
    std::vector<std::vector<std::shared_ptr<Square>>>& board = Board::getInstance().getBoard();
    //board initialization
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
           
            sf::RectangleShape square(sf::Vector2f(cellWidth, cellHeight));
            square.setPosition(col * cellWidth, row * cellHeight);
            square.setFillColor(sf::Color(200, 220, 235)); // Default color

         if (row == 0 || row == boardSize - 1 || col == 0 || col == boardSize - 1)
         {
            // Assign a different color based on the type of square
            auto squarePtr = board[row][col];  // Get your shared_ptr<Square>
           
            if (dynamic_cast<EdgeSquare*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Green); // Edge squares
                MonopolManager::getInstance().CheckEdgeSquareType(squarePtr);
            
                 
            }
            else if (auto street = dynamic_cast<Street*>(squarePtr.get())) {
                sf::Color streetColor = sf::Color::White;
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


            // Store the square
            grid[row][col] = square;

          sf::Sprite iconSprite = squarePtr->getIcon();
          if (iconSprite.getTexture()) {
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

            // Create and set up the text
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(10); // Adjust size as needed
            text.setFillColor(sf::Color::Black); // Text color

            // Example text, you can set it to a property of your Square or any other identifier
            text.setString(squarePtr->getName()); 
            text.setPosition(
                col * cellWidth + (cellWidth - text.getGlobalBounds().width) / 2, // Center horizontally
                row * cellHeight + (cellHeight - text.getGlobalBounds().height) / 2);  // Center vertically
 
            
            // Store the text in the text grid
            textGrid[row][col] = text;
          }
        }
    }


    // sf::CircleShape shape(30.f);
    // shape.setFillColor(sf::Color::Green);
    // shape.setPosition(20.f,20.f);

    // sf::RectangleShape square(sf::Vector2f(20.f,20.f));
    // square.setPosition(50.f,150.f);
    // square.setFillColor(sf::Color::White);

   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
                
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) 
            {
                // Handle dice roll or other actions
                int diceResult = MonopolManager::getInstance().RollDice();
                // Update the instruction text based on the action
                instructionText.setString("You rolled a " + std::to_string(diceResult) + "!");
            }
        }
       
        window.clear();

          // Draw all the grid squares
        for (int row = 0; row < boardSize; ++row) 
        {
            for (int col = 0; col < boardSize; ++col) 
            {
            // // Check if the square is initialized (you can add your specific condition here)
            // auto squarePtr = board[row][col]; // Get the square pointer
            // if (squarePtr) 
                window.draw(grid[row][col]); // Draw the square
                window.draw(textGrid[row][col]); // Draw the text

                 // Draw the icon if it exists
                if (iconGrid[row][col].getTexture()) { // Check if the icon is initialized
                    window.draw(iconGrid[row][col]); // Draw the icon
                }
               
           }
        }


        // Draw the instruction text
        window.draw(instructionText);

        window.display();
    }

    return 0;
}


 