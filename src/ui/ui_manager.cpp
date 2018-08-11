#include "ui_manager.hpp"

#include <experimental/optional>

#include "game_constants.hpp"
#include "game_strings.hpp"

UiManager::UiManager() {
    environment_window_ = std::make_unique<UiWindow>();
    player_info_window_ = std::make_unique<UiWindow>();
    message_log_window_ = std::make_unique<UiWindow>();
    inventory_window_ = std::make_unique<UiInventory>();
}

void UiManager::Initialize(InventoryManager &inventory_manager) {
    assert(!initialized_);
    
    InitializeEnvironmentWindow();
    InitializePlayerInfoWindow();
    InitializeMessageLogWindow();
    InitializeInventoryWindow(inventory_manager);
    
    initialized_ = true;
}

void UiManager::InitializeEnvironmentWindow() {
    assert(!initialized_);
    
    // Initialize static labels
    UiLabel_sp floor_label { std::make_shared<UiSimpleLabel>(2, 5, kFloorString)};
    UiLabel_sp environment_label { std::make_shared<UiSimpleLabel>(2, 8, kEnvironmentString) };
    
    // Initialize the window
    environment_window_->Initialize(kEnvironmentConsoleWidth,
                                    kEnvironmentConsoleHeight,
                                    kEnvironmentString,
                                    {floor_label, environment_label});
}

void UiManager::InitializePlayerInfoWindow() {
    assert(!initialized_);
        
    // Initialize static labels
    auto level_label { std::make_shared<UiLabelAndText>(2, 4, kLevelString) };
    auto str_label { std::make_shared<UiLabelAndText>(2, 9, kStrString) };
    auto dex_label { std::make_shared<UiLabelAndText>(9, 9, kDexString) };
    auto con_label { std::make_shared<UiLabelAndText>(2, 11, kConString) };
    auto int_label { std::make_shared<UiLabelAndText>(9, 11, kIntString) };
    auto hp_label { std::make_shared<UiLabelAndText>(2, 6, kHpString, "", TCOD_COLCTRL_1, TCOD_COLCTRL_2) };

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

void UiManager::InitializeInventoryWindow(InventoryManager &inventory_manager) {
    assert(!initialized_);
    
    inventory_window_->Initialize(inventory_manager,
                                  kRootViewWidth,
                                  kRootViewHeight,
                                  kInventoryString);
}

void UiManager::Draw() {
    assert(initialized_);
    
    inventory_window_->Draw();
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

UiWindow *UiManager::GetInventoryWindow() {
    assert(initialized_);
    
    return inventory_window_.get();
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

void UiManager::LogManager::LogAttack(Actor const &source, Actor const &target, int damage) {
    // {source} attacked {target} for {damage} physical damage
    
    // TODO: formatting string with cool c++17 functions
}
