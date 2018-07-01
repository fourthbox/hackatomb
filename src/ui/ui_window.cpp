    #include "ui_window.hpp"

using std::string;

void UiWindow::Initialize(size_t width, size_t height, std::string const &name, std::initializer_list<UiLabel_sp> labels) {
    assert(!initialized_);
    
    width_ = width;
    height_ = height;
    name_ = name;
    
    // Initialize the static labels
    for (auto const &label : labels) {
        assert(label_list_ids_.insert({label->GetId(), label}).second);
        auto label_hnd {std::static_pointer_cast<UiLabelWithHandler>(label)};
        if (label_hnd) {
            if (auto handle {label_hnd->GetHandle()}; handle != std::experimental::nullopt && *handle >= 0)
                assert(label_list_handles_.insert({*handle, label}).second);
        }
    }
    
    // Initialize the console
    console_ = std::make_unique<TCODConsole>(width_, height_);
    
    // Setup predefined colors
    // Background is not working
    TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
    TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::green, TCODColor::black);
    
    initialized_ = true;
}

void UiWindow::Draw() {
    assert(initialized_);
    
    // Clear the console
    console_->setDefaultBackground(TCODColor::black);
    console_->clear();
    
    // Draw frame and title
    console_->printFrame(0, 0, width_, height_,
                         true,
                         TCOD_bkgnd_flag_t::TCOD_BKGND_DEFAULT,
                         name_.empty() ? NULL : name_.c_str());
        
    // Draw the labels
    std::for_each(label_list_ids_.begin(),
                  label_list_ids_.end(),
                  [&] (auto &l) { l.second->Draw(console_.get()); });
}

bool UiWindow::UpdateLabelById(std::string const &label_id, std::string const &label_text) {
    assert(initialized_);
    
    auto label {std::find_if(std::begin(label_list_ids_),
                             std::end(label_list_ids_),
                             [&] (auto const &l) -> bool {
                                 return l.second->GetId() == label_id;
                             })};
    
    if (label != label_list_ids_.end()) {
        auto label_txt {std::static_pointer_cast<UiLabelAndText>(label->second)};
        
        assert(label_txt);

        label_txt->SetDynamicText(label_text);
        return true;
    }
    
    return false;
    
}

void UiWindow::UpdateTriggerByHandle(int handle, std::function<bool()> callback) {
    assert(initialized_ && label_list_handles_.count(handle) > 0);
    
    auto label {std::static_pointer_cast<UiLabelWithHandler>(label_list_handles_[handle])};
    
    assert(label);

    label->UpdateAction(callback);
}

bool UiWindow::TriggerByHandle(int handle) {
    assert(initialized_ && label_list_handles_.count(handle) > 0);
    
    auto label {std::static_pointer_cast<UiLabelWithHandler>(label_list_handles_[handle])};
    
    assert(label);

    return label->TriggerAction();
}
