#pragma once
#include "Command.h"
#include "Player.h"
#include "NullCommand.h"
#include "Room.h"
#include <iostream>
#include <memory>
#include <string>

class KeyRequiredCommand : public Command {
public:
    KeyRequiredCommand(Room* room, const std::string& requiredItem, Player* player)
        : Command(room), room(room), requiredItem(requiredItem), player(player) {}

    void execute() override {
    if (player->getItem(requiredItem) != nullptr) {
        std::cout << "You unlock the door with the " << requiredItem << " and enter " << room->getName() << "!" << std::endl;
        room->setEnterCommand(std::make_shared<NullCommand>());
        room->enter();
    } else {
        std::cout << "The door is locked. Would you like to use an item? (yes/no)\n> ";
        std::string answer;
        std::getline(std::cin, answer);
        if (answer == "yes" || answer == "y") {
            std::cout << "Which item would you like to use?\n> ";
            std::string itemName;
            std::getline(std::cin, itemName);
            if (player->getItem(itemName) != nullptr) {
                if (itemName == requiredItem) {
                    std::cout << "You unlock the door with the " << requiredItem << " and enter " << room->getName() << "!" << std::endl;
                    room->setEnterCommand(std::make_shared<NullCommand>());
                    room->enter();
                } else {
                    std::cout << "That item doesn't unlock the door." << std::endl;
                }
            } else {
                std::cout << "You don't have that item." << std::endl;
            }
        } else {
            std::cout << "You decide not to use an item.\n";
        }
    }
}
    
    
private:
    Room* room;
    std::string requiredItem;
    Player* player;
};