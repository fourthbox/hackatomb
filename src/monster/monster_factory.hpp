#ifndef MONSTER_FACTORY_HPP_
#define MONSTER_FACTORY_HPP_

#include "monster.hpp"

class MonsterFactory {
public:
    /**
     Creates a goblin in the specified position.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param maps_manager The maps manager
     @return A unique pointer to the generated monster.
     */
    std::unique_ptr<Monster> BuildGoblin(size_t x, size_t y, MapsManager &maps_manager);
};

#endif /* MONSTER_FACTORY_HPP_ */
