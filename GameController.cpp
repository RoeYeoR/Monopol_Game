#include "GameController.hpp"

GameController::GameController(GameModel& model, GameView& view) 
    : model(model), view(view)
     {
        model.setNotifyFunction([&view](const std::string& message) { 
            view.showMessage(message); 
        });

        view.promptNumberOfPlayers();
     }

  void GameController::handleEvents(sf::RenderWindow& window, sf::Event event) {

        // Handle text input
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128 && event.text.unicode != 13) { // Ignore Enter key
                if (std::isdigit(static_cast<char>(event.text.unicode))) {
                    input += static_cast<char>(event.text.unicode);
                    view.setInputText(input); // Method to update the input text in view
                }
            }
            // On Enter key, validate and process input
            if (event.text.unicode == 13) { // Enter key pressed
                int numPlayers = std::stoi(input);
                if (numPlayers >= 2 && numPlayers <= 8) {
                    // Create player icons
                    for (int i = 0; i < numPlayers; ++i) {
                        std::shared_ptr<Player> player = std::make_shared<Player>("Player " + std::to_string(i + 1));
                        model.addPlayer(player); 
                        sf::Sprite playerSprite;
                        playerSprite.setTexture(view.getPlayerTextures()[i]);
                        view.getPlayerIcons().push_back(playerSprite);
                            
                    }

                  // Clear input for next use
                    input.clear();
                // Proceed to the game or update view accordingly
                }
                 else 
                 {
                    // Handle invalid input (e.g., reset input or display error)
                    input.clear();
                    view.setInputText("Invalid input. Try again.");
                }
            }
        }
    
} 


void GameController::updateGame() {
    // Update game logic here, such as moving players, updating UI, etc.
    view.updatePlayerIcons();
}


