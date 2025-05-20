#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"
#include "Item.h"
#include "KeyRequiredCommand.h"
#include <memory>
#include <iostream>

int main() {
    // Create rooms
    std::shared_ptr<Room> foyer = std::make_shared<Room>("foyer", "You are in the foyer. There is a grand staircase and doors leading in all directions.");
    std::shared_ptr<Room> library = std::make_shared<Room>("library", "You are in a dusty old library. Bookcases line the walls.");
    std::shared_ptr<Room> kitchen = std::make_shared<Room>("kitchen", "You are in the kitchen. Pots and pans hang from the ceiling.");
    std::shared_ptr<Room> garden = std::make_shared<Room>("garden", "You are in a lush garden with blooming flowers.");
    std::shared_ptr<Room> cellar = std::make_shared<Room>("cellar", "You are in a dark, damp cellar. It smells of earth.");
    std::shared_ptr<Room> observatory = std::make_shared<Room>("observatory", "You are in an observatory with a large telescope.");
    std::shared_ptr<Room> ballroom = std::make_shared<Room>("ballroom", "You are in a grand ballroom with a sparkling chandelier.");
    std::shared_ptr<Room> bedroom = std::make_shared<Room>("bedroom", "You are in a cozy bedroom with a large bed and a window.");
    std::shared_ptr<Room> attic = std::make_shared<Room>("attic", "You are in a cluttered attic filled with old trunks.");
    std::shared_ptr<Room> secret_room = std::make_shared<Room>("secret-room", "You have found a secret room hidden behind a bookshelf!");

    Item* key = new Item("key", "A rusty key used to open a door.");
    library->addItem(key);

    Player::instance()->setCurrentRoom(foyer.get());

    Passage::createBasicPassage(foyer.get(), library.get(), "north", true);
    Passage::createBasicPassage(library.get(), observatory.get(), "up", true);
    Passage::createBasicPassage(foyer.get(), kitchen.get(), "east", true);
    Passage::createBasicPassage(kitchen.get(), garden.get(), "south", true);
    Passage::createBasicPassage(foyer.get(), cellar.get(), "down", true);
    Passage::createBasicPassage(foyer.get(), ballroom.get(), "west", true);
    Passage::createBasicPassage(ballroom.get(), bedroom.get(), "north", true);
    Passage::createBasicPassage(bedroom.get(), attic.get(), "up", true);
    Passage::createBasicPassage(library.get(), secret_room.get(), "west", true);


    Passage::createBasicPassage(garden.get(), kitchen.get(), "north", true);
    Passage::createBasicPassage(attic.get(), bedroom.get(), "down", true);
    Passage::createBasicPassage(cellar.get(), foyer.get(), "up", true);
    Passage::createBasicPassage(observatory.get(), library.get(), "down", true);

    secret_room->setEnterCommand(
    std::make_shared<KeyRequiredCommand>(secret_room.get(), "key", Player::instance())
    );

    ZOOrkEngine zoork(foyer);
    zoork.run();

    return 0;
}