#include "MonopolManager.hpp"


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
        chanceCards.push_back(c);
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

 std::vector<Chance>& MonopolManager::getChanceCards()
 {
    return chanceCards;

 }

int MonopolManager::RollDice()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    int dice1 = (std::rand() % 6) + 1;
    int dice2 = (std::rand() % 6) + 1;
    return (dice1+dice2);
}

const std::shared_ptr<Player>* MonopolManager::CheckStreetOwner(const std::shared_ptr<Square>& square)
{
    // Attempt to dynamic cast the Square to a Street
    Street* street = dynamic_cast<Street*>(square.get());
    if (!street) {
        throw std::runtime_error("The square is not a street.");
    }

    for (const std::shared_ptr<Player>& p : players)
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

const std::shared_ptr<Player>* MonopolManager::CheckTrainOwner(const std::shared_ptr<Square>& square)
{
    Train* train = dynamic_cast<Train*>(square.get());
    if (!train) {
        throw std::runtime_error("The square is not a train.");
    }
    for(const std::shared_ptr<Player>& p : players)
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

const std::shared_ptr<Player>* MonopolManager::CheckWaterCompanyOwner(const std::shared_ptr<Square>& square)
{
    for(const std::shared_ptr<Player>& p : players)
    {
        if(p != currentPlayer)
        {
            if(p->gethasOwnWaterCompany())
                    return &p;
        }
    }
    return nullptr;

}

const std::shared_ptr<Player>* MonopolManager::CheckElectricCompanyOwner(const std::shared_ptr<Square>& square)
{
    for(const std::shared_ptr<Player>& p : players)
    {
        if( p != currentPlayer)
        {
            if(p->gethasOwnElectricCompany())
                    return &p;
        }
    }
    return nullptr;

}

void MonopolManager::CheckTaxPrice(Tax* tax)
{
    std::cout << "You need to pay  " << tax->getPrice() << " to the bank" << std::endl;
    std::cout << "current money:  " << currentPlayer->getMoney()<< std::endl;
    currentPlayer->setMoney(currentPlayer->getMoney() - tax->getPrice());
    std::cout << "Charging your money...  " << std::endl <<" money remained after charge: "<< currentPlayer->getMoney()<< std::endl;
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


 void MonopolManager::BuyStreet(Street* street)
 {
    int ans;
    std::cout<<"Current money: " <<currentPlayer->getMoney()<< std::endl;
    
    if(currentPlayer->getMoney() < street->getPrice())
    {
        std::cout << "You don't have enough money to buy this street..." <<std::endl;
    }

    else
    {
        std::cout << "Do you want to buy this street? 1.Yes , 2.No" <<std::endl;
        std::cin >> ans; 
        if(ans ==1)
        {
            if(currentPlayer->PurchaseStreet(street))
            {
                std::cout<<"Street: "<< street->name << " was purchased succesfully" <<std::endl;
                currentPlayer->displayLong(std::cout);
            }
        }
       
    }
   
 }

  void MonopolManager::BuyTrain(Train* train)
 {
    int ans;
    std::cout<<"Current money: " <<currentPlayer->getMoney()<< std::endl;
    std::cout<<"Cost: " <<train->getPrice()<< std::endl;
    if(currentPlayer->getMoney() < train->getPrice())
    {
        std::cout << "You don't have enough money to buy this train..." <<std::endl;
    }

    else
    {
        std::cout << "Do you want to buy this train? 1.Yes , 2.No" <<std::endl;
        std::cin >> ans; 
        if(ans ==1)
        {
            if(currentPlayer->PurchaseTrain(train))
            {
                std::cout<<"Train: "<< train->name << " was purchased succesfully" <<std::endl;
                currentPlayer->displayLong(std::cout);
            }
        }
       
    }
    
 }


  void MonopolManager::BuyWaterCompany(WaterCompany* waterCompany)
 {
    int ans;
    std::cout<<"Current money: " <<currentPlayer->getMoney()<< std::endl;
    std::cout<<"Cost: " <<waterCompany->getPrice()<< std::endl;
    if(currentPlayer->getMoney() < waterCompany->getPrice())
    {
        std::cout << "You don't have enough money to buy the Water Company..." <<std::endl;
    }

    else
    {
        std::cout << "Do you want to buy the Water Company? 1.Yes , 2.No" <<std::endl;
        std::cin >> ans; 
        if(ans ==1)
        {
            if(currentPlayer->PurchaseWaterCompany(waterCompany))
            {
                std::cout<< waterCompany->name << " was purchased succesfully" <<std::endl;
                currentPlayer->displayLong(std::cout);
            }
        }
       
    }

 }


  void MonopolManager::BuyElectricCompanyOwner(ElectricCompany* electricCompany)
 {
    int ans;
    std::cout<<"Current money: " <<currentPlayer->getMoney()<< std::endl;
    std::cout<<"Cost: " <<electricCompany->getPrice()<< std::endl;
    if(currentPlayer->getMoney() < electricCompany->getPrice())
    {
        std::cout << "You don't have enough money to buy the Water Company..." <<std::endl;
    }

    else
    {
        std::cout << "Do you want to buy the Water Company? 1.Yes , 2.No" <<std::endl;
        std::cin >> ans; 
        if(ans ==1)
        {
            if(currentPlayer->PurchaseElectricCompany(electricCompany))
            {
                std::cout<< electricCompany->name << " was purchased succesfully" <<std::endl;
                currentPlayer->displayLong(std::cout);
            }
        }
       
    }
    
 }

 
  void MonopolManager::CheckEdgeSquare(EdgeSquare* edgeSquare)
 {
    switch(edgeSquare->getType())
    {
        case EdgeSquareType::Start:
            GrantPlayerMoney(StartMoney);
            break;
        case EdgeSquareType::FreeParking:
            std::cout << "You are on FREE PARKING square, turn finished ..." <<std::endl;
            break;
        case EdgeSquareType::GoToJail:
           std::cout << "You are going to jail !!" <<std::endl;
           std::cout << "Know your rights ." <<std::endl;
                GoToJail();

         case EdgeSquareType::VisitNearJail:
           std::cout << "You are visiting near the jail, nothing to do here ..." <<std::endl;
                break;       

    }
    
 }

 void MonopolManager::GrantPlayerMoney(float sum)
 {
    currentPlayer->addMoney(sum);
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