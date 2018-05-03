#include "ui_window.hpp"

using std::string;

void UiWindow::Initialize(size_t width, size_t height, string name, std::initializer_list<UiLabel> labels) {
    assert(!initialized_);
    
    width_ = width;
    height_ = height;
    name_ = name;
    
    // Initialize the static labels
    for (auto const & label : labels) {
        assert( static_label_list_.insert({label.id_, label})
               .second );
    }
    
    // Initialize the console
    console_ = std::make_unique<TCODConsole>(width_, height_);
    
    // Setup predefined colors
    // Background is not working
    TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::red, TCODColor::black);
    
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
    
    // Draw the static labels
    for (auto const &label_entry : static_label_list_) {
        if (!label_entry.second.is_highlighted_) {
            console_->print(label_entry.second.x_,
                            label_entry.second.y_,
                            label_entry.second.text_.c_str());
        } else if (label_entry.second.is_highlighted_) {
            console_->print(label_entry.second.x_,
                            label_entry.second.y_,
                            "%c%s%c",
                            TCOD_COLCTRL_1,
                            label_entry.second.text_.c_str(),
                            TCOD_COLCTRL_STOP);
        }
    }
}

UiLabel *UiWindow::GetUiLabelById(std::string id) {
    assert(initialized_);

    for (auto &label_entry : static_label_list_) {
        if (label_entry.first == id)
            return &label_entry.second;
    }
    
    return nullptr;
}
