#include "start_screen.hpp"

#include "game_constants.hpp"

void StartScreen::Initialize() {
    assert(!initialized_);
    
    start_screen_window_ = std::make_shared<UiWindow>();
    
    // Initialize labels
    auto start_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-3, "start", "start_label") };
    auto load_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-2, "load", "load_label") };
    auto config_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-1, "config", "config_label") };
    auto quit_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2, "quit", "quit_label") };
    
    start_screen_window_->Initialize(kRootViewWidth,
                                    kRootViewHeight,
                                    "hackatomb",
                                    {start_label, load_label, config_label, quit_label});
    
    initialized_ = true;
}

void StartScreen::CycleMenu(bool direction) {
    assert(initialized_);

}

void StartScreen::SelectMenu() {
    assert(initialized_);

}

std::shared_ptr<UiWindow> StartScreen::GetWindow() {
    assert(initialized_);

    return start_screen_window_;
}

void StartScreen::Draw() {
    assert(initialized_);

    start_screen_window_->Draw();
}
