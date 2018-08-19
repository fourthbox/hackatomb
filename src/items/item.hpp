#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>

class Item {
public:
    Item();
    std::string GetShortDescription() { return "asdasd"; }
    
private:
    std::string uuid_;
};

typedef std::unique_ptr<Item> Item_up;

#endif /* ITEM_HPP_ */
