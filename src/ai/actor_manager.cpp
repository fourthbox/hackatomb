#include "actor_manager.hpp"

typedef std::shared_ptr<Actor> p_Actor;

p_Actor ActorManager::GetActorByCoordinates(std::size_t x, std::size_t y, std::string map_category, uint floor) {
    for (auto const &actor : actor_list_) {
        if (actor->GetPosition().GetX() == x && actor->GetPosition().GetY() == y) {
//            if (map_category.empty() && )
        }
    }
    
    return nullptr;
}
