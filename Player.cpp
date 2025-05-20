#include <memory>
#include "Player.h"

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

Item* Player::getItem(const std::string& name) {
    for (Item* item : inventory) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

void Player::addItem(Item* item) {
    inventory.push_back(item);
}

void Player::removeItem(const std::string& name) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == name) {
            inventory.erase(it);
            return;
        }
    }
}

Item* Player::retrieveItem(const std::string& name) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == name) {
            Item* found = *it;
            inventory.erase(it);
            return found;
        }
    }
    return nullptr;
}

void Player::printInventory() const {
    if (inventory.empty()) {
        std::cout << "You are not carrying anything." << std::endl;
    } else {
        std::cout << "You are carrying:" << std::endl;
        for (const Item* item : inventory) {
            std::cout << "- " << item->getName() << std::endl;
        }
    }
}