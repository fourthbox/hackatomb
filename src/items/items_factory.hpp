#ifndef ITEMS_FACTORY_HPP_
#define ITEMS_FACTORY_HPP_

#include "armor.hpp"
#include "weapon.hpp"

class Map;

// Classe totalmente temporanea e placeholder
class ItemsFactory {
public:
    ItemsFactory() {
        sword_ = new Weapon("a short sword", false, 1, 3);
        armor_ = new Armor("a leather armor", 1);
    }
    
    void PopulateMap(Map const &map);
    
private:
    Weapon* sword_;
    Armor* armor_;
};

#endif /* ITEMS_FACTORY_HPP_ */
