#include "Item.h"
#include <iostream>

Item::Item(const std::string &n, const std::string &d)
    : GameObject(n, d), useCommand(nullptr) {}

Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> cmd)
    : GameObject(n, d), useCommand(cmd) {}

void Item::use() {
    if (useCommand) {
        useCommand->execute();
    } else {
        std::cout << "Nothing happens." << std::endl;
    }
}

void Item::setUseCommand(std::shared_ptr<Command> cmd) {
    useCommand = cmd;
}