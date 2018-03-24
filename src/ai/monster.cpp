#include "monster.hpp"

#include "player.hpp"

void Monster::Update() {
    assert(initialized_);
    
    auto location {path_finder_.Walk(x_,
                                     y_,
                                     actor_manager_->GetPlayer()->GetPosition().first,
                                     actor_manager_->GetPlayer()->GetPosition().second,
                                     0)};
    
    if (location == nullptr)
        return;
    
    x_ = location->first;
    y_ = location->second;
}

void Monster::Initialize(size_t x, size_t y, const int &sprite, std::string &name, const TCODColor &color, const Stats &stats, std::shared_ptr<ActionManager> action_manager, Map_p map) {
    assert(!initialized_);
    
    Actor::Initialize(x, y, sprite, name, color, stats, action_manager);
    path_finder_.Initialize(map);
}
