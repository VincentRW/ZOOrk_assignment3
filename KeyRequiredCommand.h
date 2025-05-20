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
            // Remove lock (restore default enter command)
            room->setEnterCommand(std::make_shared<NullCommand>());
            room->enter();
        } else {
            std::cout << "You need the " << requiredItem << " to enter this room!" << std::endl;
        }
    }
private:
    Room* room;
    std::string requiredItem;
    Player* player;
};