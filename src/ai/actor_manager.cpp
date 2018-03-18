#include "actor_manager.hpp"

#include "game_utils.hpp"

typedef std::shared_ptr<Actor> p_Actor;

using std::string;

void ActorManager::Initialize() {
    assert(!initialized_);
    initialized_ = true;
}

p_Actor ActorManager::GetActorByCoordinates(size_t x, size_t y, string &map_category, short floor) {
    assert(initialized_);
    for (auto const &actor : actor_list_) {
        if (actor->map_category_ == map_category &&
            actor->floor_ == floor &&
            actor->x_ == x && actor->y_ == y) {
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

std::vector<p_Actor>& ActorManager::GetActorList() {
    assert(initialized_);
    
    return actor_list_;
}

bool ActorManager::AddActor(std::shared_ptr<Actor> new_actor) {
    assert(initialized_);
    
    for (auto const &actor : actor_list_) {
        if (actor == new_actor) {
            Utils::LogError("ActorManager", "Trying to add an already existing actor");
            return false;
        }
    }
    
    actor_list_.push_back(new_actor);
    return true;
}

