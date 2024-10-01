#include "MonopolManager.hpp"
#include <SFML/Graphics.hpp>




 std::string GLOBAL_START_ICON = "Start";
 std::string GLOBAL_GOTOJAIL_ICON = "GoToJail";
 std::string GLOBAL_VISITING_ICON = "Jail";
 std::string GLOBAL_FREE_PRAKING_ICON = "FreeParking";





MonopolManager::MonopolManager() 
{
    chanceStrings.push_back("Advance to Go (Collect $200)");
    chanceStrings.push_back("Bank pays you dividend of $50");
    chanceStrings.push_back("Go back 3 spaces");
    chanceStrings.push_back("Go directly to Jail do not pass Go, do not collect $200");
    chanceStrings.push_back("Make general repairs on all your property  For each house pay $25  For each hotel $100");
    chanceStrings.push_back("Pay poor tax of $15");
    chanceStrings.push_back("Take a trip to Reading Railroad  If you pass Go collect $200");
    chanceStrings.push_back("Take a walk on the Boardwalk  Advance token to Boardwalk");
    chanceStrings.push_back("You have been elected Chairman of the Board  Pay each player $50");
    chanceStrings.push_back("Your building loan matures  Collect $150");
    chanceStrings.push_back("Get out of Jail Free  This card may be kept until needed or traded");
    chanceStrings.push_back("Advance to Illinois Ave.  If you pass Go, collect $200");
    chanceStrings.push_back("Advance to St. Charles Place  If you pass Go, collect $200");
    chanceStrings.push_back("You are assessed for street repairs  $40 per house, $115 per hotel");
    chanceStrings.push_back("Advance to nearest Utility  If unowned you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown.");
    chanceStrings.push_back("Advance to nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental to which they are otherwise entitled");


    for(int i=0; i <chanceStrings.size(); i++)
    {
        Chance c(chanceStrings[i]);
        gameChanceCards.push_back(c);
    }
                    
 
}

float MonopolManager::StartMoney = 200;

std::vector<std::shared_ptr<Player>>&  MonopolManager::getPlayers()
{
    return players;
}


std::shared_ptr<Player>& MonopolManager::getCurrentPlayer()
 {

    return currentPlayer;
 }
 
void MonopolManager::setCurrentPlayer(std::shared_ptr<Player>& p)
{
    currentPlayer = p;
}

 std::vector<Chance>& MonopolManager::getGameChanceCards()
 {
    return gameChanceCards;
 }

int MonopolManager::RollDice()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    int dice1 = (std::rand() % 6) + 1;
    int dice2 = (std::rand() % 6) + 1;
    return (dice1+dice2);
}

std::shared_ptr<Player>* MonopolManager::CheckStreetOwner(const std::shared_ptr<Square>& square)
{
    // Attempt to dynamic cast the Square to a Street
    Street* street = dynamic_cast<Street*>(square.get());
    if (!street) {
        throw std::runtime_error("The square is not a street.");
    }

    for ( std::shared_ptr<Player>& p : players)
    {
       if(p != currentPlayer)
       {
           for (const Street& st : p->getStreets())
           {
              if (st == *street)
              {
                return &p;
              }  
           }
       }     
    }
    return nullptr;
}

 std::shared_ptr<Player>* MonopolManager::CheckTrainOwner(const std::shared_ptr<Square>& square)
{
    Train* train = dynamic_cast<Train*>(square.get());
    if (!train) {
        throw std::runtime_error("The square is not a train.");
    }
    for( std::shared_ptr<Player>& p : players)
    {
        if( p != currentPlayer)
        {
            for(const Train& tr : p->getTrains())
            {
                if(tr == *train)
                {
                    return &p;
                }

            }
        }
    }
    return nullptr;
}

 std::shared_ptr<Player>* MonopolManager::CheckWaterCompanyOwner(const std::shared_ptr<Square>& square)
{
    for( std::shared_ptr<Player>& p : players)
    {
        if(p != currentPlayer)
        {
            if(p->gethasOwnWaterCompany())
                    return &p;
        }
    }
    return nullptr;

}
 std::shared_ptr<Player>* MonopolManager::CheckElectricCompanyOwner(const std::shared_ptr<Square>& square)
{
    for( std::shared_ptr<Player>& p : players)
    {
        if( p != currentPlayer)
        {
            if(p->gethasOwnElectricCompany())
                    return &p;
        }
    }
    return nullptr;

}

void MonopolManager::CheckTaxPrice(Tax* tax, sf::Text& gameMessage) {
    std::ostringstream messageStream;  // Create a string stream to accumulate the output message

    messageStream << "You need to pay " << tax->getPrice() << " to the bank.\n";
    messageStream << "Current money: " << currentPlayer->getMoney() << "\n";

    if (currentPlayer->getMoney() < tax->getPrice()) {
        messageStream << "You don't have enough money to pay the bank. Deleting your properties...\n";
        if (DeleteAllProperties()) {
            messageStream << currentPlayer->getName() << " went bankrupt and finished the game!...\n";
        }
    }

    // Deduct the tax amount from the player's money
    currentPlayer->setMoney(currentPlayer->getMoney() - tax->getPrice());
    messageStream << "Charging your money...\n";
    messageStream << "Money remaining after charge: " << currentPlayer->getMoney() << "\n";

    // Update the sf::Text object with the accumulated message
    gameMessage.setString(messageStream.str());
}
 void MonopolManager::AddChance()
 {
    if(currentPlayer->AddChance())
    {
        std::cout<<"A chance card was added succesfully!" << std::endl;
    }
    else{
         std::cout<<"couldn't add a chance card..." << std::endl;
    }

 }

 void MonopolManager::AddCommunityChest()
 {


 }

 float MonopolManager::getActuallBillOfSquare(std::shared_ptr<Square>& square,std::shared_ptr<Player>* ownPlayer)
 {
    float price=0;
    if(auto street = dynamic_cast<Street*>(square.get()))
    {
        if(street->getNumOfHouses()>0 && street->getHasHotel() == false)
        {
            price = street->getRentPriceWithHouse() * pow(2,street->getNumOfHouses()-1);
        }
        else if(street->getHasHotel())
        {
           price = street->getRentPriceWithHotel();
        }
        else
        {
            price = street->getRentPrice();
        }
      
    }
    else if(auto train = dynamic_cast<Train*>(square.get()))
    {
        if((*ownPlayer)->getTrains().size()>0)
        {
             switch((*ownPlayer)->getTrains().size())
        {
           case 1:
            price = 50;
            break;

           case 2:
            price =100;
             break;

            case 3:
            price = 150;
             break;

            case 4:
            price =200; 
             break;
        }

        }  
    }

    return price;

 }

 void MonopolManager::BuyStreet(Street* street,sf::Text& gameMessage)
 {
    std::ostringstream messageStream;
    messageStream << "Current money: " << currentPlayer->getMoney() << "\n";
    
    if (currentPlayer->getMoney() < street->getPrice()) {
        messageStream << "You don't have enough money to buy this street...\n";
    } else {
        messageStream << "Do you want to buy this street? 1. Yes, 2. No\n";
        int ans;
        std::cin >> ans;  // You may want to use a more GUI-friendly method to get user input
        
        if (ans == 1) {
            if (currentPlayer->PurchaseStreet(street)) {
                messageStream << "Street: " << street->name << " was purchased successfully\n";
                std::ostringstream playerInfo;
               playerInfo << currentPlayer->displayLong();  // Display player info in a stringstream
                messageStream << playerInfo.str();
            }
        }
    }

    // Update the sf::Text object with the new message
    gameMessage.setString(messageStream.str());
 }

  void MonopolManager::BuyTrain(Train* train,sf::Text& gameMessage)
 {
    std::ostringstream messageStream;  // String stream to collect all the output messages
    messageStream << "Current money: " << currentPlayer->getMoney() << "\n";
    messageStream << "Cost: " << train->getPrice() << "\n";
    
    if (currentPlayer->getMoney() < train->getPrice()) {
        messageStream << "You don't have enough money to buy this train...\n";
    } else {
        messageStream << "Do you want to buy this train? 1. Yes, 2. No\n";
        
        // Instead of std::cin, you should handle user input through SFML (buttons or keyboard events)
        int ans;
        std::cin >> ans;  // You may want to replace this with GUI input handling

        if (ans == 1) {
            if (Train::count >= 4) {
                messageStream << "All 4 trains were already sold!\n";
            } else if (currentPlayer->PurchaseTrain(train)) {
                messageStream << "Train: " << train->name << " was purchased successfully\n";
                
                std::ostringstream playerInfo;
                currentPlayer->displayLong(playerInfo);  // Collect player status info
                messageStream << playerInfo.str();  // Append player info to the message
            }
        }
    }
    
    // Update the sf::Text object with the message
    gameMessage.setString(messageStream.str());
    
 }

  void MonopolManager::BuyWaterCompany(WaterCompany* waterCompany,sf::Text& gameMessage)
 {
     std::ostringstream messageStream;  // String stream to collect all the output messages
    
    messageStream << "Current money: " << currentPlayer->getMoney() << "\n";
    messageStream << "Cost: " << waterCompany->getPrice() << "\n";
    
    if (currentPlayer->getMoney() < waterCompany->getPrice()) {
        messageStream << "You don't have enough money to buy the Water Company...\n";
    } else {
        messageStream << "Do you want to buy the Water Company? 1. Yes, 2. No\n";
        
        // Instead of std::cin, use SFML event handling for GUI input
        int ans;
        std::cin >> ans;  // Replace with GUI-based input in your actual game
        
        if (ans == 1) {
            if (currentPlayer->PurchaseWaterCompany(waterCompany)) {
                messageStream << waterCompany->name << " was purchased successfully\n";
                
                // Append player status information
                std::ostringstream playerInfo;
                currentPlayer->displayLong(playerInfo);
                messageStream << playerInfo.str();
            }
        }
    }
    
    // Update the sf::Text object with the message
    gameMessage.setString(messageStream.str());

 }

  void MonopolManager::BuyElectricCompanyOwner(ElectricCompany* electricCompany,sf::Text& gameMessage)
 {
    std::ostringstream messageStream;  // Create a string stream to collect all output messages

    messageStream << "Current money: " << currentPlayer->getMoney() << "\n";
    messageStream << "Cost: " << electricCompany->getPrice() << "\n";

    if (currentPlayer->getMoney() < electricCompany->getPrice()) {
        messageStream << "You don't have enough money to buy the Electric Company...\n";
    } else {
        messageStream << "Do you want to buy the Electric Company? 1. Yes, 2. No\n";
        
        // Instead of std::cin, handle input through the GUI (replace this later with actual button handling)
        int ans;
        std::cin >> ans;  // Replace with button click logic in the actual game
        
        if (ans == 1) {
            if (currentPlayer->PurchaseElectricCompany(electricCompany)) {
                messageStream << electricCompany->name << " was purchased successfully\n";
                
                // Append player status information
                std::ostringstream playerInfo;
                currentPlayer->displayLong(playerInfo);
                messageStream << playerInfo.str();
            }
        }
    }

    // Update the sf::Text object with the accumulated message
    gameMessage.setString(messageStream.str());
    
 }
 
 void MonopolManager::CheckEdgeSquare(EdgeSquare* edgeSquare, sf::Text& gameMessage) {
    std::ostringstream messageStream;  // Create a string stream to accumulate the output message

    switch(edgeSquare->getType()) {
        case EdgeSquareType::Start:
            GrantPlayerMoney(StartMoney);
            messageStream << "You landed on the START square. You've been granted money!\n";
            break;

        case EdgeSquareType::FreeParking:
            messageStream << "You are on FREE PARKING square, turn finished...\n";
            break;

        case EdgeSquareType::GoToJail:
            messageStream << "You are going to jail!!\n";
            messageStream << "Know your rights.\n";
            GoToJail();
            break;

        case EdgeSquareType::VisitNearJail:
            messageStream << "You are visiting near the jail, nothing to do here...\n";
            break;
    }

    // Update the sf::Text object with the accumulated message
    gameMessage.setString(messageStream.str());
}

void MonopolManager::CheckEdgeSquareType(std::shared_ptr<Square>& square)
{
   if(auto edgeSquare = dynamic_cast<EdgeSquare*>(square.get()))
   {
     switch(edgeSquare->getType())
    {
        case EdgeSquareType::Start:
             SetIcon(square,GLOBAL_START_ICON);   
            break;
        case EdgeSquareType::FreeParking:
            SetIcon(square,GLOBAL_FREE_PRAKING_ICON);   
            break;
        case EdgeSquareType::GoToJail:
           SetIcon(square,GLOBAL_GOTOJAIL_ICON);   
                 break;   
         case EdgeSquareType::VisitNearJail:
           SetIcon(square,GLOBAL_VISITING_ICON);   
                break;            
    }







   }
   
}


void MonopolManager::UpgradeStreet(Street* street, sf::Text& gameMessage) {
    std::ostringstream messageStream;  // Create a string stream to accumulate the output message

    messageStream << "Current number of houses on this street: " << street->getNumOfHouses() << "\n";

    if (street->getNumOfHouses() < 4) {
        int ans1;
        messageStream << "Would you like to upgrade and purchase another house on this street? 1.Yes, 2.No\n";
        
        // Here, instead of cin, we would use a different mechanism to get user input
        // Assuming some function or mechanism to get user input in the GUI
        // Example: ans1 = GetUserInput();  // This is a placeholder for actual input logic
        
        std::cin >> ans1;  // Placeholder for user input mechanism in the console
        
        if (ans1 == 1) {
            currentPlayer->PurchaseHouse(street);
            messageStream << "House purchased on the street!\n";
        }
    } else {
        if (!street->getHasHotel()) {
            int ans2;
            messageStream << "Would you like to upgrade and purchase a hotel on this street? 1.Yes, 2.No\n";
            
            // Assuming some function or mechanism to get user input in the GUI
            // Example: ans2 = GetUserInput();  // This is a placeholder for actual input logic
            
            std::cin >> ans2;  // Placeholder for user input mechanism in the console
            
            if (ans2 == 1) {
                currentPlayer->PurchaseHotel(street);
                messageStream << "Hotel purchased on the street!\n";
            }
        }
    }

    // Update the sf::Text object with the accumulated message
    gameMessage.setString(messageStream.str());
}

 bool MonopolManager::ChargePlayer(std::shared_ptr<Player>& src, std::shared_ptr<Player>& dst, float amount, sf::Text& gameMessage) {
    std::ostringstream messageStream;  // Create a string stream to accumulate the output message
    bool isValidTransfer = true;

    messageStream << "Transfer: " << amount << "₪ From " << src->getName() << " To " << dst->getName() << "\n";
    messageStream << "Charging ...\n";

    if (src->getMoney() < amount) {
        src->setIsBankrupt(true);
        TransferAllProperties(src, dst);
        messageStream << src->getName() << " is bankrupt! All properties transferred."<<std::endl;
        isValidTransfer = false;
    } else {
        src->changeMoney(-amount);
        dst->changeMoney(amount);
        messageStream << "Transfer completed successfully." <<std::endl;
    }

    // Update the sf::Text object with the accumulated message
    gameMessage.setString(messageStream.str());

    return isValidTransfer;
}

 void MonopolManager::TransferAllProperties(std::shared_ptr<Player>& src,std::shared_ptr<Player>& dst)
 {
    if(src->getStreets().size() > 0)
    {
        for (int i = 0; i < src->getStreets().size(); i++)
        {
           dst->getStreets().push_back(src->getStreets()[i]);
        }
        
        src->getStreets().clear();
    }
    if(src->getTrains().size() > 0)
    {
        for (int i = 0; i < src->getTrains().size(); i++)
        {
           dst->getTrains().push_back(src->getTrains()[i]);
        }  

        src->getTrains().clear();
    }
    if(src->gethasOwnWaterCompany())
    {
        src->setHasOwnWaterCompany(false);
        dst->setHasOwnWaterCompany(true);
    }

     if(src->gethasOwnElectricCompany())
    {
        src->setHasOwnElectricCompany(false);
        dst->setHasOwnElectricCompany(true);
    }

    if(src->getChanceCards().size() > 0)
    {
        for (int i = 0; i < src->getChanceCards().size(); i++)
        {
           dst->getChanceCards().push_back(src->getChanceCards()[i]);
        }
          
    }

    dst->changeMoney(src->getMoney());
    src->setMoney(0);
 }

 bool MonopolManager::DeleteAllProperties()
 {
    currentPlayer->getStreets().clear();
    currentPlayer->getTrains().clear();
    currentPlayer->getChanceCards().clear();
    currentPlayer->setHasOwnElectricCompany(false);
    currentPlayer->setHasOwnWaterCompany(false);
    currentPlayer->setMoney(0);
    return true;
 }

 void MonopolManager::GrantPlayerMoney(float sum)
 {
    currentPlayer->changeMoney(sum);
 }

 void MonopolManager::GoToJail()
 {
    currentPlayer->setIsInJail(true);
    Point2D jailSquare(0,10);
    currentPlayer->GoToSquare(jailSquare);
 }

 std::shared_ptr<Player>* MonopolManager::CheckIsWinner()
 {
    if(currentPlayer->getMoney() >= 4000)
    {
        return &currentPlayer;
    }
    for (int i = 0; i < players.size(); i++)
    {
        if((areAllRestPlayersHaveBankRupt(players[i]) && 
        !players[i]->getIsBankrupt()) )
        {
            return &players[i];  
        }
    }
    return nullptr;
 }

 bool MonopolManager::areAllRestPlayersHaveBankRupt(std::shared_ptr<Player>& p)
 {
    for (int i = 0; i < players.size(); i++)
    {
       if(players[i] == p)
       {
         continue;
       }
       else
       {
          if(!players[i]->getIsBankrupt())  
          {
            return false;
          }
       }
    }
    return true;
 }

  void MonopolManager::SetIcon(std::shared_ptr<Square>& square, const std::string& iconName) {
        // Check if texture is already loaded
        if (textures.find(iconName) == textures.end()) {
            sf::Texture iconTexture;
            if (!iconTexture.loadFromFile("Icons\\" + iconName + ".png")) {
                std::cerr << "Error loading icon texture: " << iconName << "\n";
                return; // Handle error
            }
            textures[iconName] = iconTexture; // Store the texture
        }

        // Set the texture for the square
        square->setIcon(textures[iconName]);
    }