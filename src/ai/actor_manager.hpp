/**
 @file actor_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTOR_MANAGER_HPP_
#define ACTOR_MANAGER_HPP_

#include <vector>

#include "actor.hpp"

class Player;

/**
 This class is responsable for the maangement and initialization of every actor in the loaded game.
 */
class ActorManager : public InitiableObject, public std::enable_shared_from_this<ActorManager> {
public:
    ActorManager();
    void Initialize();

    /**
     Cycles the actor list and return the actor on the specified coordinates.
     Unless specified, it looks on the current floor only.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return A pointer to the actor if an actor is find, nullptr otherwise.
     */
    Actor_p GetActorByCoordinates(size_t x, size_t y);
    
    /**
     Get the list of all the loaded actors.
     @return A vector of pointers to the actors.
     */
    std::vector<std::shared_ptr<Actor>>& GetActorList();
    
    /**
     Add an actor to the actor list performing a check for dupluicates.
     @param new_actor A pointer to the actor to add.
     @return True if the Actor was succesfully added, false otherwise.
     */
    bool AddActor(Actor_p new_actor);
    
    void AddPlayer(std::shared_ptr<Player> player);
    std::shared_ptr<Player> GetPlayer();

    /**
     Call for Update() on every actor in actor_list_
     */
    void Update();
        
private:
    std::vector<Actor_p> actor_list_;    /**< List containing all the actors in the loaded game */
    std::shared_ptr<Player> player_;                   /**< Pointer to the player. */
    
};

typedef std::shared_ptr<ActorManager> ActorManager_p;

#endif /* ACTOR_MANAGER_HPP_ */
