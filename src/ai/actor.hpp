/**
 @file actor.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTOR_HPP_
#define ACTOR_HPP_

#include <string>

#include "libpmg.hpp"
#include "libtcod.hpp"

/**
 This struct holds all the stats an actor have
 */
struct Stats {
    int atk_;
    int def_;
    int max_hp_;
    int current_hp_;
    
    Stats() {
    }
    
    Stats (int atk, int def, int max_hp) :
    atk_ {atk},
    def_ {def},
    max_hp_ {max_hp},
    current_hp_ {max_hp} {
    }

};

/**
 This class represent an intelligent entity on a map
 */
class Actor {
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
    void Initialize(size_t x, size_t y, const int &sprite, std::string &name, const TCODColor &color, const Stats &stats);
    
    virtual void Update() = 0;
    
    /**
     Draw the actor onto the selected console
     @param console The console upon which to draw the actor.
     */
    void Draw(std::shared_ptr<TCODConsole> console);
    
    /**
     Sets the position upon which the actor will be.
     There are no checks whether the actor can actually be here.
     @param x The X coordinate.
     @param y The Y coordinate.
     */
    void SetPosition(size_t x, size_t y);
    
    /**
     Gets the current position of the actor.
     @return A libpmg::Location containing the coordinates on the current map.
     */
    libpmg::Location GetPosition();
//    size_t GetAtk();
//    size_t GetDef();
//    void ApplyDmg(size_t dmg);
//    void Die();
    
protected:
    bool initialized_;      /**< Utility switch for initialization security checks. */

private:
    size_t x_, y_;      /**< Location on the current map. */
    uint floor_;        /**< Current floor. */
    int sprite_;        /**< Character used to represent this actor. */
    TCODColor color_;   /**< Color used to represent this actor. */
    std::string name_;       /**< Name of this actor. */
    Stats stats_;       /**< Statsof this actor. */
};

typedef std::shared_ptr<Actor> Actor_p;

#endif /* ACTOR_HPP_ */
