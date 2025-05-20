#include <algorithm>
#include "ZOOrkEngine.h"
#include <memory>
#include <utility>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "inventory" || command == "inv") { // <-- ADD THIS BLOCK
            player->printInventory();
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else if (command == "use") { 
            handleUseCommand(arguments);
        }else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    player->setCurrentRoom(passage->getTo());
    passage->enter();
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();

    // No argument: look at the room
    if (arguments.empty()) {
        std::cout << currentRoom->getDescription() << std::endl;
        return;
    }

    // Argument provided: look for item in room or inventory
    std::string target = arguments[0];

    // Try to find item in the room
    Item* itemInRoom = currentRoom->getItem(target);
    if (itemInRoom != nullptr) {
        std::cout << itemInRoom->getDescription() << std::endl;
        return;
    }

    // Try to find item in player's inventory
    Item* itemInInventory = player->getItem(target);
    if (itemInInventory != nullptr) {
        std::cout << itemInInventory->getDescription() << std::endl;
        return;
    }

    std::cout << "You don't see any \"" << target << "\" here." << std::endl;
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?" << std::endl;
        return;
    }
    std::string itemName = arguments[0];
    Room* room = player->getCurrentRoom();

    // Try to take the item from the room
    Item* item = room->retrieveItem(itemName);
    if (item) {
        player->addItem(item);
        std::cout << "You take the " << itemName << "." << std::endl;
    } else {
        std::cout << "There is no " << itemName << " here." << std::endl;
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?" << std::endl;
        return;
    }
    std::string itemName = arguments[0];

    // Try to drop the item from the player's inventory
    Item* item = player->retrieveItem(itemName);
    if (item) {
        player->getCurrentRoom()->addItem(item);
        std::cout << "You drop the " << itemName << "." << std::endl;
    } else {
        std::cout << "You don't have a " << itemName << "." << std::endl;
    }
}

void ZOOrkEngine::handleUseCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Use what?" << std::endl;
        return;
    }
    std::string itemName = arguments[0];
    Item* item = player->getItem(itemName);
    if (item) {
        item->use();
    } else {
        std::cout << "You don't have a " << itemName << " to use." << std::endl;
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}

