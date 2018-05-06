#ifndef MONSTER_MANAGER_HPP_
#define MONSTER_MANAGER_HPP_

#include <memory>

#include "monster_factory.hpp"

class MonsterManager {
public:
    Monster *GetRandomMonster(size_t x, size_t y, ActionManager *action_manager, MapsManager *maps_manager);

private:
    MonsterFactory monster_factory_;
    std::vector<std::unique_ptr<Monster>> monster_list_;
};

#endif /* MONSTER_MANAGER_HPP_ */
