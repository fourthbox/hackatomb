#ifndef MONSTER_FACTORY_HPP_
#define MONSTER_FACTORY_HPP_

#include "monster.hpp"

class MonsterFactory {
public:
    Monster_p CreateGoblin(size_t x, size_t y, std::shared_ptr<ActionManager> action_manager, MapsManager_p maps_manager);
};

#endif /* MONSTER_FACTORY_HPP_ */
