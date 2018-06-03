#include "action_manager.hpp"

#include "actor_manager.hpp"
#include "game_globals.hpp"
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

void ActionManager::GameOver() {
    assert(initialized_);
    
    current_turn_phase_ = TurnPhase::GAME_OVER;
}

bool ActionManager::CanMove(size_t x, size_t y) {
    assert(initialized_);
    
    return maps_manager_->CanMoveToPosition(x, y) && !CanAtttack(x, y);
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
    
    maps_manager_->OpenDoor(x, y);
}

bool ActionManager::Attack(Actor &source, size_t x, size_t y, bool ignore_armor) {
    assert(initialized_);
    
    auto target {actor_manager_->GetActorByCoordinates(x, y)};
    
    assert(target);
    
    // Check if the target dodges
    if (target->PerformDodge())
        return false;
    
    // Get total damage
    auto total_damage {source.GetAttackPower()};
    
    // Mitigate by the target constitution
    if (!ignore_armor) {
        auto armor_modifier {(float)total_damage * (float)target->GetDefenseModifier()};
        
        auto mitigated_damage {std::floor((float)total_damage - armor_modifier)};
        
        assert(mitigated_damage >= 0.0f);
        
        total_damage = (int)mitigated_damage;
    }
    
    // Subtract from the target armor
    total_damage -= target->GetArmorRating();
    
    if (total_damage <= 0)
        return false;
    
    // Inflicts the damage to the target
    target->InflictDamage(total_damage);
    
    return true;
}

TurnPhase ActionManager::GetTurnPhase() {
    assert(initialized_);

    return current_turn_phase_;
}

bool ActionManager::PerformAction(Actor &source, size_t x, size_t y) {
    assert(initialized_);

    // Check if can be attacked
    if (CanAtttack(x, y)) {
        Attack(source, x, y);
        return true;
    } else if (CanInteract(x, y)) {
        Interact(x, y);
        return true;
    }
    
    return false;
}
