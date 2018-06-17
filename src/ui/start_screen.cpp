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
    auto start_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-3, kStartLabel) };
    start_label.SetHandle('a');
    
    auto load_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-2, kLoadLabel) };
    load_label.SetHandle('b');

    auto config_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-1, kConfigLabel) };
    config_label.SetHandle('c');

    auto quit_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2, kQuitLabel) };
    quit_label.SetHandle('d');
    
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
