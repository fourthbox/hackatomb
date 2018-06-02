#ifndef MONSTER_FACTORY_HPP_
#define MONSTER_FACTORY_HPP_

#include "monster.hpp"

class MonsterFactory {
public:
    std::unique_ptr<Monster> CreateGoblin(size_t x, size_t y, ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager);
};

#endif /* MONSTER_FACTORY_HPP_ */
