#include "NullCommand.h"
#include "NullRoom.h"
#include <memory>

NullRoom::NullRoom() : Room("Nowhere", "This is a nonplace.", std::make_shared<NullCommand>()) {}