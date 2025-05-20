#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include <map>
#include <memory>

class Passage;

class Room : public Location {
public:
    Room(const std::string &, const std::string &);

    Room(const std::string &, const std::string &, std::shared_ptr<Command>);
      
      std::vector<Item*> getItems() const;
      void addItem(Item* item);
      void removeItem(const std::string& name);
      Item* getItem(const std::string& name);
      Item* retrieveItem(const std::string&);
//    void addCharacter(Character*);
//    void removeCharacter(const std::string&);
//    Character* getCharacter(const std::string&);

    void addPassage(const std::string &, std::shared_ptr<Passage>);

    void removePassage(const std::string &);

    std::shared_ptr<Passage> getPassage(const std::string &);

protected:
    std::vector<Item*> items;
    std::vector<Character*> characters;
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
};


#endif //ZOORK_ROOM_H
