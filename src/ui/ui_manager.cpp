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
    auto d_floor_label { UiLabel(s_floor_label.x_ + s_floor_label.text_.length(),
                                 s_floor_label.y_,
                                 "", kFloorString + kDynamicLabel) };
    auto d_environment_label { UiLabel(2, 7, "", kEnvironmentString + kDynamicLabel) };
    
    // Initialize the window
    environment_window_->Initialize(kEnvironmentConsoleWidth,
                                    kEnvironmentConsoleHeight,
                                    kEnvironmentString,
                                    {s_floor_label, s_environment_label},
                                    {d_floor_label, d_environment_label});
}

void UiManager::InitializePlayerInfoWindow() {
    assert(!initialized_);
    
    static const std::string kLevelString = "lvl";
    static const std::string kStrString = "str";
    static const std::string kDexString = "dex";
    static const std::string kConString = "con";
    static const std::string kIntString = "int";

    
    // Initialize static labels
    auto s_level_label { UiLabel(2, 4, kLevelString + ":", kLevelString + kStaticLabel) };
    auto s_str_label { UiLabel(2, 9, kStrString + ":", kStrString + kStaticLabel) };
    auto s_dex_label { UiLabel(9, 9, kDexString + ":", kDexString + kStaticLabel) };
    auto s_con_label { UiLabel(2, 11, kConString + ":", kConString + kStaticLabel) };
    auto s_int_label { UiLabel(9, 11, kIntString + ":", kIntString + kStaticLabel) };
    
    auto d_level_label { UiLabel(s_level_label.x_ + s_level_label.text_.length(),
                                 s_level_label.y_,
                                 "", kLevelString + kDynamicLabel) };
    auto d_str_label { UiLabel(s_str_label.x_ + s_str_label.text_.length(),
                               s_str_label.y_,
                               "", kStrString + kDynamicLabel) };
    auto d_dex_label { UiLabel(s_dex_label.x_ + s_dex_label.text_.length(),
                               s_dex_label.y_,
                               "", kDexString + kDynamicLabel) };
    auto d_con_label { UiLabel(s_con_label.x_ + s_con_label.text_.length(),
                               s_con_label.y_,
                               "", kConString + kDynamicLabel) };
    auto d_int_label { UiLabel(s_int_label.x_ + s_int_label.text_.length(),
                               s_int_label.y_,
                               "", kIntString + kDynamicLabel) };

    player_info_window_->Initialize(kPlayerInfoWindowWidth,
                                    kPlayerInfoConsoleHeight,
                                    "@",
                                    {s_level_label, s_str_label, s_dex_label, s_con_label, s_int_label},
                                    {d_level_label, d_str_label, d_dex_label, d_con_label, d_int_label});
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
        if (auto label {window->GetDynamicLabel(label_id)}; label != nullptr) {
            label->text_ = label_text;
            success = true;
        }
    }
    
    return success;
}

