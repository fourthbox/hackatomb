#include "engine.hpp"

#include <cassert>

#include "libtcod.hpp"
#include "game_constants.hpp"
#include "game_utils.hpp"

typedef std::shared_ptr<Actor> Actor_p;
typedef std::shared_ptr<Map> Map_p;

Engine::Engine() :
    initialized_ {false}
{}

void Engine::Initialize(std::shared_ptr<libpmg::DungeonMap> map, Player_p player) {
    if (initialized_) {
        Utils::LogWarning("Engine", "Engine already initialized.");
        return;
    }
    
    InitEngine();
    InitUi();
    
    // Initialize the map
    auto new_map {std::make_unique<Map>(map)};
    
    // Configure the map keys
    current_map_category_ = "main_dungeon";
    current_floor_ = 0;

    // Add first map to dungeon
    maps_manager_.AddMapToMaster(std::move(new_map), current_map_category_, current_floor_);
    
    // Add the player
    this->player_ = player;
    
    // Set as initialized
    initialized_ = true;

    // Compute fov the first time
    ComputeFov();
}

void Engine::Initialize(std::shared_ptr<libpmg::WorldMap> map) {
    if (initialized_) {
        Utils::LogWarning("Engine", "Engine already initialized.");
        return;
    }
    
    InitEngine();
    
    // Add the world map
    world_map_ = std::make_unique<World>(map);
    
    // Set as initialized
    initialized_ = true;
}

void Engine::InitEngine() {
    if (initialized_) {
        Utils::LogWarning("Engine", "Engine already initialized.");
        return;
    }
    
    // Initialize Root Console Manager
    root_console_manager_.Initialize(kRootViewWidth, kRootViewHeight,
                                     kEnvironmentConsoleWidth, kPlayerInfoConsoleWidth,
                                     0, kMessageLogConsoleHeight, "hackatomb");
    
    // Initialize the Maps Manager
    maps_manager_.Initialize();
}

void Engine::InitUi() {
    if (initialized_) {
        Utils::LogWarning("Engine", "Engine already initialized.");
        return;
    }
        
    // Initialize the UI Manager
    ui_manager_.Initialize();
    
    // Set the window on the root console
    root_console_manager_.SetLeftWindow(ui_manager_.environment_window_);
    root_console_manager_.SetRightWindow(ui_manager_.player_info_window_);
    root_console_manager_.SetBottomWindow(ui_manager_.message_log_window_);
}


void Engine::Update() {
    assert(initialized_);
        
    // Idle phase.
    // Everything that needs to be done when no user action has been detected
    game_status_ = TurnPhase::IDLE;
    
    player_->Update();
    
    for (auto const &actor : actor_list_) {
        actor->Update();
    }
}

void Engine::Render() {
    assert(initialized_);
    
    // Draw the map
    maps_manager_.Draw(current_map_category_, current_floor_, root_console_manager_.main_view_);
    
    // Draw the player
    player_->Draw(root_console_manager_.main_view_);

    // Draw monsters
    for (auto const &actor : actor_list_) {
        if (maps_manager_.IsInFov(actor->GetPosition().GetX(),
                                  actor->GetPosition().GetY(),
                                  current_map_category_,
                                  current_floor_))
            actor->Draw(root_console_manager_.main_view_);
    }

    // Draw the Ui
    ui_manager_.Draw();
    
    // Draw to screen
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


bool Engine::CanMoveToPosition(size_t x, size_t y) {
    assert(initialized_);

    return maps_manager_.CanMoveToPosition(x, y, current_map_category_, current_floor_);
}

void Engine::ComputeFov() {
    assert(initialized_);

    maps_manager_.ComputeFov(player_, current_map_category_, current_floor_);
}

Actor_p Engine::GetActor(size_t x, size_t y) {
    assert(initialized_);

    for (auto const &actor : actor_list_) {
        if (actor->GetPosition().GetX() == x && actor->GetPosition().GetY() == y)
            return actor;
    }
    
    return nullptr;
}

void Engine::AddMonster(Actor_p monster) {
    assert(initialized_);

    actor_list_.push_back(monster);
}
