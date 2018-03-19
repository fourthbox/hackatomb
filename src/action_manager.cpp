#include "action_manager.hpp"

void ActionManager::Initialize(std::shared_ptr<ActorManager> actor_manager, std::shared_ptr<MapsManager> maps_manager) {
    assert(!initialized_);
    
    // Default the first turn phase to idle
    current_turn_phase_ = TurnPhase::IDLE;
    
    actor_manager_ = actor_manager;
    maps_manager_ = maps_manager;
    
    initialized_ = true;
}

void ActionManager::Moved(Actor_p actor) {
    assert(initialized_);
    
    current_turn_phase_ = TurnPhase::ACTION;
}

bool ActionManager::CanMove(size_t x, size_t y) {
    assert(initialized_);
    
    return maps_manager_->CanMoveToPosition(x, y);
}

bool ActionManager::CanAtttack(size_t x, size_t y) {
    assert(initialized_);
    
    return actor_manager_->GetActorByCoordinates(x, y) != nullptr;
}

bool ActionManager::CanInteract(size_t x, size_t y) {
    assert(initialized_);
    
    return true;
}

