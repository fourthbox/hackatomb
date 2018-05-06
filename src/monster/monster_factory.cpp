#include "monster_factory.hpp"

#include "bestiary.hpp"

std::unique_ptr<Monster> MonsterFactory::CreateGoblin(size_t x, size_t y, ActionManager *action_manager, MapsManager *maps_manager) {
    auto monster {std::make_unique<Monster>()};
    
    monster->Initialize(x, y, kGoblinStats.sprite_, kGoblinStats.name_, kGoblinStats.color_, kGoblinStats.stats_, action_manager, maps_manager);
    
    return std::move(monster);
}
