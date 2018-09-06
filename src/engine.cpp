#include "engine.hpp"

#include "game_constants.hpp"
#include "game_utils.hpp"
#include "label_constants.hpp"
#include "monster.hpp"

Engine::Engine() :
start_screen_initialized_ {false},
game_initialized_ {false},
is_playing_ {false},
is_start_screen_first_update_cycle_ {true},
is_main_game_first_update_cycle_ {true} {
    
    // Initialize Root Console Manager
    root_console_manager_.Initialize(kRootViewWidth, kRootViewHeight, "hackatomb");
        
    // Initialize the UI Manager
    ui_manager_.Initialize(items_manager_);
    
    // Set the windows on the root console
    root_console_manager_.SetLeftWindow(ui_manager_.GetEnvironmentWindow());
    root_console_manager_.SetRightWindow(ui_manager_.GetPlayerInfoWindow());
    root_console_manager_.SetBottomWindow(ui_manager_.GetMessageLogWindow());
    root_console_manager_.SetFullScreenWindow(ui_manager_.GetInventoryWindow());
}

void Engine::InitializeStartScreen() {
    assert (!start_screen_initialized_);
    
    // Initialize the Start Screen
    start_screen_.Initialize(this);

    // Add Start Screen to the root console manager
    root_console_manager_.SetStartScreenWindow(start_screen_.GetWindow());
    
    // Initialize Input Manager
    input_manager_.Initialize(aim_manager_, action_manager_, start_screen_, ui_manager_);

    start_screen_initialized_ = true;
}

void Engine::InitializeGame() {
    assert(start_screen_initialized_ && !game_initialized_);
    
    // Initialize the Maps Manager
    maps_manager_.Initialize();
    
    // Initialize the Actor Manager
    actor_manager_.Initialize();
    
    // Initialize the Action Manager
    action_manager_.Initialize(*this);
    
    // Initialize the Player
    actor_manager_.InitializePlayer(maps_manager_.GetRandomLocation(DungeonCategory::NORMAL_, 0));
    
    // Initialize the Monsters
    actor_manager_.InitializeMonsterManager(action_manager_, maps_manager_);
    
    // Populate the dungeon with Monsters
    actor_manager_.PopulateMap(maps_manager_, DungeonCategory::NORMAL_);
    
    // Distribute Items across the dungeon
    // TODO: finish
//    items_manager_.PopulateMap();
    
    Actor *player {&actor_manager_.GetPlayer()};
    
    // Add Stats to Ui for the first time
    assert(ui_manager_.UpdateLabel(kHpString, std::to_string(actor_manager_.GetPlayer().GetHp())));

    // Compute fov the first time
    maps_manager_.ComputeFov(*player);
    
    // Initialize Aim Manager
    aim_manager_.Initialize(player->GetMapLocation().dungeon_category_, player->GetMapLocation().floor_, maps_manager_);
    
    // Everything that needs to be done when no user action has been detected
    turn_manager_.StartTurn();
    
    // Set as initialized
    game_initialized_ = true;
}

void Engine::Update() {
    assert(game_initialized_);
    
    // Only in the very first update iteration, execute a render beforehand
    if (is_main_game_first_update_cycle_) {
        Render();
        is_main_game_first_update_cycle_ = false;
    }
    
    // Checks if a game over has occurred
    if (turn_manager_.GetCurrentTurnPhase() == TurnPhase::GAME_OVER_) {
        GameOver();
    }
    
    // Receive user input
    assert(turn_manager_.GetCurrentTurnPhase() != TurnPhase::ACTION_);
    input_manager_.Update(turn_manager_.GetCurrentTurnPhase());
    
    // Update aiming
    if (turn_manager_.GetCurrentTurnPhase() == TurnPhase::AIM_) {
        aim_manager_.Update(actor_manager_.GetPlayer(), action_manager_, maps_manager_);
    }
    
    if (turn_manager_.GetCurrentTurnPhase() == TurnPhase::ACTION_) {
        // If an action was performed, cycle an update for every speed
        for (auto i {kMinSpeed}; i <= kMaxSpeed; i++) {
            // Update player
            actor_manager_.GetPlayer().Update(i, action_manager_, maps_manager_);
            
            // Update all actors
            actor_manager_.Update(i, action_manager_, maps_manager_);
        }
        
        turn_manager_.StartTurn();
    }
}

void Engine::UpdateStartScreen() {
    assert(start_screen_initialized_);
    
    // Only in the very first update iteration, execute a render beforehand
    if (is_start_screen_first_update_cycle_) {
        RenderStartScreen();
        is_start_screen_first_update_cycle_ = false;
    }

    input_manager_.UpdateStartScreen();
}

void Engine::Render() {
    assert(game_initialized_);
    
    // Get turn phase
    auto turn_phase {turn_manager_.GetCurrentTurnPhase()};
    
    // Draw the crosshair's trail
    // The trail is a tile effect, and therefore must be drawn before the actual crosshair
    if (turn_phase == TurnPhase::AIM_)
        aim_manager_.DrawTrail(*root_console_manager_.main_view_, actor_manager_.GetPlayer().GetMapLocation());

    // ******************************************************************************
    // *** EVERY DRAW CALL ADDING EFFECTS TO THE TILES MUST BE CALLED BEFORE THIS ***
    // ******************************************************************************
    
    // Draw the map
    maps_manager_.Draw(*root_console_manager_.main_view_, actor_manager_.GetPlayer());
    
    // Draw monsters
    actor_manager_.DrawMonsters(*root_console_manager_.main_view_, maps_manager_);
    
    // Draw the player
    actor_manager_.DrawPlayer(*root_console_manager_.main_view_);
    
    // Draw the crosshair's trail
    // The trail is a tile effect, and therefore must be drawn before the actual crosshair
    if (turn_phase == TurnPhase::AIM_)
        aim_manager_.DrawCrosshair(*root_console_manager_.main_view_, actor_manager_.GetPlayer().GetMapLocation());
    
    // ***********************************************************
    // *** EVERY DRAW CALL TO THE UI MUST BE CALLED AFTER THIS ***
    // ***********************************************************

    // Draw the Ui
    ui_manager_.Draw();
    
    // Move the camera
    root_console_manager_.UpdateCameraPosition(actor_manager_.GetPlayer().GetMapLocation(), is_main_game_first_update_cycle_);
    
    // Blit consoles to screen to screen
    root_console_manager_.Render(turn_phase);
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

