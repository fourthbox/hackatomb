/**
 @file actor.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTOR_HPP_
#define ACTOR_HPP_

#include <string>

#include "initiable_object.hpp"
#include "libtcod.hpp"
#include "stats.hpp"

class ActionManager;
class ActorManager;
class MapsManager;
class PlayerManager;
class Tile;

/**
 This class represent an intelligent entity on a map
 */
class Actor : public InitiableObject {
    friend class ActorManager;
    
public:
    /**
     Initialize this instance.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param sprite The character code to represent this actor.
     @param name The name of the actor.
     @param color The color to represent this actor.
     @param stats The stats for this actor.
     */
    void Initialize(size_t x, size_t y, int const &sprite, std::string const &name, TCODColor const &color, Stats const &stats);
    
    virtual bool Update(size_t speed, ActionManager &action_manager);
    
    /**
     Attempts to perform a dodge.
     @return True if the dodge was succesfully performed, false otherwise.
     */
    bool PerformDodge() const;
        
    /**
     Draw the actor onto the selected console
     @param console The console upon which to draw the actor.
     */
    void Draw(TCODConsole &console);
    
    /**
     Gets the current position of the actor.
     @return A pair containing the coordinates on the current map.
     */
    std::pair<size_t, size_t> GetPosition() const;
    
    int GetFovRadius() const;
    
    inline void MoveToPosition(size_t x, size_t y) { x_ = x; y_ = y; }
    
    inline std::string const &GetName() { return name_; } const;
    
    int GetAttackPower() const;
    float GetDefenseModifier() const;
    size_t GetArmorRating() const;
    void InflictDamage(int total_damage);
    
    bool CanSee(size_t x, size_t y, MapsManager &maps_manager) const;
    bool CanSee(Tile *tile, MapsManager &maps_manager) const;
    bool CanSee(Actor *actor, MapsManager &maps_manager) const;
    
    Actor *GetClosestActorInFov(ActorManager &actor_manager, MapsManager &maps_manager);
    
protected:    
    size_t x_, y_;      /**< Location on the current map. */
    short floor_;        /**< Current floor. */
    std::string map_category_; /**< Current map category */
    int sprite_;        /**< Character used to represent this actor. */
    TCODColor color_;   /**< Color used to represent this actor. */
    std::string name_;  /**< Name of this actor. */
    Stats stats_;       /**< Stats of this actor. */
    
    virtual void Die(ActionManager &action_manager) = 0;
};

#endif /* ACTOR_HPP_ */
