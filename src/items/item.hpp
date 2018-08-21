#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>

#include "map_entity.hpp"

class Item : public MapEntity {
public:
    Item(std::string const &short_description);
    inline std::string GetShortDescription() const { return short_description_; }
    
    inline std::string GetUuid() const { return uuid_; }
    
private:
    std::string uuid_, short_description_;
};

typedef std::unique_ptr<Item> Item_up;

#endif /* ITEM_HPP_ */
