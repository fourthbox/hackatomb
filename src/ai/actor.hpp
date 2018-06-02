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
     @param action_manager Reference to the ActionManager.
     @param maps_manager Reference to the MapsManager
     */
    void Initialize(size_t x, size_t y, int const &sprite, std::string const &name, TCODColor const &color, Stats const &stats, ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager);
    
    virtual bool Update(size_t speed);
    
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
    
    size_t GetAttackPower() const;
    float GetDefenseModifier() const;
    size_t GetArmorRating() const;
    void InflictDamage(size_t total_damage);
    
protected:
    ActionManager *action_manager_;     /**< Pointer to the ActionManager */
    ActorManager *actor_manager_;       /**< Pointer to the ActionManaer */
    MapsManager *maps_manager_;         /**< Pointer to the MapsManager */
    
    size_t x_, y_;      /**< Location on the current map. */
    uint floor_;        /**< Current floor. */
    std::string map_category_; /**< Current map category */
    int sprite_;        /**< Character used to represent this actor. */
    TCODColor color_;   /**< Color used to represent this actor. */
    std::string name_;  /**< Name of this actor. */
    Stats stats_;       /**< Stats of this actor. */
    
    virtual void Die() = 0;
};

#endif /* ACTOR_HPP_ */
