#include "actor_manager.hpp"

#include "game_utils.hpp"
#include "monster.hpp"
#include "player.hpp"

using std::string;

void ActorManager::Initialize() {
    assert(!initialized_);
    
    initialized_ = true;
}

void ActorManager::InitializePlayer(std::pair<size_t, size_t> start_position, ActionManager &action_manager, MapsManager &maps_manager) {
    player_manager_.InitializePlayer(start_position, action_manager, maps_manager);
    actor_list_.push_back(&player_manager_.GetPlayer());
}

Actor *ActorManager::GetActorByCoordinates(size_t x, size_t y) {
    assert(initialized_);
    for (auto const &actor : actor_list_) {
        if (actor->x_ == x && actor->y_ == y) {
//            if (map_category.empty() && )
        }
    }
    
    return nullptr;
}

void ActorManager::Update() {
    assert(initialized_);
    
    // TODO: usare monster manager
    
    for (auto const &monster : GetMonsterList()) {
        monster->Update();
    }
}

std::vector<Monster*> ActorManager::GetMonsterList() {
    assert(initialized_);
    
    std::vector<Monster*> monster_list;
    
    for (auto const &actor : actor_list_) {
        auto monster {dynamic_cast<Monster*>(actor)};
        if (monster != nullptr)
            monster_list.push_back(monster);
    }

    return monster_list;
}

void ActorManager::SetAllMonstersVisible() {
    assert(initialized_);
    
    auto monster_list {GetMonsterList()};

    for (auto const &monster : monster_list) {
        monster->SetAlwaysVisible(true);
    }
}
