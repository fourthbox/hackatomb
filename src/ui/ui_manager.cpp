#include "ui_manager.hpp"

#include <cassert>

#include "game_constants.hpp"

UiManager::UiManager() : initialized_ {false}
{}

void UiManager::Initialize() {
    InitializeEnvironmentWindow();
    InitializePlayerInfoWindow();
    InitializeMessageLogWindow();
    
    initialized_ = true;
}

void UiManager::InitializeEnvironmentWindow() {
    // Initialize labels
    auto floor_label { UiLabel(2, 5, "floor:", "floor_label") };
    auto environment_label { UiLabel(2, 8, "environment:", "environment_label") };
    auto temperature_label { UiLabel(2, 11, "temperature:", "temperature_label") };
    
    // Initialize the window
    environment_window_ = new UiWindow(kEnvironmentConsoleWidth,
                                       kEnvironmentConsoleHeight,
                                       "environment",
                                       {floor_label, environment_label, temperature_label} );
}

void UiManager::InitializePlayerInfoWindow() {
    // Initialize labels
    auto floor_label { UiLabel(2, 5, "floor:", "floor_label") };
    auto environment_label { UiLabel(2, 8, "environment:", "environment_label") };
    auto temperature_label { UiLabel(2, 11, "temperature:", "temperature_label") };

    player_info_window_ = new UiWindow(kPlayerInfoConsoleWidth,
                                       kPlayerInfoConsoleHeight,
                                       "player_name");
}

void UiManager::InitializeMessageLogWindow() {
    message_log_window_ = new UiWindow(kRootViewWidth,
                                       kMessageLogConsoleHeight,
                                       "log");
}

void UiManager::Draw() {
    assert(initialized_);
    
    // Blit the environment_console console on the root console
    auto environment_console {environment_window_->Draw()};
    TCODConsole::blit(environment_console, 0, 0, 0, 0,
                      TCODConsole::root, 0, 0);
    
    // Blit the environment_console console on the root console
    auto player_info_console {player_info_window_->Draw()};
    TCODConsole::blit(player_info_console, 0, 0, 0, 0,
                      TCODConsole::root, TCODConsole::root->getWidth() - kPlayerInfoConsoleWidth, 0);

    // Blit the environment_console console on the root console
    auto message_log_console {message_log_window_->Draw()};
    TCODConsole::blit(message_log_console, 0, 0, 0, 0,
                      TCODConsole::root, 0, TCODConsole::root->getHeight() - kMessageLogConsoleHeight);
}
