#include "engine.hpp"

#include "game_constants.hpp"
#include "game_utils.hpp"
#include "monster.hpp"

Engine::Engine() :
start_screen_initialized_ {false},
game_initialized_ {false},
is_playing_ {false},
is_start_screen_first_update_cycle_ {false},
is_main_game_first_update_cycle_ {false} {
    
    // Initialize Root Console Manager
    root_console_manager_.Initialize(kRootViewWidth, kRootViewHeight, "hackatomb");
    
    // Initialize the UI Manager
    ui_manager_.Initialize();
    
    // Set the window on the root console
    root_console_manager_.SetLeftWindow(ui_manager_.GetEnvironmentWindow());
    root_console_manager_.SetRightWindow(ui_manager_.GetPlayerInfoWindow());
    root_console_manager_.SetBottomWindow(ui_manager_.GetMessageLogWindow());
}

void Engine::InitializeStartScreen() {
    assert (!start_screen_initialized_);
    
    // Initialize the Start Screen
    start_screen_.Initialize(this);

    // Add Start Screen to the root console manager
    root_console_manager_.SetStartScreenWindow(start_screen_.GetWindow());
    
    // Initialize Input Manager
    input_manager_.Initialize(actor_manager_, maps_manager_, start_screen_, aim_manager_, action_manager_);

    start_screen_initialized_ = true;
}

void Engine::InitializeGame() {
    assert(start_screen_initialized_ && !game_initialized_);
    
    // Initialize the Maps Manager
    maps_manager_.Initialize();
    
    // Initialize the Actor Manager
    actor_manager_.Initialize();
    
    // Initialize the Action Manager
    action_manager_.Initialize(actor_manager_, maps_manager_);
    
    // Initialize the Player
    actor_manager_.InitializePlayer(maps_manager_.GetRandomPosition(), action_manager_, maps_manager_);
    
    // Initialize the Monsters
    actor_manager_.InitializeMonsterManager(action_manager_, maps_manager_);
    
    auto &player {actor_manager_.GetPlayer()};
    
    // Compute fov the first time
    maps_manager_.ComputeFov((Actor&)player);
    
    // Attach player to input manager
    input_manager_.SetPlayer(player);
    
    // Initialize Aim Manager
    aim_manager_.Initialize(maps_manager_);
    
    // Everything that needs to be done when no user action has been detected
    action_manager_.StartTurn();
    
    // Set as initialized
    game_initialized_ = true;
}

void Engine::Update() {
    assert(game_initialized_);
    
    // Only in the very first update iteration, execute a render beforehand
    if (!is_main_game_first_update_cycle_) {
        Render();
        is_main_game_first_update_cycle_ = true;
    }
    
    // Checks if a game over has occurred
    if (action_manager_.GetTurnPhase() == TurnPhase::GAME_OVER_) {
        GameOver();
    }
    
    // Receive user input
    input_manager_.Update();
    
    // Update aiming
    if (action_manager_.GetTurnPhase() == TurnPhase::AIM_) {
        aim_manager_.Update(action_manager_, actor_manager_, maps_manager_);
    }
    
    // Cycle an update for every speed
    for (auto i {kMinSpeed}; i <= kMaxSpeed; i++) {
        // Update player
        actor_manager_.GetPlayer().Update(i, action_manager_);
        
        // If an action was performed, update all other actors
        if (action_manager_.GetTurnPhase() == TurnPhase::ACTION_) {
            actor_manager_.Update(i);
        }
    }
    
    if (action_manager_.GetTurnPhase() == TurnPhase::ACTION_)
        action_manager_.StartTurn();
}

void Engine::UpdateStartScreen() {
    assert(start_screen_initialized_);
    
    // Only in the very first update iteration, execute a render beforehand
    if (!is_start_screen_first_update_cycle_) {
        RenderStartScreen();
        is_start_screen_first_update_cycle_ = true;
    }

    input_manager_.UpdateStartScreen();
}

void Engine::Render() {
    assert(game_initialized_);
    
    // Draw the crosshair's trail
    // The trail is a tile effect, and therefore must be drawn before the actual crosshair
    if (action_manager_.GetTurnPhase() == TurnPhase::AIM_)
        aim_manager_.DrawTrail(*root_console_manager_.main_view_, actor_manager_);

    // **********************************************************************
    // EVERY DRAW CALL ADDING EFFECTS TO THE TILES MUST BE CALLED BEFORE THIS
    // **********************************************************************
    
    // Draw the map
    maps_manager_.Draw(*root_console_manager_.main_view_, actor_manager_.GetPlayer());
    
    // Draw monsters
    actor_manager_.DrawMonsters(*root_console_manager_.main_view_);
    
    // Draw the player
    actor_manager_.DrawPlayer(*root_console_manager_.main_view_);
    
    // Draw the crosshair's trail
    // The trail is a tile effect, and therefore must be drawn before the actual crosshair
    if (action_manager_.GetTurnPhase() == TurnPhase::AIM_)
        aim_manager_.DrawCrosshair(*root_console_manager_.main_view_, actor_manager_);

    // Draw the Ui
    ui_manager_.Draw();
    
    // Blit consoles to screen to screen
    root_console_manager_.Render();
}

void Engine::RenderStartScreen() {
    assert(start_screen_initialized_);
    
    // Draw the Ui
    start_screen_.Draw();
    
    // Blit consoles to screen to screen
    root_console_manager_.RenderStartScreen();
}

void Engine::GameOver() {
    is_playing_ = false;
}

