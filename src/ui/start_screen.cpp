#include "start_screen.hpp"

#include "engine.hpp"
#include "game_constants.hpp"
#include "game_globals.hpp"
#include "label_constants.hpp"

void StartScreen::Initialize(Engine *engine) {
    assert(!initialized_);
    
    engine_ = engine;
    start_screen_window_ = std::make_unique<UiWindow>();
    
    // Initialize labels
    UiLabel_sp start_label { std::make_shared<UiLabelWithHandler>(kRootViewWidth / 2, kRootViewHeight/2-3, 'a', kStartLabel) };
    UiLabel_sp load_label { std::make_shared<UiLabelWithHandler>(kRootViewWidth / 2, kRootViewHeight/2-2, 'b', kLoadLabel) };
    UiLabel_sp config_label { std::make_shared<UiLabelWithHandler>(kRootViewWidth / 2, kRootViewHeight/2-1, 'c', kConfigLabel) };
    UiLabel_sp quit_label { std::make_shared<UiLabelWithHandler>(kRootViewWidth / 2, kRootViewHeight/2, 'd', kQuitLabel) };
    
    start_screen_window_->Initialize(kRootViewWidth,
                                     kRootViewHeight,
                                     "hackatomb",
                                     {start_label, load_label, config_label, quit_label});

    initialized_ = true;
}

UiWindow *StartScreen::GetWindow() {
    assert(initialized_);

    return start_screen_window_.get();
}

void StartScreen::Draw() {
    assert(initialized_);

    start_screen_window_->Draw();
}

void StartScreen::TriggerCommand(char cmd) {
    assert(initialized_);

    if (cmd == 'a') {
         // Initialize first dungeon
         engine_->InitializeGame();
         engine_->StartGame();
    }
}
