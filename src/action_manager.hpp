/**
 @file action_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTION_MANAGER_HPP_
#define ACTION_MANAGER_HPP_

#include "actor_manager.hpp"
#include "maps_manager.hpp"

/**
 Enumerator that holds the possible actions performable by an actor
 */
enum struct Action {
    NONE,
    MOVE_N,
    MOVE_NE,
    MOVE_E,
    MOVE_SE,
    MOVE_S,
    MOVE_SW,
    MOVE_W,
    MOVE_NW
};

/**
 Enumerator that defines the phases of the turn.
 */
enum struct TurnPhase {
    IDLE,   /**< The game is idle. Waiting for a player input to procede. */
    ACTION  /**< The player has performed an action. Every actor will perform an action. */
};

/**
 This class manages all actions that can be taken by an actor.
 Every actor that want to interact with the map and/or other actors, must call a function from this class.
 */
class ActionManager : public InitiableObject {
public:
    /**
     Initialize this instance of the class.
     @param actor_manager A pointer to the ActorManager.
     @param maps_manager A pointer to the MapsManager.
     */
    void Initialize(std::shared_ptr<ActorManager> actor_manager, std::shared_ptr<MapsManager> maps_manager);
    
    /**
     Check wheter an actor can move to the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can move there, false otherwise.
     */
    bool CanMove(size_t x, size_t y);
    
    /**
     Check wheter an actor can attack on the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can attack there, false otherwise.
     */
    bool CanAtttack(size_t x, size_t y);
    
    /**
     Check wheter an actor can interact with the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can interact there, false otherwise.
     */
    bool CanInteract(size_t x, size_t y);
    
    /**
     Signals that an actor moved in the specified position, setting the current_turn_phase_ to ACTION.
     @param actor A pointer to the actor.
     */
    void Moved(std::shared_ptr<Actor> actor);
    
private:
    TurnPhase current_turn_phase_;                  /**< Keeps the current turn phase */
    std::shared_ptr<ActorManager> actor_manager_;   /**< Pointer to the ActorManager */
    std::shared_ptr<MapsManager> maps_manager_;     /**< Pointer to the MapsManager */
};

#endif /* ACTION_MANAGER_HPP_ */
