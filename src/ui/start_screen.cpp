#include "start_screen.hpp"

#include "game_constants.hpp"
#include "game_globals.hpp"
#include "label_constants.hpp"

void StartScreen::Initialize() {
    assert(!initialized_);
    
    start_screen_window_ = std::make_shared<UiWindow>();
    
    // Initialize labels
    auto start_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-3, kStartLabel, kStartLabelName) };
    auto load_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-2, kLoadLabel, kLoadLabelName) };
    auto config_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2-1, kConfigLabel, kConfigLabelName) };
    auto quit_label { UiLabel(kRootViewWidth / 2, kRootViewHeight/2, kQuitLabel, kQuitLabelName) };
    
    start_screen_window_->Initialize(kRootViewWidth,
                                    kRootViewHeight,
                                    "hackatomb",
                                    {start_label, load_label, config_label, quit_label});
    
    // Setup the labels to be cyclable
    if (auto label {start_screen_window_->GetUiLabelById(kStartLabelName)}; label != nullptr)
        selectable_labels_.push_back(label);
    
    if (auto label {start_screen_window_->GetUiLabelById(kLoadLabelName)}; label != nullptr)
        selectable_labels_.push_back(label);

    if (auto label {start_screen_window_->GetUiLabelById(kConfigLabelName)}; label != nullptr)
        selectable_labels_.push_back(label);

    if (auto label {start_screen_window_->GetUiLabelById(kQuitLabelName)}; label != nullptr)
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
