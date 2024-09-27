#include "Board.hpp"
#include "MonopolManager.hpp"

Board::Board() :board(rows, std::vector<std::shared_ptr<Square>>(cols))
{   
    //edge square
    setSquare(0,0,std::make_shared<EdgeSquare>("FREE PARKING",EdgeSquareType::FreeParking));

    setSquare(0, 1, std::make_shared<Street>("KENTUCKY Ave", 220,Color::Red,100));
    setSquare(0, 2, std::make_shared<Chance>("Chance Square"));
    setSquare(0, 3, std::make_shared<Street>("INDIANA Ave", 220,Color::Red,100));
    setSquare(0, 4, std::make_shared<Street>("ILLINOIS Ave", 240,Color::Red,100));
    setSquare(0, 5, std::make_shared<Train>("B.& O. RAILROAD"));
    setSquare(0, 6, std::make_shared<Street>("ATLANTIC Ave", 260,Color::Yellow,100));
    setSquare(0, 7, std::make_shared<Street>("VENTNOR Ave", 260,Color::Yellow,100));
    setSquare(0, 8, std::make_shared<WaterCompany>("Water"));
    setSquare(0, 9, std::make_shared<Street>("MARVIN GARDEN", 120,Color::Yellow,100));

    //edge square
    setSquare(0,10,std::make_shared<EdgeSquare>("GO TO JAIL !",EdgeSquareType::GoToJail));

    setSquare(1, 10, std::make_shared<Street>("PACIFIC Ave", 300,Color::Green,100));
    setSquare(2,10, std::make_shared<Street>("NORTH CAROLINA Ave", 300,Color::Green,100));
    setSquare(3,10, std::make_shared<CommunityChest>("CommunityChest Square"));
    setSquare(4, 10, std::make_shared<Street>("PENNSYLVANIA Ave", 320,Color::Green,100));
    setSquare(5,10, std::make_shared<Train>("SHORT LINE"));
    setSquare(6, 10, std::make_shared<Chance>("Chance Square"));
    setSquare(7, 10, std::make_shared<Street>("PARK PLACE", 120,Color::Blue,100));
    setSquare(8, 10, std::make_shared<Tax>("LUXURY TAX", 100));
    setSquare(9, 10, std::make_shared<Street>("BOARDWALK", 400,Color::Blue,100));

     //edge square
    setSquare(10,10,std::make_shared<EdgeSquare>("START",EdgeSquareType::Start));

    setSquare(10, 9, std::make_shared<Street>("MEDITER-RANEAN Ave", 60,Color::Brown,100));
    setSquare(10, 8, std::make_shared<CommunityChest>("CommunityChest Square"));
    setSquare(10, 7, std::make_shared<Street>("BALTIC Ave", 60,Color::Brown,100));
    setSquare(10, 6, std::make_shared<Tax>("INCOME TAX", 200));
    setSquare(10, 5, std::make_shared<Train>("READING RAILROAD"));
    setSquare(10, 4, std::make_shared<Street>("ORIENTAL Ave", 100,Color::Azure,100));
    setSquare(10, 3, std::make_shared<Chance>("Chance Square"));
    setSquare(10, 2, std::make_shared<Street>("VERMONT Ave", 100,Color::Azure,100));
    setSquare(10, 1, std::make_shared<Street>("CONNECTICUT Ave", 120,Color::Azure,100));

    //edge square
    setSquare(10,0,std::make_shared<EdgeSquare>("VISITING NEAR JAIL",EdgeSquareType::VisitNearJail));

    setSquare(1, 0, std::make_shared<Street>("NEW YORK Ave", 200,Color::Orange,100));
    setSquare(2, 0, std::make_shared<Street>("TENNESSEE Ave", 180,Color::Orange,100));
    setSquare(3, 0, std::make_shared<CommunityChest>("CommunityChest Square"));
    setSquare(4, 0, std::make_shared<Street>("ST.JAMES PLACE", 180,Color::Orange,100));
    setSquare(5, 0, std::make_shared<Train>("PENNSYLVANIA RAILROAD"));
    setSquare(6, 0, std::make_shared<Street>("VIRGINIA Ave", 160,Color::Pink,100));
    setSquare(7, 0, std::make_shared<Street>("STATES Ave", 140,Color::Pink,100));
    setSquare(8, 0, std::make_shared<ElectricCompany>("Electric"));
    setSquare(9, 0, std::make_shared<Street>("ST.CHARLES PLACE", 140,Color::Pink,100));
    
}

void Board::setSquare(int x, int y, std::shared_ptr<Square> square)
{
    if (x >= 0 && x < rows && y >= 0 && y < cols) {
        board[x][y] = square;
    }
}

std::vector<std::vector<std::shared_ptr<Square>>>& Board::getBoard()
{
  return board;
}


 std::shared_ptr<Player>* Board::checkSquareOwnerShip(const std::shared_ptr<Square>& square) {
    
    std::shared_ptr<Player>* p =nullptr;

    if (dynamic_cast<Street*>(square.get())) {
     
       p = MonopolManager::getInstance().CheckStreetOwner(square);
    } 
    else if (dynamic_cast<Train*>(square.get())) {
       
        p = MonopolManager::getInstance().CheckTrainOwner(square);
    }
    else if (dynamic_cast<WaterCompany*>(square.get())) {
        
      p = MonopolManager::getInstance().CheckWaterCompanyOwner(square);
    }
     else if (dynamic_cast<ElectricCompany*>(square.get())) {
        
       p = MonopolManager::getInstance().CheckElectricCompanyOwner(square);
    }

    return p;
    
}


void Board::offerPlayerOptions(const std::shared_ptr<Square>& square)
{
    if (auto street = dynamic_cast<Street*>(square.get())) {
        std::cout << "It's a StreetSquare." << std::endl;
       MonopolManager::getInstance().BuyStreet(street);

    } else if (auto tax = dynamic_cast<Tax*>(square.get())) {
        std::cout << "It's a TaxSquare." << std::endl;
         MonopolManager::getInstance().CheckTaxPrice(tax);

    }
    else if (auto chance = dynamic_cast<Chance*>(square.get())) {
        std::cout << "It's a ChanceSquare." << std::endl;
         MonopolManager::getInstance().AddChance();
    }
    else if (auto communityChest = dynamic_cast<CommunityChest*>(square.get())) {
        std::cout << "It's a CommunityChestSquare." << std::endl;
        MonopolManager::getInstance().AddCommunityChest();
    }
    else if (auto train = dynamic_cast<Train*>(square.get())) {
        std::cout << "It's a TrainSquare." << std::endl;
        MonopolManager::getInstance().BuyTrain(train);
    }
    else if (auto waterCompany =dynamic_cast<WaterCompany*>(square.get())) {
        std::cout << "It's a WaterCompanySquare." << std::endl;
        MonopolManager::getInstance().BuyWaterCompany(waterCompany);
    }
     else if (auto electricCompany =dynamic_cast<ElectricCompany*>(square.get())) {
        std::cout << "It's an ElectricCompanySquare." << std::endl;
        MonopolManager::getInstance().BuyElectricCompanyOwner(electricCompany);
    }
    else if (auto edgeSquare =dynamic_cast<EdgeSquare*>(square.get())) {
        std::cout << "It's an EdgeSquare." << std::endl;
          MonopolManager::getInstance().CheckEdgeSquare(edgeSquare);
    } 
     else {
        std::cout << "It's a base Square." << std::endl;
    }


}

void Board::offerPlayerUpgrades(const std::shared_ptr<Square>& square)
{
    if (auto street = dynamic_cast<Street*>(square.get())) {
        std::cout << "This Street belongs to you." << std::endl;
        MonopolManager::getInstance().UpgradeStreet(street);
    } 
     else {
        std::cout << "This Square can not be Upgraded." << std::endl;
    }
}
