#include "ui_manager.hpp"

#include <experimental/optional>

#include "game_constants.hpp"
#include "game_strings.hpp"

UiManager::UiManager() {
    environment_window_ = std::make_unique<UiWindow>();
    player_info_window_ = std::make_unique<UiWindow>();
    message_log_window_ = std::make_unique<UiWindow>();
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
    
    // Initialize static labels
    auto floor_label { UiLabel(2, 5, kFloorString) };
    auto environment_label { UiLabel(2, 8, kEnvironmentString) };
    
    // Initialize the window
    environment_window_->Initialize(kEnvironmentConsoleWidth,
                                    kEnvironmentConsoleHeight,
                                    kEnvironmentString,
                                    {floor_label, environment_label});
}

void UiManager::InitializePlayerInfoWindow() {
    assert(!initialized_);
        
    // Initialize static labels
    auto level_label { UiLabel(2, 4, kLevelString) };
    auto str_label { UiLabel(2, 9, kStrString) };
    auto dex_label { UiLabel(9, 9, kDexString) };
    auto con_label { UiLabel(2, 11, kConString) };
    auto int_label { UiLabel(9, 11, kIntString) };
    auto hp_label { UiLabel(2, 6, kHpString, "", std::experimental::nullopt, TCOD_COLCTRL_2) };

    player_info_window_->Initialize(kPlayerInfoWindowWidth,
                                    kPlayerInfoConsoleHeight,
                                    "@",
                                    {level_label, str_label, dex_label, con_label, int_label, hp_label});
}

void UiManager::InitializeMessageLogWindow() {
    assert(!initialized_);

    message_log_window_->Initialize(kRootViewWidth,
                                    kMessageLogWindowHeight,
                                    kLogString);
}

void UiManager::Draw() {
    assert(initialized_);
    
    environment_window_->Draw();
    player_info_window_->Draw();
    message_log_window_->Draw();
}

UiWindow *UiManager::GetEnvironmentWindow() {
    assert(initialized_);
    
    return environment_window_.get();
}

UiWindow *UiManager::GetPlayerInfoWindow() {
    assert(initialized_);

    return player_info_window_.get();
}

UiWindow *UiManager::GetMessageLogWindow() {
    assert(initialized_);

    return message_log_window_.get();
}

bool UiManager::UpdateLabel(std::string const &label_id, std::string const &label_text) {
    assert(initialized_);
    
    auto success {false};
    
    for (auto const &window : {environment_window_.get(), player_info_window_.get(), message_log_window_.get()}) {
        auto ret {window->UpdateLabelById(label_id, label_text)};
        if (ret) success = true;
    }
    
    return success;
}

