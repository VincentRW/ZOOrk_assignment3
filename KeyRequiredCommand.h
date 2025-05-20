#pragma once
#include "Command.h"
#include "Player.h"
#include <iostream>
#include <memory>

class KeyRequiredCommand : public Command {
public:
    KeyRequiredCommand(GameObject* target, const std::string& requiredItem)
        : Command(target), requiredItem(requiredItem) {}

    void execute() override {
        Player* player = Player::getInstance();
        if (player->getItem(requiredItem) != nullptr) {
            std::cout << "You unlock the door with the " << requiredItem << " and enter " << gameObject->getName() << "!" << std::endl;
            // Optionally, remove key from inventory:
            // player->removeItem(requiredItem);
            // Remove lock after use:
            gameObject->setEnterCommand(std::make_shared<NullCommand>());
            gameObject->enter();
        } else {
            std::cout << "You need the " << requiredItem << " to enter this room!" << std::endl;
        }
    }
private:
    std::string requiredItem;
};