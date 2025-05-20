#include "Item.h"
#include <memory>
#include <utility>

Item::Item(const std::string &n, const std::string &d) : GameObject(n, d),
                                                         useCommand(std::make_shared<NullCommand>()) {}

Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : GameObject(n, d),
                                                                                     useCommand(std::move(c)) {}

void Item::use() {
    std::cout << "You use the " << name << ", but nothing special happens." << std::endl;
}

void Item::setUseCommand(std::shared_ptr<Command> c) {
    useCommand = c;
}