#include "action_manager.hpp"

#include "engine.hpp"
#include "game_strings.hpp"

void ActionManager::Initialize(Engine &engine) {
    
    this->engine_ = &engine;
    
    initialized_ = true;
}

bool ActionManager::CanMove(size_t x, size_t y) {
    assert(initialized_);
    
    return engine_->GetMapsManager().IsTileWalkable(x, y);
}

bool ActionManager::CanAtttack(size_t x, size_t y) {
    assert(initialized_);
    
    return engine_->GetActorManager().GetActorByCoordinates(x, y) != nullptr;
}

bool ActionManager::CanInteract(size_t x, size_t y) {
    assert(initialized_);
    
    return engine_->GetMapsManager().IsInteractable(x, y);
}

void ActionManager::Interact(size_t x, size_t y) {
    assert(initialized_);
    
    engine_->GetMapsManager().OpenDoor(x, y);
}

bool ActionManager::Attack(Actor &source, size_t x, size_t y, bool ignore_armor) {
    assert(initialized_);
    
    auto target {engine_->GetActorManager().GetActorByCoordinates(x, y)};
    
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
    // If false, the target is dead
    if (!target->InflictDamage(total_damage)) {
        if (engine_->GetActorManager().GetPlayer().IsDead())
            engine_->GetTurnManager().GameOver();
    }
    
    // Update UI
    assert(engine_->GetUiManager().UpdateLabel(kHpString,
                                               std::to_string(engine_->GetActorManager().GetPlayer().GetHp())));

    return true;
}

bool ActionManager::PerformAction(Actor &source, size_t x, size_t y) {
    assert(initialized_);
    
    // If the tile is out of the map, exit
    if (!engine_->GetMapsManager().GetTileFromFloor(x, y))
        return false;
    
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

void ActionManager::PerformActionOnCrosshair() {
    assert(initialized_);
    
    auto crosshair_position {engine_->GetAimManager().GetCrosshairLocation()};
    
    // Check if can be attacked
    if (CanAtttack(crosshair_position.first, crosshair_position.second))
        Attack(engine_->GetActorManager().GetPlayer(), crosshair_position.first, crosshair_position.second);
    
    // Reset the crosshair
    engine_->GetAimManager().ResetCrosshair();
    
    // Set the turn to action
    engine_->GetTurnManager().ActionPerformed();
}

void ActionManager::MoveToFloor(bool is_upstairs) {
    assert(initialized_);
    
    auto maps_manager {&engine_->GetMapsManager()};
    auto player {&engine_->GetActorManager().GetPlayer()};

    auto stair_position {is_upstairs ? maps_manager->GetEntrancePosition() : maps_manager->GetExitPosition() };

    // Go Upstairs
    if (stair_position && *stair_position == player->GetPosition()) {
        if (auto new_coors {maps_manager->MoveToFloor(is_upstairs)}; new_coors != std::experimental::nullopt)
            player->MoveToPosition(new_coors->first, new_coors->second);
    }
        
    // Update UI
    assert(engine_->GetUiManager().UpdateLabel(kFloorString,
                                               std::to_string(maps_manager->GetCurrentFloor())));
}

void ActionManager::DoNothing() {
    assert(initialized_);
    
    engine_->GetActorManager().GetPlayer().SetAction(Action::NONE_);
}

void ActionManager::ActorMoved() {
    assert(initialized_);
    
    engine_->GetTurnManager().StartTurn();
}

void ActionManager::ActorWaited() {
    assert(initialized_);
        
    engine_->GetTurnManager().StartTurn();
}

void ActionManager::PlayerAction(Action action) {
    assert(initialized_);
    
    engine_->GetActorManager().GetPlayer().SetAction(action);
    engine_->GetTurnManager().ActionPerformed();
}

void ActionManager::PerformFloorMapping() {
    assert(initialized_);
    
    engine_->GetMapsManager().SetAllExplored();
    engine_->GetActorManager().SetAllMonstersVisible();
}

void ActionManager::StartAiming() {
    assert(initialized_);
    
    // Change the turn phase
    engine_->GetTurnManager().SwitchToAimMode();
    
    // Setup crosshair for arrows
    engine_->GetAimManager().SetupCrossshair(CrosshairMode::ARROW_,
                                             engine_->GetActorManager().GetPlayer().GetFovRadius(),
                                             engine_->GetActorManager().GetPlayer(),
                                             engine_->GetActorManager().GetAllActors(),
                                             engine_->GetMapsManager());
}

CoordinateOpt ActionManager::SeekPlayer() {
    assert(initialized_);

    return std::experimental::make_optional(engine_->GetActorManager().GetPlayer().GetPosition());
}
