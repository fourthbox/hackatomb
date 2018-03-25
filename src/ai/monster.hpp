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
     @param action_manager A pointer to the ActionManager.
     @param maps_manager A pointer to the MapManager.
     */
    void Initialize(size_t x, size_t y, const int &sprite, std::string &name, const TCODColor &color, const Stats &stats, std::shared_ptr<ActionManager> action_manager, MapsManager_p maps_manager);

private:
    PathFinder path_finder_;
};

#endif /* MONSTER_HPP_ */
