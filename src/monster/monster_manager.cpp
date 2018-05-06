#include "monster_manager.hpp"

Monster *MonsterManager::GetRandomMonster(size_t x, size_t y, ActionManager &action_manager, MapsManager &maps_manager) {
    auto monster {monster_factory_.CreateGoblin(x, x, action_manager, maps_manager)};
    monster_list_.push_back(std::move(monster));
    
    return monster.get();
}
