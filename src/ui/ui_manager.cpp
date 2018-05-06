#include "ui_manager.hpp"

#include "game_constants.hpp"

UiManager::UiManager() {
    environment_window_ = new UiWindow();
    player_info_window_ = new UiWindow();
    message_log_window_ = new UiWindow();
}

void UiManager::Initialize() {
    assert(!initialized_);
    
    InitializeEnvironmentWindow();
    InitializePlayerInfoWindow();
    InitializeMessageLogWindow();
    
    initialized_ = true;
}

void UiManager::InitializeEnvironmentWindow() {
    assert(!initialized_);
    
    // Initialize labels
    auto floor_label { UiLabel(2, 5, "floor:", "floor_label") };
    auto environment_label { UiLabel(2, 8, "environment:", "environment_label") };
    auto temperature_label { UiLabel(2, 11, "temperature:", "temperature_label") };
    
    // Initialize the window
    environment_window_->Initialize(kEnvironmentConsoleWidth,
                                    kEnvironmentConsoleHeight,
                                    "environment",
                                    {floor_label, environment_label, temperature_label} );
}

void UiManager::InitializePlayerInfoWindow() {
    assert(!initialized_);

    player_info_window_->Initialize(kPlayerInfoWindowWidth,
                                    kPlayerInfoConsoleHeight,
                                    "player_name");
}

void UiManager::InitializeMessageLogWindow() {
    assert(!initialized_);

    message_log_window_->Initialize(kRootViewWidth,
                                    kMessageLogWindowHeight,
                                    "log");
}

void UiManager::Draw() {
    assert(initialized_);
    
    environment_window_->Draw();
    player_info_window_->Draw();
    message_log_window_->Draw();
}

UiWindow *UiManager::GetEnvironmentWindow() {
    assert(initialized_);
    
    return environment_window_;
}

UiWindow *UiManager::GetPlayerInfoWindow() {
    assert(initialized_);

    return player_info_window_;
}

UiWindow *UiManager::GetMessageLogWindow() {
    assert(initialized_);

    return message_log_window_;
}
