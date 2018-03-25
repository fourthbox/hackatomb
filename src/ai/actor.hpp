/**
 @file actor.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTOR_HPP_
#define ACTOR_HPP_

#include <string>

#include "initiable_object.hpp"
#include "libtcod.hpp"

/**
 This struct holds all the stats an actor have
 */
struct Stats {
    int atk_;
    int def_;
    int max_hp_;
    int current_hp_;
    int fov_;
    
    Stats() {
    }
    
    Stats (int atk, int def, int max_hp, int fov) :
    atk_ {atk},
    def_ {def},
    max_hp_ {max_hp},
    current_hp_ {max_hp},
    fov_ {fov} {
    }

};

class ActionManager;
class ActorManager;
class MapsManager;

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
     @param action_manager A pointer to the ActionManager.
     */
    void Initialize(size_t x, size_t y, const int &sprite, std::string &name, const TCODColor &color, const Stats &stats, std::shared_ptr<ActionManager> action_manager, std::shared_ptr<MapsManager> maps_manager);
    
    virtual void Update() = 0;
    
    /**
     Draw the actor onto the selected console
     @param console The console upon which to draw the actor.
     */
    void Draw(std::shared_ptr<TCODConsole> console);
    
    /**
     Gets the current position of the actor.
     @return A pair containing the coordinates on the current map.
     */
    std::pair<size_t, size_t> GetPosition();
    
    int GetFovRadius();
    
    // This is only a temporary solution, because the actor manager should manage the initialization and instantiation of the actors, passing itself as a parameter.
    void SetActorManager(std::shared_ptr<ActorManager> am) {actor_manager_ = am;}
        
protected:
    std::shared_ptr<ActionManager> action_manager_;     /**< Pointer to the ActionManager */
    std::shared_ptr<ActorManager> actor_manager_;       /**< Pointer to the ActionManaer */
    std::shared_ptr<MapsManager> maps_manager_;         /**< Pointer to the MapsManager */
    
    size_t x_, y_;      /**< Location on the current map. */
    uint floor_;        /**< Current floor. */
    std::string map_category_; /**< Current map category */
    int sprite_;        /**< Character used to represent this actor. */
    TCODColor color_;   /**< Color used to represent this actor. */
    std::string name_;  /**< Name of this actor. */
    Stats stats_;       /**< Statsof this actor. */
};

typedef std::shared_ptr<Actor> Actor_p;

#endif /* ACTOR_HPP_ */
