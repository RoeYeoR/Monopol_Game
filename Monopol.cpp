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
    
    MonopolManager::getInstance().setCurrentPlayer(MonopolManager::getInstance().getPlayers()[0]);
   
    std::cout << "Number of players:" <<numOfPlayers <<std::endl;
    std::cout << "Displaying the players:" <<std::endl;
    for (int i = 0; i <  MonopolManager::getInstance().getPlayers().size() ; i++)
    {
       MonopolManager::getInstance().getPlayers()[i]->displayShort(std::cout);
       std::cout << std::endl;
    }
    
    //player 1 turn
    currentPlayer = MonopolManager::getInstance().getCurrentPlayer();
    int diceResult = MonopolManager::getInstance().RollDice();
    std::cout << "Dice Result: " << diceResult << std::endl;
    
    currentPlayer->MoveOnBoard(diceResult);
    Point2D& newPos = currentPlayer->getCurrentPosition();
    std::cout << "Player's new position: " << newPos << std::endl;
    std::cout << "New position status: " <<  std::endl;
    (actuallBoard[newPos.getX()][newPos.getY()]->display(std::cout));
    
    const std::shared_ptr<Player>* p = board.checkSquareOwnerShip(actuallBoard[newPos.getX()][newPos.getY()]);
    if( p == nullptr)
    {      
        board.offerPlayerOptions(actuallBoard[newPos.getX()][newPos.getY()]);
    }
    else
    {
       actuallBoard[newPos.getX()][newPos.getY()]->display(std::cout);
       std::cout <<"it's occupied  by " << (*currentPlayer).getName();
    }

    //return 0;
}



