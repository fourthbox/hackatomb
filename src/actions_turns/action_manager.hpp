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
     Set the turn phase to idle mode.
     */
    void ActorMoved();
    
    /**
     Set the turn phase to idle mode.
     */
    void ActorWaited();
    
    /**
     The source actor performs an attack on the specified tile.
     @param source The actor that performs the action.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param ignore_armor If true, it will ignore the defender armor.
     @return True if succesfully performed an action, false otherwise.
     */
    bool Attack(Actor &source, size_t x, size_t y, bool ignore_armor = false);
    
    /**
     Check wheter an actor can attack on the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can attack there, false otherwise.
     */
    bool CanAtttack(size_t x, size_t y);
    
    /**
     Check wheter an actor can move to the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can move there, false otherwise.
     */
    bool CanMove(size_t x, size_t y);
    
    /**
     Set the turn phase to aim mode.
     Use this when no action has been performed.
     To wait/skip a turn use ActorWaited()
     */
    void DoNothing();
    
    /**
     Dispatch an action executed by the player.
     @param action The executed action.
     */
    void Interact(size_t x, size_t y);
    
    /**
     Move the player to the lower floor.
     */
    void MoveDowstairs() { MoveToFloor(false); }
    
    /**
     Move the player to the higher floor.
     */
    void MoveUpstairs() { MoveToFloor(true); }
    
    /**
     Triggers an action form an actor, to the destination coordinate.
     First it checks if it's attackable, and eventually triggers an attack.
     Then if it's interactable, and eventually triggers an interaction.
     @param source The actor that performs the action.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if succesfully performed an action, false otherwise.
     */
    bool PerformAction(Actor &source, size_t x, size_t y);
    
    /**
     Triggers an action form an actor, to the destination under the crosshair.
     */
    void PerformActionOnCrosshair();

    /**
     Dispatch an action executed by the player.
     @param action The executed action.
     */
    void PlayerAction(Action action);

    /**
     Set the turn phase to aim mode.
     */
    void StartAiming();
    
    /**
     Set the turn phase to aim mode.
     @param source The actor that performs the action.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if succesfully performed an action, false otherwise.
     */
    bool ShootAction(Actor &source, size_t x, size_t y);
    
    /**
     Make all tiles explored and all actors visibles.
     */
    void PerformFloorMapping();
    
    /**
     Open the inventory menu.
     */
    void OpenInventory();
    
    /**
     Close any open menu window.
     */
    void CloseMenu();
    
    /**
     Search for the player and return the position.
     @return Player map position.
     */
    MapLocation_opt SeekPlayer();
    
private:
    Engine *engine_;
    
    /**
     Check wheter an actor can interact with the specified coordinates.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if an Actor can interact there, false otherwise.
     */
    bool CanInteract(size_t x, size_t y);
    
    /**
     Move the player to the next flooe.
     @param is_upstairs If true, will move upstairs. If false, will move downstairs.
     */
    void MoveToFloor(bool is_upstairs);

};

#endif /* ACTION_MANAGER_HPP_ */
