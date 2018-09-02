#include "actor.hpp"

#include "action_manager.hpp"
#include "engine.hpp"
#include "game_constants.hpp"

using std::string;

void Actor::Initialize(MapLocation const &map_location, int const &sprite, std::string const &name, TCODColor const &color, Stats const &stats) {
    assert(!initialized_);
    
    map_location_ = map_location;
    sprite_ = sprite;
    name_ = name;
    color_ = color;
    stats_ = stats;
    is_dead_ = false;
    
    initialized_ = true;
}

int Actor::GetFovRadius() const {
    assert(initialized_);
    
    return stats_.fov_;
}

int Actor::GetHp() const {
    assert(initialized_);
    
    return stats_.current_hp_;
}

void Actor::Draw(TCODConsole &console) {
    assert(initialized_);

    console.setChar(map_location_.x_, map_location_.y_, sprite_);
    console.setCharForeground(map_location_.x_, map_location_.y_, color_);
}

bool Actor::Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager) {
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

// Return false if dead
bool Actor::InflictDamage(int total_damage) {
    assert(initialized_);
    
    stats_.current_hp_ -= total_damage;
    
    if (stats_.current_hp_ <= 0) {
        Die();
        return false;
    }
    
    return true;
}

Actor *Actor::GetClosestActorInFov(std::vector<Actor*> actor_list, MapsManager &maps_manager) {
    return GetClosestActorInRange(actor_list, GetFovRadius(), maps_manager);
};

Actor *Actor::GetClosestActorInRange(std::vector<Actor*> actor_list, size_t range, MapsManager &maps_manager) {
    assert (initialized_);
    
    // Calculate distance between 2 points
    auto distance = [this] (Actor &actor) -> float {
        auto p1 {GetPosition()}, p2 {actor.GetPosition()};
        
        return sqrt( (p1.first - p2.first) * (p1.first - p2.first) +
                    (p1.second - p2.second) * (p1.second - p2.second) );
    };
    
    auto shortest_dist {std::numeric_limits<float>::max()};
    Actor *target {nullptr};
    for (auto &actor : actor_list) {
        if (maps_manager.IsInFov(*this, actor->GetMapLocation())) {
            if (auto dist {distance(*actor)};
                dist < shortest_dist
                && dist != 0
                && dist <= range) {
                
                shortest_dist = dist;
                target = actor;
            }
        }
    }

    return target;
}

void Actor::Die() {
    is_dead_ = true;
}
