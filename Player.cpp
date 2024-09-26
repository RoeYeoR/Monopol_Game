#include "Player.hpp"


Player::Player(std::string name) : name(name) , money(1500) 
{
    currentPosition.setX(10);
    currentPosition.setY(10);

    hasOwnElectricCompany = false;
    hasOwnWaterCompany = false;
    isInJail = false;
    isBankrupt =false;
}

std::string Player::getName() 
 {
    return name;
 }

float Player::getMoney()
{

    return money;

}

bool  Player::getIsInJail()
{
   return isInJail;
}

bool Player::getIsBankrupt()
{

    return isBankrupt;
}

 void Player::setMoney(float newMoney)
 {

    money = newMoney;
 }

 void Player::changeMoney(float newMoney)
 {

    money += newMoney;
 }

void Player::setIsBankrupt(bool var)
{
    isBankrupt = var;
}

void Player::setHasOwnWaterCompany(bool var)
{
   hasOwnWaterCompany = var;
}
void Player::setHasOwnElectricCompany(bool var)
{
   hasOwnElectricCompany = var;
}

 void Player::setIsInJail(bool var)
 {
    isInJail = var;
 }

Point2D& Player::getCurrentPosition()
{
    return currentPosition;
}


  std::vector<Street>& Player::getStreets() 
 {
    return streets;

 }

  std::vector<Train>& Player::getTrains() 
 {
    return trains;

 }

 const bool Player::gethasOwnWaterCompany() const
{
    return hasOwnWaterCompany;

}
const bool Player::gethasOwnElectricCompany() const
{
        return hasOwnElectricCompany;
}


void Player::MoveOnBoard(int diceResult)
{
 // bottom line
 if(currentPosition.getX() == 10)
 {
    if(currentPosition.getY() - diceResult > 0)
        {
            currentPosition.setY(currentPosition.getY() - diceResult); 
        }
    else
    {
        while(currentPosition.getY() > 0)
        {
            currentPosition.setY(currentPosition.getY()-1);
            diceResult--; 
        }

        currentPosition.setX(currentPosition.getX() - diceResult );
    }
 }

// Upper line
 else if(currentPosition.getX() == 0)
 {
     if(currentPosition.getY() + diceResult < 10)
        {
            currentPosition.setY(currentPosition.getY() + diceResult); 
        }
    else
    {
        while(currentPosition.getY() < 10)
        {
            currentPosition.setY(currentPosition.getY() + 1);
            diceResult--; 
        }

        currentPosition.setX(currentPosition.getX() + diceResult);
    }

 }

 // left line
 else if(currentPosition.getY() == 0)
 {
      if(currentPosition.getX() - diceResult > 0)
        {
            currentPosition.setX(currentPosition.getX() - diceResult); 
        }
    else
    {
        while(currentPosition.getX() > 0)
        {
            currentPosition.setX(currentPosition.getX() - 1);
            diceResult--; 
        }

        currentPosition.setY(currentPosition.getY() + diceResult);
    }

 }

  // right line
 else if(currentPosition.getY() == 10)
 {
    if(currentPosition.getX() + diceResult < 10)
        {
            currentPosition.setX(currentPosition.getX() + diceResult); 
        }
    else
    {
        while(currentPosition.getX() < 10)
        {
            currentPosition.setX(currentPosition.getX() + 1);
            diceResult--; 
        }

        currentPosition.setY(currentPosition.getY() - diceResult);
    } 
 }

}


void Player::GoToSquare(Point2D& p)
{
    currentPosition = p;

}

 bool Player::PurchaseStreet(Street* street)
 {
    streets.push_back(*street);
    money -= street->getPrice();
    return true;
 }

 bool Player::PurchaseTrain(Train* train)
 {
    trains.push_back(*train);
    money -= train->getPrice();
    Train::count++;
    return true;
 }

bool Player::PurchaseWaterCompany(WaterCompany* waterCompany)
{
    money -= waterCompany->getPrice();
    hasOwnWaterCompany = true;
    return true;
}


bool Player::PurchaseHouse(Street* street)
{
   street->addHouse(); 

}
bool Player::PurchaseHotel(Street* street)
{
    street->addHotel();
}


bool Player::PurchaseElectricCompany(ElectricCompany* electricCompany )
{

    money -= electricCompany->getPrice();
    hasOwnElectricCompany = true;
    return true;
}

bool Player::AddChance()
{
  Chance* card = nullptr;
  std::vector<Chance>& originalChanceCards =  MonopolManager::getInstance().getGameChanceCards();
  for (Chance& c : originalChanceCards)
  {
    if(!c.getWasInUse())
    {
        card = &c;
        break;
    }
  }
  if(card != nullptr)
  {
    ChanceCards.push_back(*card);
    return true;
  }
  return false;
   
}

 void Player::displayShort(std::ostream& os) const 
 {
    os << "Player short status: " << "name: " << name << "," << " money: " << money << std::endl;

 }

  void Player::displayLong(std::ostream& os) const 
 {
    os << "Player status: " << "name: " << name << "," << " money: " << money << 
    ", current Position on board: " << currentPosition << ", Own Electric Company?" << (hasOwnElectricCompany ? " Yes" : " No")
    <<  ", Own Water Company?" << (hasOwnWaterCompany ? " Yes" : " No") <<std::endl;

    // Loop through all streets and call their display method
    os << "Owned Streets:" << std::endl;
    if(streets.size() ==0)
    {
         os << "No streets yet." << std::endl;
    }
    else{
        
        for (const Street& street : streets) {
        street.display(os); // Call the display method for each street
        }

    }

   // Loop through all trains and call their display method
    os << "Owned Trains:" << std::endl;
    if(trains.size() ==0)
    {
         os << "No trains yet." << std::endl;
    }
    else{
    
    for (const Train& train : trains) {
        train.display(os); // Call the display method for each train
    }


    }
  



 }