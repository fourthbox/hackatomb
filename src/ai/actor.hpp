/**
 @file actor.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTOR_HPP_
#define ACTOR_HPP_

#include <string>

#include "map_entity.hpp"
#include "stats.hpp"

class ActionManager;
class ActorManager;
class MapsManager;
class PlayerManager;
class Tile;

/**
 This class represent an intelligent entity on a map
 */
class Actor : public MapEntity {
    friend class ActorManager;
    
public:
    /**
     Draw the actor onto the selected console
     @param console The console upon which to draw the actor.
     */
    void Draw(TCODConsole &console);

    /**
     Initialize this instance.
     @param map_location The map location.
     @param sprite The character code to represent this actor.
     @param name The name of the actor.
     @param color The color to represent this actor.
     @param stats The stats for this actor.
     */
    void Initialize(MapLocation const &map_location, int const &sprite, std::string const &name, TCODColor const &color, Stats const &stats);
    
    /**
     Inflicts the specified damage to the actor. Check if it dies afterwards.
     @param total_damage The total damage inflicted to the actor
     @return True if the actor survived the damage, false otherwise
     */
    bool InflictDamage(int total_damage);
    
    /**
     Move the actor to the specified location.
     @param location The map location.
     */
    void MoveToLocation(MapLocation const &location);
    
    /**
     Attempts to perform a dodge.
     @return True if the dodge was succesfully performed, false otherwise.
     */
    bool PerformDodge() const;

    /**
     Update cycle.
     @param speed The speed for this update cycle.
     @param action_manager The actor manager.
     @param maps_manager The maps manager.
     */
    virtual bool Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager);
    
    
    // Getters
    int GetFovRadius() const;
    int GetHp() const;
    int GetAttackPower() const;
    float GetDefenseModifier() const;
    size_t GetArmorRating() const;
    inline bool IsDead() { return is_dead_; } const;
    
    /**
     Get the closest actor in fov, if any, nullptr utherwise.
     @param actor_list The actor list to check inside of the fov.
     @param maps_manager The maps_manager
     @return The closest actor in fov, if any, nullptr utherwise.
     */
    Actor *GetClosestActorInFov(std::vector<Actor*> actor_list, MapsManager &maps_manager);
    
    /**
     Get the closest actor in a given range, if any, nullptr utherwise.
     @param actor_list The actor list to check inside of the fov.
     @param range The range of needed to check.
     @param maps_manager The maps manager.
     @return The closest actor in fov, if any, nullptr utherwise.
     */
    Actor *GetClosestActorInRange(std::vector<Actor*> actor_list, size_t range, MapsManager &maps_manager);
    
protected:
    Stats stats_;       /**< Stats of this actor. */
    bool is_dead_;
    
    virtual void Die();
};

#endif /* ACTOR_HPP_ */
