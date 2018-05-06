/**
 @file actor_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTOR_MANAGER_HPP_
#define ACTOR_MANAGER_HPP_

#include <vector>

#include "monster_manager.hpp"
#include "player_manager.hpp"

/**
 This class is responsable for the maangement and initialization of every actor in the loaded game.
 */
class ActorManager : public InitiableObject, public std::enable_shared_from_this<ActorManager> {
public:
    void Initialize();

    /**
     Cycles the actor list and return the actor on the specified coordinates.
     Unless specified, it looks on the current floor only.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return A pointer to the actor if an actor is find, nullptr otherwise.
     */
    Actor *GetActorByCoordinates(size_t x, size_t y);
    
    /**
     Get the list of all the loaded monsters.
     @return A vector of pointers to the monsters.
     */
    std::vector<Monster*> GetMonsterList();
    
    /**
     Call for Update() on every actor in actor_list_
     */
    void Update();
    
    void SetAllMonstersVisible();
    
    void InitializePlayer(std::pair<size_t, size_t> start_position, ActionManager *action_manager, MapsManager *maps_manager);
    inline Player &GetPlayer() { return player_manager_.GetPlayer(); }
    
private:
    std::vector<Actor*> actor_list_;    /**< List containing all the actors in the loaded game */
    PlayerManager player_manager_;     /**< The PlayerManager */
    MonsterManager monster_manager_;     /**< The MonsterManager */
};

#endif /* ACTOR_MANAGER_HPP_ */
