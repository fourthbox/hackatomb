/**
 @file action_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTION_MANAGER_HPP_
#define ACTION_MANAGER_HPP_

#include "initiable_object.hpp"

class Actor;
class ActorManager;
class MapsManager;

/**
 Enumerator that holds the possible actions performable by an actor
 */
enum struct Action {
    NONE_,
    MOVE_N_,
    MOVE_NE_,
    MOVE_E_,
    MOVE_SE_,
    MOVE_S_,
    MOVE_SW_,
    MOVE_W_,
    MOVE_NW_,
    SKIP
};

/**
 Enumerator that defines the phases of the turn.
 */
enum struct TurnPhase {
    IDLE_,   /**< The game is idle. Waiting for a player input to procede. */
    ACTION_, /**< The player has performed an action. Every actor will perform an action. */
    GAME_OVER_, /**< The game is over. Show game over screen */
    AIM_ /**< The game is in aim mode. */
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
    void Initialize(ActorManager &actor_manager, MapsManager &maps_manager);
    
    /**
     Check wheter an actor can move to the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can move there, false otherwise.
     */
    bool CanMove(size_t x, size_t y);
    
    
    /**
     Signals that an actor moved in the specified position, setting the current_turn_phase_ to ACTION_.
     */
    void ActionPerformed();
    
    /**
     Triggers an action form an actor, to the destination coordinate.
     First it checks if it's attackable, and triggers an attack.
     Then if it's interactable, and triggers an interaction.
     @param source The actor that performs the action
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if succesfully performed an action, false otherwise.
     */
    bool PerformAction(Actor &source, size_t x, size_t y);
    bool Attack(Actor &source, size_t x, size_t y, bool ignore_armor = false);

    void Interact(size_t x, size_t y);
    
    void StartTurn();
    
    void GameOver();
    
    TurnPhase GetTurnPhase() const;
    
    void SwitchToAimMode();
    
    /**
     Check wheter an actor can attack on the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can attack there, false otherwise.
     */
    bool CanAtttack(size_t x, size_t y);
    
    bool ShootAction(Actor &source, size_t x, size_t y);
    
private:
    TurnPhase current_turn_phase_;                  /**< Keeps the current turn phase */
    ActorManager *actor_manager_;                   /**< Pointer to the ActorManager */
    MapsManager *maps_manager_;                     /**< Pointer to the MapsManager */
    
    /**
     Check wheter an actor can interact with the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can interact there, false otherwise.
     */
    bool CanInteract(size_t x, size_t y);

};

#endif /* ACTION_MANAGER_HPP_ */
