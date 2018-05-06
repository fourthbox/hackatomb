#include "engine.hpp"

#include "game_constants.hpp"
#include "game_utils.hpp"
#include "monster.hpp"

Engine::Engine() :
is_playing_ {false} {
    
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
    input_manager_.Initialize(actor_manager_, maps_manager_, start_screen_);

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
    
    auto &player {actor_manager_.GetPlayer()};
    
    // Compute fov the first time
    maps_manager_.ComputeFov((Actor&)player);
    
    // Attach player to input manager
    input_manager_.SetPlayer(player);
    
    // Set as initialized
    game_initialized_ = true;
}

void Engine::Update() {
    assert(game_initialized_);
        
    // Idle phase.
    // Everything that needs to be done when no user action has been detected
    action_manager_.StartTurn();

    input_manager_.Update();
    
    actor_manager_.GetPlayer().Update();
        
    if (action_manager_.GetTurnPhase() == TurnPhase::ACTION_)
        actor_manager_.Update();
}

void Engine::UpdateStartScreen() {
    assert(start_screen_initialized_);
    
    input_manager_.UpdateStartScreen();
}

void Engine::Render() {
    assert(game_initialized_);
    
    // Draw the map
    maps_manager_.Draw(*root_console_manager_.main_view_.get(), actor_manager_.GetPlayer());
    
    // Draw the player
    actor_manager_.GetPlayer().Draw(*root_console_manager_.main_view_.get());
    
    // Draw monsters
    for (auto const &monster : actor_manager_.GetMonsterList()) {
        if (monster->IsVisible() || maps_manager_.IsInFov(monster->GetPosition().first, monster->GetPosition().second))
            monster->Draw(*root_console_manager_.main_view_.get());
    }
    
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
