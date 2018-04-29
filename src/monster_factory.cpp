#include "monster_factory.hpp"

#include "bestiary.hpp"

Monster_p MonsterFactory::CreateGoblin(size_t x, size_t y, std::shared_ptr<ActionManager> action_manager, MapsManager_p maps_manager) {
    auto monster {std::shared_ptr<Monster>()};
    
    monster->Initialize(x, y, kGoblinStats.sprite_, kGoblinStats.name_, kGoblinStats.color_, kGoblinStats.stats_, action_manager, maps_manager);
    
    return monster;
}
