/**
 @file actor_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTOR_MANAGER_HPP_
#define ACTOR_MANAGER_HPP_

#include <vector>

#include "actor.hpp"

/**
 This class is responsable for the maangement and initialization of every actor in the loaded game.
 */
class ActorManager {
public:
    /**
     Cycles the actor list and return the actor on the specified coordinates.
     Unless specified, it looks on the current floor only.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param map_category The map category upon which the actor is. If left mpty, will use the current map category.
     @param floor The floor category upon which the actor is. If set to -1, will use the current floor.
     @return A pointer to the actor if an actor is find, nullptr otherwise.
     */
    std::shared_ptr<Actor> GetActorByCoordinates(std::size_t x, std::size_t y, std::string map_category = "", uint floor = -1);
    
private:
    std::vector<std::shared_ptr<Actor>> actor_list_;    /**< List containing all the actors in the loaded game */
    
};

#endif /* ACTOR_MANAGER_HPP_ */
