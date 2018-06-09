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
    auto start_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-3, kStartLabel, kStartLabelId) };
    auto load_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-2, kLoadLabel, kLoadLabelId) };
    auto config_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-1, kConfigLabel, kConfigLabelId) };
    auto quit_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2, kQuitLabel, kQuitLabelId) };
    
    start_screen_window_->Initialize(kRootViewWidth,
                                    kRootViewHeight,
                                    "hackatomb",
                                    {start_label, load_label, config_label, quit_label});
    
    // Setup the labels to be cyclable
    if (auto label {start_screen_window_->GetStaticLabel(kStartLabelId)}; label != nullptr)
        selectable_labels_.push_back(label);
    
    if (auto label {start_screen_window_->GetStaticLabel(kLoadLabelId)}; label != nullptr)
        selectable_labels_.push_back(label);

    if (auto label {start_screen_window_->GetStaticLabel(kConfigLabelId)}; label != nullptr)
        selectable_labels_.push_back(label);

    if (auto label {start_screen_window_->GetStaticLabel(kQuitLabelId)}; label != nullptr)
        selectable_labels_.push_back(label);

    // Set the first selected label to Start Game
    selected_label_ = selectable_labels_.begin();
    (*selected_label_)->is_highlighted_ = true;
    
    initialized_ = true;
}

void StartScreen::CycleMenu(bool direction) {
    assert(initialized_);

    (*selected_label_)->is_highlighted_ = false;
    
    if (direction) {
        if (++selected_label_ == selectable_labels_.end())
            selected_label_ = selectable_labels_.begin();
    } else {
        if (selected_label_-- == selectable_labels_.begin())
            selected_label_ = selectable_labels_.end()-1;
    }
    
    (*selected_label_)->is_highlighted_ = true;
}

void StartScreen::SelectMenu() {
    assert(initialized_ && engine_ != nullptr);
    
    if ((*selected_label_)->id_ == kStartLabelId) {
        // Initialize first dungeon
        engine_->InitializeGame();
        engine_->StartGame();
    }
}

UiWindow *StartScreen::GetWindow() {
    assert(initialized_);

    return start_screen_window_.get();
}

void StartScreen::Draw() {
    assert(initialized_);

    start_screen_window_->Draw();
}
