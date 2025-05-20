#include "NullPassage.h"
#include "Room.h"
#include <memory>
#include <utility>


Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        passageMap.erase(direction);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}

Item* Room::getItem(const std::string& name) {
    for (Item* item : items) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

void Room::addItem(Item* item) {
    items.push_back(item);
}

void Room::removeItem(const std::string& name) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == name) {
            items.erase(it);
            return;
        }
    }
}

Item* Room::retrieveItem(const std::string& name) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == name) {
            Item* found = *it;
            items.erase(it);
            return found;
        }
    }
    return nullptr;
}