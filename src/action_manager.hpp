/**
 @file action_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTION_MANAGER_HPP_
#define ACTION_MANAGER_HPP_

#include "actor_manager.hpp"
#include "maps_manager.hpp"

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
    void Initialize(std::shared_ptr<ActorManager> actor_manager, std::shared_ptr<MapsManager> maps_manager);
    
    bool CanMove(size_t x, size_t y);
    bool CanAtttack(size_t x, size_t y);
    bool CanInteract(size_t x, size_t y);
    void Moved(std::shared_ptr<Actor> actor);
    
private:
    TurnPhase current_turn_phase_;
    std::shared_ptr<ActorManager> actor_manager_;
    std::shared_ptr<MapsManager> maps_manager_;
};

#endif /* ACTION_MANAGER_HPP_ */
