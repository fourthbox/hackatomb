#include "actor.hpp"

#include "action_manager.hpp"
#include "engine.hpp"
#include "game_constants.hpp"

using std::string;

void Actor::Initialize(size_t x, size_t y, int const &sprite, std::string const &name, TCODColor const &color, Stats const &stats) {
    assert(!initialized_);
    
    x_ = x;
    y_ = y;
    sprite_ = sprite;
    name_ = name;
    color_ = color;
    stats_ = stats;
    
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

bool Actor::Update(size_t speed, ActionManager &action_manager) {
    assert(initialized_);

    return stats_.speed_ == speed;
}

bool Actor::PerformDodge() const {
    assert(initialized_);

    return (Engine::GetRandomPercentage() <= stats_.dex_ * kDodgePointsPerDex);
}

int Actor::GetAttackPower() const {
    assert(initialized_);
    
    auto attack_power {stats_.str_};
    
    assert(attack_power < INT_MAX);

    // TODO: add weapon modifier
    return (int) attack_power;
}

float Actor::GetDefenseModifier() const {
    assert(initialized_);
    
    auto def {(float)stats_.con_ * kDefensePointsPerCon};

    return def;
}

size_t Actor::GetArmorRating() const {
    assert(initialized_);

    return 1;
}

void Actor::InflictDamage(int total_damage, ActionManager &action_manager) {
    assert(initialized_);
    
    stats_.current_hp_ -= total_damage;
    
    if (stats_.current_hp_ <= 0)
        Die(action_manager);
}

bool Actor::CanSee(size_t x, size_t y, MapsManager &maps_manager) const {
    assert(initialized_);
    
    maps_manager.ComputeFov(*this);
    
    return maps_manager.IsInFov(x, y);
}

bool Actor::CanSee(Tile *tile, MapsManager &maps_manager) const {
    assert(tile);
    
    return CanSee(tile->GetX(), tile->GetY(), maps_manager);
}

bool Actor::CanSee(Actor *actor, MapsManager &maps_manager) const {
    assert(actor);
    
    return CanSee(actor->GetPosition().first, actor->GetPosition().second, maps_manager);
}

Actor *Actor::GetClosestActorInFov(ActorManager &actor_manager, MapsManager &maps_manager) {
    assert (initialized_);
    
    // Compute fov
    maps_manager.ComputeFov(*this);
    
    // Calculate distance between 2 points
    auto distance = [this] (Actor &actor) -> float {
        auto p1 {GetPosition()}, p2 {actor.GetPosition()};
        
        return sqrt( (p1.first - p2.first) * (p1.first - p2.first) +
                    (p1.second - p2.second) * (p1.second - p2.second) );
    };
    
    auto actor_list {actor_manager.GetAllActors()};
    
    auto shortest_dist {std::numeric_limits<float>::max()};
    Actor *target {nullptr};
    for (auto &actor : actor_list) {
        if (CanSee(actor, maps_manager)) {
            if (auto dist {distance(*actor)}; dist < shortest_dist && dist != 0) {
                shortest_dist = dist;
                target = actor;
            }
        }
    }
    
    return target;
}
