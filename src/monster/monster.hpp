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
     Initialize this instance.
     @param map_location The map location.
     @param stats The stats for this actor.
     @param maps_manager The maps manager
     */
    void Initialize(MapLocation const &map_location, MonsterStats const &stats, MapsManager &maps_manager);
    
    /**
     Check if the monster is always visible.
     @return True if it's always visible, false otherwise.
     */
    bool IsPermaVisible();
    
    /**
     Toggle the monster to be always visible.
     @param is_perma_visible If true will be visible.
     */
    void TogglePermaVisible(bool is_perma_visible);

    /**
     Update the player based on the action.
     @param speed The speed of this update cycle.
     @param action_manager The action manager.
     @param maps_manager The maps manager.
     */
    bool Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager) override;
    
private:
    PathFinder path_finder_;
    bool is_perma_visible_;
    
    /**
     Change the status, the sprite and the color fo the moster to dead.
     */
    void Die() override;
};

#endif /* MONSTER_HPP_ */
