#include "monster_manager.hpp"

void MonsterManager::Initialize(ActorManager &actor_manager) {
    assert(!initialized_);
    
    this->actor_manager_ = &actor_manager;
    
    initialized_ = true;
}

void MonsterManager::PopulateMap(MapsManager &maps_manager, DungeonCategory category) {
    assert(initialized_);
    
    // Generate all the monsters that this dungeon will host, based on
    // the amount of XP that must be yold by the dungeon.
    auto dungeon_maps {maps_manager.GetDungeonByCategory(category)};
    
    // Get random position in rendom room
//    auto starting_coors {maps_manager.GetRandomPosition()};
//
//    // Generate monster
//    auto monster {monster_factory_.BuildGoblin(starting_coors.first, starting_coors.second, maps_manager)};
    
//    // Add it to the monster list
//    monster_list_.push_back(std::move(monster));
}

void MonsterManager::Draw(TCODConsole &console, Player const &player, MapsManager &maps_manager) {
    assert(initialized_);
    
    for (auto const &monster : monster_list_) {
        if (monster->IsPermaVisible() || maps_manager.IsInFov((Actor&)player,
                                                                monster->GetPosition().first,
                                                                monster->GetPosition().second))
            monster->Draw(console);
    }
}

void MonsterManager::TogglePermaVisible(bool is_perma_visible, Monster *monster) const {
    assert(initialized_);

    if (monster == nullptr) {
        for (auto const &mnst : monster_list_) {
            mnst->TogglePermaVisible(is_perma_visible);
        }
    } else {
        monster->TogglePermaVisible(is_perma_visible);
    }
}

void MonsterManager::Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager) const {
    assert(initialized_);
    
    for (auto const &monster : monster_list_) {
        monster->Update(speed, action_manager, maps_manager);
    }
}

Monster *MonsterManager::GetMonsterByCoordinates(size_t x, size_t y) const {
    for (auto const &monster : monster_list_) {
        if (monster->GetPosition().first == x && monster->GetPosition().second == y) {
            return monster.get();
        }
    }
    
    return nullptr;
}

std::vector<Actor*> MonsterManager::GetMonsterList() const {
    assert (initialized_);
    
    std::vector<Actor*> new_list;
    
    for (auto const &monster : monster_list_)
        new_list.push_back(monster.get());
    
    return new_list;
}
