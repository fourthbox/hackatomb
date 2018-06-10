/**
 @file action_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTION_MANAGER_HPP_
#define ACTION_MANAGER_HPP_

#include "actor.hpp"
#include "initiable_object.hpp"
#include "map.hpp"

class Engine;

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
 This class manages all actions that can be taken by an actor.
 Every actor that want to interact with the map and/or other actors, must call a function from this class.
 */
class ActionManager : public InitiableObject {
public:
    void Initialize(Engine &engine);
    
    /**
     Check wheter an actor can move to the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can move there, false otherwise.
     */
    bool CanMove(size_t x, size_t y);
    
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
    void PerformActionOnCrosshair();
    bool Attack(Actor &source, size_t x, size_t y, bool ignore_armor = false);
    void PlayerAction(Action action);

    void Interact(size_t x, size_t y);
            
    void StartAiming();
    void DoNothing();
    
    void ActorMoved();
    void ActorWaited();
    void PlayerDied();
    
    /**
     Check wheter an actor can attack on the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can attack there, false otherwise.
     */
    bool CanAtttack(size_t x, size_t y);
    
    bool ShootAction(Actor &source, size_t x, size_t y);
    
    void MoveUpstairs() { MoveToFloor(true); }
    void MoveDowstairs() { MoveToFloor(false); }
    
    void PerformFloorMapping();
    
    CoordinateOpt SeekPlayer();
    
private:
    Engine *engine_;
    
    /**
     Check wheter an actor can interact with the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can interact there, false otherwise.
     */
    bool CanInteract(size_t x, size_t y);
    void MoveToFloor(bool is_upstairs);

};

#endif /* ACTION_MANAGER_HPP_ */
