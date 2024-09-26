#include <iostream>
#include <string>
#include "Player.hpp"
#include "MonopolManager.hpp"
#include "Board.hpp"


int main ()
{
    int numOfPlayers;
    std::string name; 
    std::shared_ptr<Player> currentPlayer = nullptr; 
    Board& board = Board::getInstance();
    std::vector<std::vector<std::shared_ptr<Square>>>& actuallBoard =board.getBoard();

    std::cout <<"Enter number of Players: " <<std::endl;
    std::cin >> numOfPlayers;

    for (int i = 0; i < numOfPlayers; i++)
    {
         std::cout <<"Enter name of player " <<i+1<< ":" <<std::endl;
         std::cin >> name;
         //MonopolManager::getInstance().getPlayers().push_back(Player(name));
         MonopolManager::getInstance().getPlayers().push_back(std::make_shared<Player>(name));
    }
    
    std::cout<<std::endl;
    std::cout<<std::endl;

    MonopolManager::getInstance().setCurrentPlayer(MonopolManager::getInstance().getPlayers()[0]);
   
    std::cout << "Number of players:" <<numOfPlayers <<std::endl << std::endl;
    std::cout << "Displaying the players:" <<std::endl << std::endl;
    for (int i = 0; i <  MonopolManager::getInstance().getPlayers().size() ; i++)
    {
       MonopolManager::getInstance().getPlayers()[i]->displayShort(std::cout);
       std::cout << std::endl;
    }


    std::shared_ptr<Player>* winner = nullptr;
    int i=0;
   
    while (winner == nullptr )
    {
    std::cout << "************************************"<< std::endl<< std::endl; 
   
    MonopolManager::getInstance().setCurrentPlayer(MonopolManager::getInstance().getPlayers()[i]);
    //player i turn
    currentPlayer = MonopolManager::getInstance().getCurrentPlayer();
    std::cout << currentPlayer->getName() <<"'s turn!"<< std::endl<< std::endl;
    int diceResult = MonopolManager::getInstance().RollDice();
    std::cout << "Dice Result: " << diceResult << std::endl;
    
    currentPlayer->MoveOnBoard(diceResult);
    Point2D& newPos = currentPlayer->getCurrentPosition();
    std::cout << currentPlayer->getName()<<"-> new position: " << newPos << std::endl<< std::endl;
    
    (actuallBoard[newPos.getX()][newPos.getY()]->display(std::cout));
    
    
    std::shared_ptr<Player>* p = board.checkSquareOwnerShip(actuallBoard[newPos.getX()][newPos.getY()]);
    if( p == nullptr)
    {      
        board.offerPlayerOptions(actuallBoard[newPos.getX()][newPos.getY()]);
    }
    else if( *p != currentPlayer)
    {
        std::shared_ptr<Square>& currentSquare =  actuallBoard[newPos.getX()][newPos.getY()];
        currentSquare->display(std::cout);
        std::cout <<"This Sqaure is owned by " << (*p)->getName();
        float calculatedPrice = MonopolManager::getInstance().getActuallBillOfSquare(currentSquare,p);  
      
       if(!MonopolManager::getInstance().ChargePlayer(currentPlayer,*p,calculatedPrice))
       {
           std::cout<< currentPlayer->getName() <<" went bankrupt ..." <<std::endl << "All it's properties were passed to " 
           << (*p)->getName() <<std::endl;
       }
       else
       {
             std::cout << "Transfer of " << currentSquare->getPrice() <<"₪ was done Successfully!"<<std::endl;
       }
    }
    else
    {
        board.offerPlayerUpgrades(actuallBoard[newPos.getX()][newPos.getY()]);

    }
        winner = MonopolManager::getInstance().CheckIsWinner();
        i++;
        i = (i % numOfPlayers);
        std::cout << "************************************"<< std::endl<< std::endl; 
    }
   

    //return 0;
}



