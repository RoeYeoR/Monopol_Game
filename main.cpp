#include <SFML/Graphics.hpp>


#include "MonopolManager.hpp"
#include "Board.hpp" 





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

    //Get Font
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Roi\\Desktop\\ComputerScience\\YearB\\SemesterB\\Systems2\\Systems2_FinalProject\\Fonts\\GameFont2.ttf")) 
    { 
        std::cerr << "Error loading font\n"; // Print error message
        return -1; // Handle error
    }
    //Get Textures
    sf::Texture iconTexture;
    if (!iconTexture.loadFromFile("C:\\Users\\Roi\\Desktop\\ComputerScience\\YearB\\SemesterB\\Systems2\\Systems2_FinalProject\\Icons\\Start.png")) { // Update with your icon path
        std::cerr << "Error loading icon texture\n";
        return -1; // Handle error
    }


   
  

   
    std::vector<std::vector<sf::RectangleShape>> grid(boardSize, std::vector<sf::RectangleShape>(boardSize));
    std::vector<std::vector<sf::Text>> textGrid(boardSize, std::vector<sf::Text>(boardSize));
    std::vector<std::vector<sf::Sprite>> iconGrid(boardSize, std::vector<sf::Sprite>(boardSize)); // Grid for icons
    std::vector<std::vector<std::shared_ptr<Square>>>& board = Board::getInstance().getBoard();
    //board initialization
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
           
            sf::RectangleShape square(sf::Vector2f(cellWidth, cellHeight));
            square.setPosition(col * cellWidth, row * cellHeight);
            square.setFillColor(sf::Color::White); // Default color

         if (row == 0 || row == boardSize - 1 || col == 0 || col == boardSize - 1)
         {
            // Assign a different color based on the type of square
            auto squarePtr = board[row][col];  // Get your shared_ptr<Square>
           
            if (dynamic_cast<EdgeSquare*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Green); // Edge squares

                //Get Sprites
                sf::Sprite iconSprite;
                iconSprite.setTexture(iconTexture);

                float iconSize = cellWidth * 0.5f; // Adjust the size of the icon as needed
                iconSprite.setScale(iconSize /iconTexture.getSize().x , iconSize/iconTexture.getSize().y ); // Scale the icon
                
                // Center the icon within the square
                iconSprite.setPosition(
                col * cellWidth + (cellWidth - iconSprite.getGlobalBounds().width) / 2,
                row * cellHeight + (cellHeight - iconSprite.getGlobalBounds().height) / 2);

                 // Store the icon in the icon grid
                    iconGrid[row][col] = iconSprite;

            }
            else if (dynamic_cast<Street*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Yellow); // Streets
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
            }
            else if (dynamic_cast<Tax*>(squarePtr.get())) {
                square.setFillColor(sf::Color::Magenta); // Taxes
                MonopolManager::getInstance().SetIcon(squarePtr,"Tax");
            }

            // Store the square
            grid[row][col] = square;
            iconGrid[row][col] = squarePtr->getIcon();


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

    std::cout << "Starting window loop..." << std::endl;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
                
            // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) 
            // {
            //     // Handle dice roll or other actions
            //    int diceResult = MonopolManager::getInstance().RollDice();

            // }    
        }
        std::cout << "Window loop ended." << std::endl;
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


        // window.draw(shape);
        // window.draw(square);

        window.display();
    }

    return 0;
}


 