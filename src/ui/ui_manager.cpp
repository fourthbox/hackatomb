#include "ui_manager.hpp"

#include "game_constants.hpp"

UiManager::UiManager() {
    environment_window_ = std::make_shared<UiWindow>();
    player_info_window_ = std::make_shared<UiWindow>();
    message_log_window_ = std::make_shared<UiWindow>();
    
    start_screen_window_ = std::make_shared<UiWindow>();
}

void UiManager::Initialize() {
    assert(!initialized_);
    
    InitializeEnvironmentWindow();
    InitializePlayerInfoWindow();
    InitializeMessageLogWindow();
    
    InitializeStartScreenWindow();
    
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

void UiManager::InitializeStartScreenWindow() {
    assert(!initialized_);
    
    // Initialize labels
    auto start_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-3, "start", "start_label") };
    auto load_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-2, "load", "load_label") };
    auto config_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-1, "config", "config_label") };
    auto quit_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2, "quit", "quit_label") };

    start_screen_window_->Initialize(kRootViewWidth,
                                     kRootViewHeight,
                                     "hackatomb",
                                     {start_label, load_label, config_label, quit_label});
}

void UiManager::Draw() {
    assert(initialized_);
    
    environment_window_->Draw();
    player_info_window_->Draw();
    message_log_window_->Draw();
}

void UiManager::DrawStartScreen() {
    assert(initialized_);
    
    start_screen_window_->Draw();
}
