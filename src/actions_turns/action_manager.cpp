#include "action_manager.hpp"

#include "engine.hpp"
#include "label_constants.hpp"

void ActionManager::Initialize(Engine &engine) {
    
    this->engine_ = &engine;
    
    initialized_ = true;
}

bool ActionManager::CanMove(MapLocation const &location) {
    assert(initialized_);
    
    return engine_->GetMapsManager().IsTileWalkable(location);
}

bool ActionManager::CanAtttack(MapLocation const &location) {
    assert(initialized_);
    
    return engine_->GetActorManager().GetActorByCoordinates(location) != nullptr;
}

bool ActionManager::CanInteract(MapLocation const &location) {
    assert(initialized_);
    
    return engine_->GetMapsManager().IsInteractable(location);
}

void ActionManager::Interact(MapLocation const &location) {
    assert(initialized_);
    
    engine_->GetMapsManager().OpenDoor(location);
}

bool ActionManager::Attack(Actor &source, MapLocation const &location, bool ignore_armor) {
    assert(initialized_);
    
    auto target {engine_->GetActorManager().GetActorByCoordinates(location)};
    
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
    // Log message to console
    engine_->GetUiManager().log_manager_.LogAttack(source, *target, total_damage);

    return true;
}

bool ActionManager::PerformAction(Actor &source, MapLocation const &location) {
    assert(initialized_);
    
    // If the tile is out of the map, exit
    if (!engine_->GetMapsManager().GetTileFromFloor(location))
        return false;
    
    // Check if can be attacked
    if (CanAtttack(location)) {
        Attack(source, location);
        return true;
    } else if (CanInteract(location)) {
        Interact(location);
        return true;
    }
    
    return false;
}

void ActionManager::PerformActionOnCrosshair() {
    assert(initialized_);
    
    auto crosshair_position {engine_->GetAimManager().GetCrosshairLocation()};
    
    // Check if can be attacked
    if (CanAtttack(crosshair_position))
        Attack(engine_->GetActorManager().GetPlayer(), crosshair_position);
    
    // Reset the crosshair
    engine_->GetAimManager().ResetCrosshair();
    
    // Set the turn to action
    engine_->GetTurnManager().ActionPerformed();
}

void ActionManager::MoveToFloor(bool is_upstairs) {
    assert(initialized_);
    
    auto maps_manager {&engine_->GetMapsManager()};
    auto actor_manager {&engine_->GetActorManager()};
    auto player {&engine_->GetActorManager().GetPlayer()};
    auto player_location {player->GetMapLocation()};

    auto stair_position {is_upstairs ?
        maps_manager->GetEntrancePosition(player_location) :
        maps_manager->GetExitPosition(player_location) };

    // Go Upstairs
    if (stair_position && *stair_position == player_location) {
        if (auto new_location {maps_manager->MoveToFloor(*stair_position, is_upstairs)}; new_location)
            player->MoveToLocation(*new_location);
    }
    
    // Update the actors
    actor_manager->NewFloorLoaded(*maps_manager);
            
    // Update UI
    assert(engine_->GetUiManager().UpdateLabel(kFloorLabelId, std::to_string(player->GetMapLocation().floor_+1)));
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
    
    auto player_location {SeekPlayer()};
    
    assert(player_location);
    
    engine_->GetMapsManager().SetAllExplored(player_location->dungeon_category_, player_location->floor_);
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

void ActionManager::OpenInventory() {
    assert(initialized_);
    
    // Change the turn phase
    engine_->GetTurnManager().SwitchToMenuMode();
}

void ActionManager::CloseMenu() {
    assert(initialized_);
    
    // Change the turn phase
    engine_->GetTurnManager().StartTurn();
}

MapLocation_opt ActionManager::SeekPlayer() {
    assert(initialized_);

    return std::experimental::make_optional(engine_->GetActorManager().GetPlayer().GetMapLocation());
}
