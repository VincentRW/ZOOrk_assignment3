#include "RoomDefaultEnterCommand.h"
#include "Room.h"
#include <iostream>

void RoomDefaultEnterCommand::execute() {
    std::cout << gameObject->getDescription() << "\n";

    // List items in the room
    Room* room = static_cast<Room*>(gameObject);
    auto items = room->getItems(); // You may need to implement/get this method

    if (!items.empty()) {
        std::cout << "You see the following item(s) in this room:\n";
        for (auto item : items) {
            std::cout << "- " << item->getName() << "\n";
        }
    }
}