#include "actor_manager.hpp"

#include "game_utils.hpp"
#include "player.hpp"

using std::string;

ActorManager::ActorManager() {
    player_ = nullptr;
}

void ActorManager::Initialize() {
    assert(!initialized_);
    initialized_ = true;
}

Actor_p ActorManager::GetActorByCoordinates(size_t x, size_t y) {
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
    
    for (auto const &actor : actor_list_) {
        actor->Update();
    }
}

std::vector<Actor_p>& ActorManager::GetActorList() {
    assert(initialized_);
    
    return actor_list_;
}

bool ActorManager::AddActor(Actor_p new_actor) {
    assert(initialized_);
    
    for (auto const &actor : actor_list_) {
        if (actor == new_actor) {
            Utils::LogError("ActorManager", "Trying to add an already existing actor");
            return false;
        }
    }

    new_actor->SetActorManager(shared_from_this());
    actor_list_.push_back(new_actor);
    
    return true;
}

void ActorManager::AddPlayer(std::shared_ptr<Player> player) {
    assert(initialized_ && player_ == nullptr);
    
    player_ = player;
    
    player_->Actor::SetActorManager(shared_from_this());
}

std::shared_ptr<Player> ActorManager::GetPlayer() {
    assert(initialized_ && player_ != nullptr);
    
    return player_;
}
