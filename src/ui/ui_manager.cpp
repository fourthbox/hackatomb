#include "ui_manager.hpp"

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
    auto s_floor_label { UiLabel(2, 5, kFloorString + ":", kFloorString + kStaticLabel) };
    auto s_environment_label { UiLabel(2, 8, kEnvironmentString + ":", kEnvironmentString + kStaticLabel) };
    
    // Initialize dynamic labels
    auto d_floor_label { UiLabel(s_floor_label.x_, s_floor_label.y_+1, "", kFloorString + kDynamicLabel) };
    auto d_environment_label { UiLabel(2, 7, "", kFloorString + kDynamicLabel) };
    
    // Initialize the window
    environment_window_->Initialize(kEnvironmentConsoleWidth,
                                    kEnvironmentConsoleHeight,
                                    kEnvironmentString,
                                    {s_floor_label, s_environment_label} );
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
        if (auto label {window->GetDynamicLabel(label_id)}; label != nullptr) {
            label->text_ = label_text;
            success = true;
        }
    }
    
    return success;
}

