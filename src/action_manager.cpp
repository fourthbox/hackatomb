#include "action_manager.hpp"

#include "actor_manager.hpp"
#include "maps_manager.hpp"

void ActionManager::Initialize(ActorManager &actor_manager, MapsManager &maps_manager) {
    assert(!initialized_);
    
    // Default the first turn phase to idle
    current_turn_phase_ = TurnPhase::IDLE_;
    
    actor_manager_ = &actor_manager;
    maps_manager_ = &maps_manager;
    
    initialized_ = true;
}

void ActionManager::ActionPerformed() {
    assert(initialized_);
    
    current_turn_phase_ = TurnPhase::ACTION_;
}

void ActionManager::StartTurn() {
    assert(initialized_);
    
    current_turn_phase_ = TurnPhase::IDLE_;
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
    
    return maps_manager_->IsInteractable(x, y);
}

void ActionManager::Interact(size_t x, size_t y) {
    assert(initialized_);
    
    return maps_manager_->OpenDoor(x, y);
}

TurnPhase ActionManager::GetTurnPhase() {
    assert(initialized_);

    return current_turn_phase_;
}

