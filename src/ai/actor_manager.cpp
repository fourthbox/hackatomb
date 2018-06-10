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
    player_manager_.InitializePlayer(start_position);
}

void ActorManager::InitializeMonsterManager(ActionManager &action_manager, MapsManager &maps_manager) {
    monster_manager_.Initialize(*this, maps_manager);
}

void ActorManager::DrawMonsters(TCODConsole &console, MapsManager &maps_manager) {
    assert(initialized_);

    monster_manager_.Draw(console, GetPlayer(), maps_manager);
}

void ActorManager::DrawPlayer(TCODConsole &console) {
    assert(initialized_);

    player_manager_.GetPlayer().Draw(console);
}

Actor *ActorManager::GetActorByCoordinates(size_t x, size_t y) {
    assert(initialized_);
    
    // Check if player is there
    if (auto *player {&player_manager_.GetPlayer()};
        player->GetPosition().first == x
        && player->GetPosition().second == y)
        return player;
    
    return monster_manager_.GetMonsterByCoordinates(x, y);
}

void ActorManager::Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager) {
    assert(initialized_);
    
    monster_manager_.Update(speed, action_manager, maps_manager);
}

void ActorManager::SetAllMonstersVisible() const {
    assert(initialized_);
    
    monster_manager_.SetPermaVisible(true);
}
