#include "actor.hpp"

#include "action_manager.hpp"
#include "engine.hpp"
#include "game_constants.hpp"

using std::string;

void Actor::Initialize(size_t x, size_t y, int const &sprite, std::string const &name, TCODColor const &color, Stats const &stats, ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager) {
    assert(!initialized_);
    
    x_ = x;
    y_ = y;
    sprite_ = sprite;
    name_ = name;
    color_ = color;
    stats_ = stats;
    action_manager_ = &action_manager;
    actor_manager_ = &actor_manager;
    maps_manager_ = &maps_manager;
        
    initialized_ = true;
}

int Actor::GetFovRadius() const {
    assert(initialized_);
    
    return stats_.fov_;
}

void Actor::Draw(TCODConsole &console) {
    assert(initialized_);

    console.setChar(x_, y_, sprite_);
    console.setCharForeground(x_, y_, color_);
}

std::pair<size_t, size_t> Actor::GetPosition() const {
    assert(initialized_);
    
    return std::make_pair(x_, y_);
}

bool Actor::Update(size_t speed) {
    assert(initialized_);

    return stats_.speed_ == speed;
}

bool Actor::PerformDodge() const {
    assert(initialized_);

    return (Engine::GetRandomPercentage() <= stats_.dex_ * kDodgePointsPerDex);
}

size_t Actor::GetAttackPower() const {
    assert(initialized_);

    // TODO: add weapon modifier
    return stats_.str_;
}

float Actor::GetDefenseModifier() const {
    assert(initialized_);

    return (float)stats_.con_ * kDefensePointsPerCon;
}

size_t Actor::GetArmorRating() const {
    assert(initialized_);

    return 1;
}

void Actor::InflictDamage(size_t total_damage) {
    assert(initialized_);
    
    stats_.current_hp_ -= total_damage;
    
    if (stats_.current_hp_ <= 0)
        Die();
}
