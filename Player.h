#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"

class Player : public Character {
public:
    static Player *instance() {
        // Note: lazy instantiation of the singleton Player object
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    Item* getItem(const std::string& name);

    void addItem(Item* item);

    void removeItem(const std::string& name);

    Item* retrieveItem(const std::string& name); 
    
    void printInventory() const;

    void setCurrentRoom(Room*);

    Room* getCurrentRoom() const;

    Player(const Player &) = delete;

    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()) {}
};

#endif //ZOORK_PLAYER_H
