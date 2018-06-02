#include "actor_manager.hpp"

#include "game_utils.hpp"
#include "monster.hpp"
#include "player.hpp"

using std::string;

void ActorManager::Initialize() {
    assert(!initialized_);
    
    initialized_ = true;
}

void ActorManager::InitializePlayer(Coordinate start_position, ActionManager &action_manager, MapsManager &maps_manager) {
    player_manager_.InitializePlayer(start_position, action_manager, *this, maps_manager);
    actor_list_.push_back(&player_manager_.GetPlayer());
}

void ActorManager::InitializeMonsterManager(ActionManager &action_manager, MapsManager &maps_manager) {
    monster_manager_.Initialize(action_manager, *this, maps_manager);
}

void ActorManager::DrawMonsters(TCODConsole &console) {
    assert(initialized_);

    monster_manager_.Draw(console);
}

void ActorManager::DrawPlayer(TCODConsole &console) {
    assert(initialized_);

    player_manager_.GetPlayer().Draw(console);
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
    
    monster_manager_.Update();
}

void ActorManager::SetAllMonstersVisible() const {
    assert(initialized_);
    
    monster_manager_.SetPermaVisible(true);
}
