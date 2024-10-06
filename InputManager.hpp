#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

enum class InputState {
    None,
    BuyStreet,
    PayTax,
    BuyTrain,
    BuyWaterCompany,
    BuyElectricCompany,
    HandleChance,
    HandleCommunityChest,
    EdgeSquare,
    // Add other states as needed
};

class InputManager {
public:
    static InputManager& getInstance() {
        static InputManager instance;
        return instance;
    }

    InputState getCurrentState() const { return currentState; }
    void setCurrentState(InputState state) { currentState = state; }

    bool isWaitingForInput() const { return waitingForInput; }
    void setWaitingForInput(bool waiting) { waitingForInput = waiting; }

    int getPlayerChoice() const { return playerChoice; }
    void setPlayerChoice(int choice) { playerChoice = choice; }

    void reset() {
    currentState = InputState::None;   // Reset the state
    waitingForInput = false;           // Reset waiting state
    playerChoice = -1;                 // Reset the player's choice
}

private:
    InputManager() : currentState(InputState::None), waitingForInput(false), playerChoice(-1) {}

    InputState currentState;
    bool waitingForInput;
    int playerChoice;
};

#endif
