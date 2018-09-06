#include "ui_manager.hpp"

#include <experimental/optional>
#include <sstream>

#include "game_constants.hpp"
#include "game_globals.hpp"
#include "label_constants.hpp"

#define COLOR_WHITE_    "#1"
#define COLOR_RED_      "#2"
#define COLOR_GREEN_    "#3"
#define COLOR_BLUE_     "#4"
#define COLOR_YELLOW_   "#5"

static const std::string kLine0Label = "line_0";
static const std::string kLine1Label = "line_1";
static const std::string kLine2Label = "line_2";
static const std::string kLine3Label = "line_3";

UiManager::UiManager() {
    environment_window_ = std::make_unique<UiWindow>();
    player_info_window_ = std::make_unique<UiWindow>();
    message_log_window_ = std::make_unique<UiWindow>();
    inventory_window_ = std::make_unique<UiInventory>();
}

void UiManager::Initialize(ItemsManager &inventory_manager) {
    assert(!initialized_);
    
    // Setup predefined colors
    // Background is not working
    TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
    TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);
    TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::green, TCODColor::black);
    TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::blue, TCODColor::black);
    TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::yellow, TCODColor::black);

    // Initialize windows
    InitializeEnvironmentWindow();
    InitializePlayerInfoWindow();
    InitializeMessageLogWindow();
    InitializeInventoryWindow(inventory_manager);
    
    initialized_ = true;
}

void UiManager::InitializeEnvironmentWindow() {
    assert(!initialized_);
    
    // Initialize static labels
    UiLabel_sp floor_label { std::make_shared<UiLabelAndText>(2, 5, kFloorString, "1", TCOD_COLCTRL_1, TCOD_COLCTRL_1, kFloorLabelId)};
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
    auto hp_label { std::make_shared<UiLabelAndText>(2, 6, kHpString, "", TCOD_COLCTRL_1, TCOD_COLCTRL_3) };

    player_info_window_->Initialize(kPlayerInfoWindowWidth,
                                    kPlayerInfoConsoleHeight,
                                    "@",
                                    {level_label, str_label, dex_label, con_label, int_label, hp_label});
}

void UiManager::InitializeMessageLogWindow() {
    assert(!initialized_);
    
    // Initialize static labels
    auto line_0 { std::make_shared<UiColoredTextLabel>(2, 4, "", "line_0") };
    auto line_1 { std::make_shared<UiColoredTextLabel>(2, 3, "", "line_1") };
    auto line_2 { std::make_shared<UiColoredTextLabel>(2, 2, "", "line_2") };
    auto line_3 { std::make_shared<UiColoredTextLabel>(2, 1, "", "line_3") };
    
    message_log_window_->Initialize(kRootViewWidth,
                                    kMessageLogWindowHeight,
                                    kLogString,
                                    {line_0, line_1, line_2, line_3});
}

void UiManager::InitializeInventoryWindow(ItemsManager &inventory_manager) {
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
    
    // Shift Log messages
    message_log_window_->UpdateColoredLabelById(kLine0Label, log_manager_.GetStringFromTop(0));
    message_log_window_->UpdateColoredLabelById(kLine1Label, log_manager_.GetStringFromTop(1));
    message_log_window_->UpdateColoredLabelById(kLine2Label, log_manager_.GetStringFromTop(2));
    message_log_window_->UpdateColoredLabelById(kLine3Label, log_manager_.GetStringFromTop(3));

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
    
    auto windows = {environment_window_.get(), player_info_window_.get(), message_log_window_.get()};
    
    return std::any_of(windows.begin(),
                       windows.end(),
                       [&] (auto &w) { return w->UpdateLabelById(label_id, label_text); });
}

void UiManager::LogManager::LogAttack(Actor &source, Actor &target, int damage) {
    // {source} attacked {target} for {damage} physical damage
    std::ostringstream stream;
    stream
    << COLOR_GREEN_ << source.GetName()
    << COLOR_WHITE_ << " attacked "
    << COLOR_BLUE_ << target.GetName()
    << COLOR_WHITE_ << " for "
    << COLOR_RED_ << std::to_string(damage)
    << COLOR_WHITE_ << " physical damage.";

    AddMessage(stream.str());
}

std::string UiManager::LogManager::GetStringFromTop(size_t position) {
    if (position >= message_queue_.size())
        return "";
        
    return message_queue_.at(position);
}
