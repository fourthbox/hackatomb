#include "engine.hpp"

#include "game_constants.hpp"
#include "game_utils.hpp"
#include "monster.hpp"

Engine::Engine() {
    action_manager_ = std::make_shared<ActionManager>();
    actor_manager_ = std::make_shared<ActorManager>();
    maps_manager_ = std::make_shared<MapsManager>();
}

void Engine::Initialize(libpmg::DungeonMap &map, Player_p player) {
    if (initialized_) {
        Utils::LogWarning("Engine", "Engine already initialized.");
        return;
    }
    
    // Initialize Root Console Manager
    root_console_manager_.Initialize(kRootViewWidth, kRootViewHeight, "hackatomb");
    
    // Initialize the Maps Manager
    maps_manager_->Initialize();
    
    // Initialize the Actor Manager
    actor_manager_->Initialize();

    // Initialize the UI Manager
    ui_manager_.Initialize();
    
    // Set the window on the root console
    root_console_manager_.SetLeftWindow(ui_manager_.environment_window_);
    root_console_manager_.SetRightWindow(ui_manager_.player_info_window_);
    root_console_manager_.SetBottomWindow(ui_manager_.message_log_window_);

    // Initialize the map
    auto new_map {std::make_unique<Map>(map)};
    
    // Configure the map keys
    std::string current_map_category {"main_dungeon"};
    auto current_floor {0};

    // Add first map to dungeon
    maps_manager_->AddMapToMaster(std::move(new_map), current_map_category, current_floor);
    // Set the map manager to be in the current map
    maps_manager_->current_map_category_ = current_map_category;
    maps_manager_->current_floor_ = current_floor;
    
    // Add the player
    actor_manager_->AddPlayer(player);
    
    // Initialize the Action Manager
    action_manager_->Initialize(actor_manager_, maps_manager_);
    
    // Initialize Input Manager
    input_manager_.Initialize(player);
    
    // Compute fov the first time
    maps_manager_->ComputeFov(player);

    // Set as initialized
    initialized_ = true;
}

//void Engine::Initialize(std::shared_ptr<libpmg::WorldMap> map) {
//    if (initialized_) {
//        Utils::LogWarning("Engine", "Engine already initialized.");
//        return;
//    }
//
////    InitEngine();
////
////    // Add the world map
////    world_map_ = std::make_unique<World>(map);
//    
//    // Set as initialized
//    initialized_ = true;
//}

void Engine::Update() {
    assert(initialized_);
        
    // Idle phase.
    // Everything that needs to be done when no user action has been detected
    action_manager_->StartTurn();

    input_manager_.Update();
    
    actor_manager_->GetPlayer()->Update();
    
    if (action_manager_->GetTurnPhase() == TurnPhase::ACTION)
        actor_manager_->Update();
}

void Engine::Render() {
    assert(initialized_);
    
    // Draw the map
    maps_manager_->Draw(root_console_manager_.main_view_, actor_manager_->GetPlayer());
    
    // Draw the player
    actor_manager_->GetPlayer()->Draw(root_console_manager_.main_view_);

    // Draw monsters
    for (auto const &monster : actor_manager_->GetMonsterList()) {
        if (monster->IsVisible() || maps_manager_->IsInFov(monster->GetPosition().first, monster->GetPosition().second))
            monster->Draw(root_console_manager_.main_view_);
    }

    // Draw the Ui
    ui_manager_.Draw();
    
    // Blit consoles to screen to screen
    root_console_manager_.Render();
}

void Engine::RenderWorld() {
    assert(initialized_);
    
    // Clear the screen
//    root_console_manager_.Clear();
    
    // Draw the map
    world_map_->Draw();
    
    // Draw to screen
    root_console_manager_.Render();
}

void Engine::AddMonster(Actor_p monster) {
    assert(initialized_ && actor_manager_->AddActor(monster));
}
