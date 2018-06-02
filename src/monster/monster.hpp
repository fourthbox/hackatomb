/**
 @file monster.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include "actor.hpp"
#include "path_finder.hpp"

class Monster : public Actor {
public:
    /**
     Update the player based on the action.
     */
    void Update() override;
    
    /**
     Initialize this instance.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param sprite The character code to represent this actor.
     @param name The name of the actor.
     @param color The color to represent this actor.
     @param stats The stats for this actor.
     @param action_manager Reference to the ActionManager.
     @param maps_manager Reference to the MapManager.
     */
    void Initialize(size_t x, size_t y, int const &sprite, std::string const &name, TCODColor const &color, Stats const &stats, ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager);
    
    bool IsPermaVisible();
    void SetPermaVisible(bool is_perma_visible);

private:
    PathFinder path_finder_;
    bool is_perma_visible_;
};

#endif /* MONSTER_HPP_ */
