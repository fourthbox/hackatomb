#include "monster_manager.hpp"

void MonsterManager::Initialize(ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager) {
    assert(!initialized_);
    
    action_manager_ = &action_manager;
    maps_manager_ = &maps_manager;
    
    // Get random position in rendom room
    auto starting_coors {maps_manager_->GetRandomPosition()};
    
    // Generate monster
    auto monster {monster_factory_.CreateGoblin(starting_coors.first,
                                                starting_coors.second,
                                                action_manager,
                                                actor_manager,
                                                maps_manager)};

    // Add it to the monster list
    monster_list_.push_back(std::move(monster));
    
    initialized_ = true;
}

void MonsterManager::Draw(TCODConsole &console) {
    assert(initialized_);
    
    for (auto const &monster : monster_list_) {
        if (monster->IsPermaVisible() || maps_manager_->IsInFov(monster->GetPosition().first, monster->GetPosition().second))
            monster->Draw(console);
    }
}

void MonsterManager::SetPermaVisible(bool is_perma_visible, Monster *monster) const {
    assert(initialized_);

    if (monster == nullptr) {
        for (auto const &mnst : monster_list_) {
            mnst->SetPermaVisible(is_perma_visible);
        }
    } else {
        monster->SetPermaVisible(is_perma_visible);
    }
}

void MonsterManager::Update(size_t speed) const {
    assert(initialized_);
    
    for (auto const &monster : monster_list_) {
        monster->Update(speed);
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
