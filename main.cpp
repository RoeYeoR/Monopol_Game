#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "MonopolManager.hpp"
#include "Board.hpp"
#include "Player.hpp"  
#include "EdgeSquare.hpp" 
#include "InputManager.hpp"


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
sf::Music music;

// Load music from a file (WAV, OGG, or FLAC)
if (!music.openFromFile("Audio\\GameMusic2.ogg"))
{
    std::cerr << "Error loading music file\n";
    return -1;
}

// Play the music
music.play();

// Set music properties (optional)
music.setLoop(true); // Set the music to loop


//Get Font
sf::Font font;
if (!font.loadFromFile("Fonts\\GameFont3.ttf")) 
{ 
std::cerr << "Error loading font\n"; // Print error message
return -1; // Handle error
}

//Get Font
sf::Font font3;
if (!font3.loadFromFile("Fonts\\GameFont3.ttf")) 
{ 
std::cerr << "Error loading font\n"; // Print error message
return -1; // Handle error
}




// Flag to check if the number of players is entered
bool isNumPlayersEntered = false;
int numPlayers = 0;
int maxNumOfPlayers = 8;
// Placeholder for player icons
std::vector<sf::Sprite> playerIcons;
std::vector<sf::Texture> playerTextures;

std::vector<std::shared_ptr<Player>> players;
int currentPlayerIndex = 0;
bool hasDoneTurn = false;
bool hasPressedOnStatusButton = false;



// Welcome text
sf::Text WelcomeText;
WelcomeText.setFont(font);
WelcomeText.setCharacterSize(50);
WelcomeText.setFillColor(sf::Color::Yellow);
WelcomeText.setOutlineThickness(1);
WelcomeText.setString("Welcome To Monopl Game");


sf::FloatRect textBoundsWelcome = WelcomeText.getLocalBounds();
WelcomeText.setOrigin(textBoundsWelcome.width / 2, textBoundsWelcome.height / 2); // Center the origin
WelcomeText.setPosition(windowSize.x / 2, windowSize.y / 2 - 350); // Position it in the center of the window


// Instruction text
sf::Text InstructionText;
InstructionText.setFont(font);
InstructionText.setCharacterSize(24);
InstructionText.setFillColor(sf::Color::Black);
InstructionText.setString("Enter number of players (2-8):");


sf::FloatRect textBoundsInstruction = InstructionText.getLocalBounds();
InstructionText.setOrigin(textBoundsInstruction.width / 2 , textBoundsInstruction.height / 2); // Center the origin
InstructionText.setPosition(windowSize.x / 2, windowSize.y / 2 -50); // Position it in the center of the window


// Instruction Space text
sf::Text InstructionSpaceText;
InstructionSpaceText.setFont(font);
InstructionSpaceText.setCharacterSize(24);
InstructionSpaceText.setFillColor(sf::Color::Black);
InstructionSpaceText.setString("PRESS SPACE TO CHANGE TURN TO NEXT PLAYER");


sf::FloatRect textBoundsInstructionSpace = InstructionSpaceText.getLocalBounds();
InstructionSpaceText.setOrigin(textBoundsInstructionSpace.width / 2, textBoundsInstructionSpace.height / 2); // Center the origin
InstructionSpaceText.setPosition(windowSize.x / 2, windowSize.y / 2 + 350); 


// GameMessage text
sf::Text GameMessageText;
GameMessageText.setFont(font);
GameMessageText.setCharacterSize(24);
GameMessageText.setFillColor(sf::Color::Black);
GameMessageText.setString("Game Message ...");


sf::FloatRect textBoundsGameMessageText = GameMessageText.getLocalBounds();
GameMessageText.setOrigin(textBoundsGameMessageText.width / 2, textBoundsGameMessageText.height / 2); // Center the origin
GameMessageText.setPosition(windowSize.x / 2, windowSize.y / 2 + 200); 

// GameMessage2 text
sf::Text GameMessage2Text;
GameMessage2Text.setFont(font);
GameMessage2Text.setCharacterSize(24);
GameMessage2Text.setFillColor(sf::Color::Black);
GameMessage2Text.setString("Game Message 2 ...");


sf::FloatRect textBoundsGameMessage2Text = GameMessage2Text.getLocalBounds();
GameMessage2Text.setOrigin(textBoundsGameMessage2Text.width / 2, textBoundsGameMessage2Text.height / 2); // Center the origin
GameMessage2Text.setPosition(windowSize.x / 2, windowSize.y / 2 + 300); 



// Status text
sf::Text StatusText;
StatusText.setFont(font);
StatusText.setCharacterSize(24);
StatusText.setFillColor(sf::Color::Black);
//StatusText.setString("Status...");


sf::FloatRect textBoundsStatus = StatusText.getLocalBounds();
StatusText.setOrigin(textBoundsStatus.width / 2 , textBoundsStatus.height / 2 ); // Center the origin
StatusText.setPosition(windowSize.x / 2, windowSize.y / 2 - 200); // Position it in the center of the window


// Status text
sf::Text StatusPlayerTurnText;
StatusPlayerTurnText.setFont(font);
StatusPlayerTurnText.setCharacterSize(35);
StatusPlayerTurnText.setFillColor(sf::Color::Black);
StatusPlayerTurnText.setOutlineThickness(0.5f);
StatusPlayerTurnText.setString("Player 1's Turn");


sf::FloatRect textBoundsStatusPlayerTurn = StatusPlayerTurnText.getLocalBounds();
StatusPlayerTurnText.setOrigin(textBoundsStatusPlayerTurn.width / 2, textBoundsStatusPlayerTurn.height / 2); // Center the origin
StatusPlayerTurnText.setPosition(windowSize.x / 2, windowSize.y / 2 - 300); // Position it in the center of the window


// Text for user input
sf::Text playerInputText;
playerInputText.setFont(font);
playerInputText.setCharacterSize(24);
playerInputText.setFillColor(sf::Color::Black);
playerInputText.setPosition(windowSize.x / 2 - 50, windowSize.y / 2);
std::string input = "";

//Yes and No buttons
sf::RectangleShape yesButton(sf::Vector2f(100, 50));
sf::RectangleShape noButton(sf::Vector2f(100, 50));

sf::Text yesText, noText;
yesText.setFont(font); // Assuming you have a font loaded
yesText.setString("Yes");
yesText.setCharacterSize(24);
yesText.setFillColor(sf::Color::Black);

noText.setFont(font);  // Same font for "No"
noText.setString("No");
noText.setCharacterSize(24);
noText.setFillColor(sf::Color::Black);

// Set button positions
yesButton.setPosition(300, 400); // Adjust these values as needed
noButton.setPosition(500, 400);

yesText.setPosition(320, 410);  // Adjust positions to center the text inside the buttons
noText.setPosition(520, 410);

yesButton.setFillColor(sf::Color::Green);
noButton.setFillColor(sf::Color::Red);




for (int i = 0; i < maxNumOfPlayers; i++)
{
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Icons\\Player" + std::to_string(i+1) + ".png")) 
    {
        std::cerr << "Error loading player texture " << "\n";
        return -1; // Handle error
    }
    playerTextures.push_back(playerTexture);
}

// Create two buttons: Player Status and Roll the Dice
sf::RectangleShape playerStatusButton(sf::Vector2f(200.f, 50.f));
playerStatusButton.setFillColor(sf::Color(100, 100, 250)); // Blue color
playerStatusButton.setPosition(windowSize.x / 2 - 100, windowSize.y / 2 + 30); // Position in the center

sf::Text playerStatusText;
playerStatusText.setFont(font);
playerStatusText.setString("Status");
playerStatusText.setCharacterSize(24);
playerStatusText.setFillColor(sf::Color::White);
playerStatusText.setPosition(playerStatusButton.getPosition().x + 20, playerStatusButton.getPosition().y + 10); // Center the text

sf::RectangleShape rollDiceButton(sf::Vector2f(200.f, 50.f));
rollDiceButton.setFillColor(sf::Color(100, 250, 100)); // Green color
rollDiceButton.setPosition(windowSize.x / 2 - 100, windowSize.y / 2 + 100); // Below Player Status button

sf::Text rollDiceText;
rollDiceText.setFont(font);
rollDiceText.setString("Roll the Dice");
rollDiceText.setCharacterSize(24);
rollDiceText.setFillColor(sf::Color::White);
rollDiceText.setPosition(rollDiceButton.getPosition().x + 20, rollDiceButton.getPosition().y + 10);



std::vector<std::vector<sf::RectangleShape>> grid(boardSize, std::vector<sf::RectangleShape>(boardSize));
std::vector<std::vector<sf::Text>> textGrid(boardSize, std::vector<sf::Text>(boardSize));
std::vector<std::vector<sf::Sprite>> iconGrid(boardSize, std::vector<sf::Sprite>(boardSize)); // Grid for icons
std::vector<std::vector<std::shared_ptr<Square>>>& board = Board::getInstance().getBoard();
//board initialization
for (int row = 0; row < boardSize; ++row) {
for (int col = 0; col < boardSize; ++col) {
    
    sf::RectangleShape square(sf::Vector2f(cellWidth, cellHeight));
    square.setPosition(col * cellWidth, row * cellHeight);
    square.setFillColor(sf::Color(241, 231, 254)); // Default color

    if (row == 0 || row == boardSize - 1 || col == 0 || col == boardSize - 1)
    {
    // Assign a different color based on the type of square
    auto squarePtr = board[row][col];  
    
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
    text.setCharacterSize(15); // Adjust size as needed
    text.setOutlineThickness(0.2f);
    text.setFillColor(sf::Color::Black); // Text color

    // Example text, you can set it to a property of your Square or any other identifier
    text.setString(squarePtr->getName()); 
    text.setPosition(
        col * cellWidth + (cellWidth - text.getGlobalBounds().width) / 2, // Center horizontally
        row * cellHeight + (cellHeight - text.getGlobalBounds().height) / 2);  // Center vertically

    
    // Store the text in the text grid
    textGrid[row][col] = text;
    }
    else
    {
    // Store Default square
    grid[row][col] = square;
    }
}
}


while (window.isOpen())
{
sf::Event event;
while (window.pollEvent(event))
{
    if (event.type == sf::Event::Closed)
    {
        window.close();
    }

        // Handle text input for number of players
    if (!isNumPlayersEntered && event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode >= '0' && event.text.unicode <= '9')
        {
            input += static_cast<char>(event.text.unicode);
            playerInputText.setString(input);
        }
        else if (event.text.unicode == '\b' && !input.empty())
         { // Handle backspace
            input.pop_back();
            playerInputText.setString(input);
        }
        else if (event.text.unicode == 13 && !input.empty())
        { // Enter key pressed
            numPlayers = std::stoi(input);
            if (numPlayers >= 2 && numPlayers <= 8) 
            {
                isNumPlayersEntered = true;

            // Constants for the starting square position
            const float startX = 10 * cellWidth;
            const float startY = 10 * cellHeight;

            // Calculate dimensions based on the number of players
            const float spacingX = cellWidth / (numPlayers <= 4 ? 2 : 4);  // Adjust spacing based on players
            const float spacingY = cellHeight / (numPlayers <= 4 ? 2 : 4); // Adjust spacing based on players

            const float scaleFactor = (numPlayers <= 4) ? 0.5f : 0.3f; 

            // Generate player icons
            for (int i = 0; i < numPlayers; ++i)
            {
                
                std::shared_ptr<Player> p = std::make_shared<Player>("Player " + std::to_string(i + 1));
                players.push_back(p);


               sf::Sprite playerSprite;
               playerSprite.setTexture(playerTextures[i]);


                playerSprite.setScale(scaleFactor, scaleFactor);
                
                // Calculate positions to spread the icons in the starting square
                float offsetX = (i % 2 == 0) ? -spacingX : spacingX; 
                float offsetY = (i < 2) ? -spacingY : spacingY;

                // Set the position of the player icon based on offsets
                playerSprite.setPosition(startX + offsetX, startY + offsetY);

                // Add player icon to vector
                playerIcons.push_back(playerSprite);
              
            }
                MonopolManager::getInstance().setCurrentPlayer(players[currentPlayerIndex]);
                MonopolManager::getInstance().setPlayers(players);
                InstructionText.setString("Players have been placed on the start square.");
            } 
            else 
            {
                    input = ""; // Reset invalid input
                    playerInputText.setString(input);
                    InstructionText.setString("Please enter a valid number (2-8):");
            }

        }
    }

        // Detect clicks on the buttons
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          
                if (yesButton.getGlobalBounds().contains(mousePos.x,mousePos.y))  // Yes button clicked
                {
                       
                }
                else if (noButton.getGlobalBounds().contains(mousePos.x,mousePos.y))  // No button clicked
                {
                    
                    
                }

            // Check if Player Status button is clicked
            if (playerStatusButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
            {
                hasPressedOnStatusButton = !hasPressedOnStatusButton;
                if(hasPressedOnStatusButton)
                {
                     std::string statusStr =  players[currentPlayerIndex]->displayLong();
                     
                     StatusText.setString(statusStr);
                    sf::FloatRect textBoundsStatus = StatusText.getLocalBounds();
                    StatusText.setOrigin(textBoundsStatus.width / 2 , textBoundsStatus.height / 2 ); // Center the origin
                    StatusText.setPosition(windowSize.x / 2, windowSize.y / 2 -200 ); // Position it in the center of the window
                    playerStatusText.setString("Hide Status");
                    InstructionText.setString("");
                    WelcomeText.setString("");
                    StatusPlayerTurnText.setString("");
                }
                else
                {
                    WelcomeText.setString("Welcome To Monopl Game");
                    StatusPlayerTurnText.setString("Player " +std::to_string(currentPlayerIndex+1) +"'s Turn");
                    StatusText.setString("");
                    playerStatusText.setString("Status");
                }            
            }

            // Check if Roll the Dice button is clicked
            if (rollDiceButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && !hasDoneTurn) 
            {
                // Roll the dice
                int diceResult = MonopolManager::getInstance().RollDice();
                
                
                InstructionText.setString("You rolled  " + std::to_string(diceResult) + "!");
                sf::FloatRect textBoundsInstruction = InstructionText.getLocalBounds();
                InstructionText.setOrigin(textBoundsInstruction.width / 2 , textBoundsInstruction.height / 2); // Center the origin
                InstructionText.setPosition(windowSize.x / 2, windowSize.y / 2 ); // Position it in the center of the window

                players[currentPlayerIndex]->MoveOnBoard(diceResult);
                Point2D& currentPos =  players[currentPlayerIndex]->getCurrentPosition();
                std::ostringstream newPosStr; 
                newPosStr << "Position On Board: " << currentPos.to_string() << "\n" << "Current Square: " <<board[currentPos.getX()][currentPos.getY()]->display();
                StatusText.setOrigin(textBoundsStatus.width / 2 +250 , textBoundsStatus.height / 2 );
                StatusText.setString(newPosStr.str());
                
                std::shared_ptr<Player>* p = Board::getInstance().checkSquareOwnerShip(board[currentPos.getX()][currentPos.getY()]);
                std::ostringstream os;   

            if (currentPos.getX() >= 0 && currentPos.getX() < 11 && currentPos.getY() >= 0 && currentPos.getY() < 11)  
            {
                if( p == nullptr)
                {      
                         Board::getInstance().offerPlayerOptions(board[currentPos.getX()][currentPos.getY()],GameMessageText);
                }
                
                else if( *p != players[currentPlayerIndex])
               {
                    std::shared_ptr<Square>& currentSquare =  board[currentPos.getX()][currentPos.getY()];
        
                    os << currentSquare->display();
                    os <<"This Sqaure is owned by " << (*p)->getName();
                    float calculatedPrice = MonopolManager::getInstance().getActuallBillOfSquare(currentSquare,p);  
                
                    if(!MonopolManager::getInstance().ChargePlayer(players[currentPlayerIndex],*p,calculatedPrice,GameMessageText))
                    {
                        os<< players[currentPlayerIndex]->getName() <<" went bankrupt ..." <<std::endl << "All it's properties were passed to " 
                        << (*p)->getName() <<std::endl;
                    }
                    else
                    {
                        os << "Transfer of " << currentSquare->getPrice() <<"₪ was done Successfully!"<<std::endl;
                    }
                }
                else
                {
                    Board::getInstance().offerPlayerUpgrades(board[currentPos.getX()][currentPos.getY()],GameMessageText);

                }
                hasDoneTurn = true;

                if(os.str().length()>0)
                {
                    GameMessage2Text.setString(os.str());
                }

             }
            }

            else
            {
                if(hasDoneTurn)
                {
                     InstructionText.setString("You already did your Turn. Press Space to move on to the next Player !");
                     InstructionText.setOrigin(textBoundsInstruction.width / 2 + 200 , textBoundsInstruction.height / 2); // Center the origin
                }
               
            }
                
        }
               
    }


    if (event.type == sf::Event::KeyPressed)
    {
        // Check if the pressed key is the spacebar
        if (event.key.code == sf::Keyboard::Space) {
            currentPlayerIndex ++;
            currentPlayerIndex = currentPlayerIndex % numPlayers;
            MonopolManager::getInstance().setCurrentPlayer(players[currentPlayerIndex]);
            StatusPlayerTurnText.setString("Player " +std::to_string(currentPlayerIndex+1) +"'s Turn");
            //StatusText.setString("Status ...");
            InstructionText.setString("");
            GameMessageText.setString("");
            GameMessage2Text.setString("");
            StatusText.setString("");
            hasDoneTurn = false;
        }
        
    }



    // Handle input only when waiting for user input
        if (InputManager::getInstance().isWaitingForInput()) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    InputManager::getInstance().setPlayerChoice(1);  // Player chose "Yes"
                    InputManager::getInstance().setWaitingForInput(false);
                } else if (event.key.code == sf::Keyboard::Num2) {
                    InputManager::getInstance().setPlayerChoice(2);  // Player chose "No"
                    InputManager::getInstance().setWaitingForInput(false);
                }
            }
        }

}

switch (InputManager::getInstance().getCurrentState()) {
    case InputState::None:
        // Logic for None state
        break;

    case InputState::BuyStreet:
        // Logic for BuyStreet state
        if (InputManager::getInstance().getPlayerChoice() == 1)
        {
            
            GameMessageText.setString("You chose to buy this street !:)");
             GameMessageText.setOrigin(textBoundsGameMessageText.width / 2 + 200, textBoundsGameMessageText.height / 2);
            Point2D& currentPos= players[currentPlayerIndex]->getCurrentPosition();
            auto street = dynamic_cast<Street*>(board[currentPos.getX()][currentPos.getY()].get());
             if (players[currentPlayerIndex]->PurchaseStreet(street)) {
                 std::ostringstream messageStream;                
                messageStream << "Street: " << street->name << " was purchased successfully!\n";
                GameMessage2Text.setString(messageStream.str());
                GameMessage2Text.setOrigin(textBoundsGameMessage2Text.width / 2 + 200, textBoundsGameMessage2Text.height / 2);
                
            }

              InputManager::getInstance().reset();

        }

        if (InputManager::getInstance().getPlayerChoice() == 2)
        {
            GameMessageText.setString("");
            GameMessage2Text.setString("You chose not to buy this Street... go on to the next player !");
            InputManager::getInstance().reset();


        }
        break;


    case InputState::BuyTrain:
        // Logic for BuyTrain state
         if (InputManager::getInstance().getPlayerChoice() == 1)
        {
            
            GameMessageText.setString("You chose to buy this train !:)");
            GameMessageText.setOrigin(textBoundsGameMessageText.width / 2 + 200, textBoundsGameMessageText.height / 2);
            Point2D& currentPos= players[currentPlayerIndex]->getCurrentPosition();
            auto train = dynamic_cast<Train*>(board[currentPos.getX()][currentPos.getY()].get());
            if (players[currentPlayerIndex]->PurchaseTrain(train)) {
                 std::ostringstream messageStream;                
                messageStream << "Train: " << train->name << " was purchased successfully!\n";
                GameMessage2Text.setString(messageStream.str());
                
            }

              InputManager::getInstance().reset();

        }

        if (InputManager::getInstance().getPlayerChoice() == 2)
        {
            GameMessageText.setString("");
            GameMessage2Text.setString("You chose not to buy this Train... go on to the next player !");
            InputManager::getInstance().reset();


        }
        break;

    case InputState::BuyWaterCompany:
        // Logic for BuyWaterCompany state
           if (InputManager::getInstance().getPlayerChoice() == 1)
        {
            
            GameMessageText.setString("You chose to buy the water company !:)");
            Point2D& currentPos= players[currentPlayerIndex]->getCurrentPosition();
            auto waterCompany = dynamic_cast<WaterCompany*>(board[currentPos.getX()][currentPos.getY()].get());
            if (players[currentPlayerIndex]->PurchaseWaterCompany(waterCompany)) {
                std::ostringstream messageStream;                
                messageStream <<  waterCompany->name << " was purchased successfully!\n";
                GameMessage2Text.setString(messageStream.str());
                GameMessage2Text.setOrigin(textBoundsGameMessage2Text.width / 2 + 200, textBoundsGameMessage2Text.height / 2);
                
            }

              InputManager::getInstance().reset();

        }

        if (InputManager::getInstance().getPlayerChoice() == 2)
        {
            GameMessageText.setString("");
            GameMessage2Text.setString("You chose not to buy the water company... go on to the next player !");
            InputManager::getInstance().reset();


        }
        break;

    case InputState::BuyElectricCompany:
        // Logic for BuyElectricCompany state
             if (InputManager::getInstance().getPlayerChoice() == 1)
        {
            
            GameMessageText.setString("You chose to buy the electric company !:)");
            Point2D& currentPos= players[currentPlayerIndex]->getCurrentPosition();
            auto electricCompany = dynamic_cast<ElectricCompany*>(board[currentPos.getX()][currentPos.getY()].get());
            if (players[currentPlayerIndex]->PurchaseElectricCompany(electricCompany)) {
                std::ostringstream messageStream;                
                messageStream <<  electricCompany->name << " was purchased successfully!\n";
                GameMessage2Text.setString(messageStream.str());
                
            }

              InputManager::getInstance().reset();

        }

        if (InputManager::getInstance().getPlayerChoice() == 2)
        {
            GameMessageText.setString("");
            GameMessage2Text.setString("You chose not to buy the electric company... go on to the next player !");
            InputManager::getInstance().reset();


        }
        break;


    case InputState::UpgradeStreet:
    // Logic for HandleChance state
     if (InputManager::getInstance().getPlayerChoice() == 1)
        {
            
            GameMessageText.setString("You chose to upgrade this street !:)");
            Point2D& currentPos= players[currentPlayerIndex]->getCurrentPosition();
            auto street = dynamic_cast<Street*>(board[currentPos.getX()][currentPos.getY()].get());
            bool isValid = MonopolManager::getInstance().CheckAddingHouseValidabilty(street);
             if(isValid)
             {
                if (players[currentPlayerIndex]->PurchaseHouse(street)) 
                {
                std::ostringstream messageStream;                
                messageStream << "Street: " << street->name << " was upgraded successfully!\n";
                GameMessage2Text.setString(messageStream.str());
                
                }

             }
             else{
                GameMessage2Text.setString("You still can not buy an house on this street \n  You need to buy all streets on the same color before that action ... ");

             }
             
              InputManager::getInstance().reset();

        }

        if (InputManager::getInstance().getPlayerChoice() == 2)
        {
            GameMessageText.setString("");
            GameMessage2Text.setString("You chose not to upgrade this Street... go on to the next player !");
            InputManager::getInstance().reset();


        }

    break;

    case InputState::HandleChance:
        // Logic for HandleChance state
        break;

    case InputState::HandleCommunityChest:
        // Logic for HandleCommunityChest state
        break;

    case InputState::EdgeSquare:
        // Logic for EdgeSquare state
        break;

    // Add more cases for other InputStates as needed

    default:
        // Handle any unexpected states
        break;
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

// Draw the Welcome text
window.draw(WelcomeText);
window.draw(InstructionText);
window.draw(StatusText);
window.draw(InstructionSpaceText);
window.draw(StatusPlayerTurnText);
window.draw(GameMessageText); 
window.draw(GameMessage2Text);

if (!isNumPlayersEntered) {
window.draw(playerInputText);
}

// Draw player icons if the number of players is entered
if (isNumPlayersEntered)
{

window.draw(playerStatusButton);
window.draw(playerStatusText);
window.draw(rollDiceButton);
window.draw(rollDiceText);

// Draw the player icons after placement
for (sf::Sprite& icon : playerIcons)
{
    window.draw(icon);
}

}

window.display();
}

return 0;
}


