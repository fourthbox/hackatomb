#include "ui_window.hpp"

using std::string;

void UiWindow::Initialize(size_t width, size_t height, std::string const &name, std::initializer_list<UiLabel> static_labels, std::initializer_list<UiLabel> dynamic_labels) {
    assert(!initialized_);
    
    width_ = width;
    height_ = height;
    name_ = name;
    
    // Initialize the static labels
    for (auto const &label : static_labels) {
        assert( static_label_list_.insert({label.id_, label}).second );
    }
    
    // Initialize the dynamic labels
    for (auto const &label : dynamic_labels) {
        assert( dynamic_label_list_.insert({label.id_, label}).second );
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
    DrawLabelList(static_label_list_);
    DrawLabelList(dynamic_label_list_);
}

void UiWindow::DrawLabelList(std::unordered_map<std::string, UiLabel> const &label_list) {
    for (auto const &label : label_list) {
        console_->print(label.second.x_,
                        label.second.y_,
                        "%c%s%c",
                        label.second.color_.value_or(TCOD_COLCTRL_1),
                        label.second.text_.c_str(),
                        TCOD_COLCTRL_STOP);
    }
}

UiLabel *UiWindow::GetStaticLabel(std::string const &id) {
    assert(initialized_);

    for (auto &label_entry : static_label_list_) {
        if (label_entry.first == id)
            return &label_entry.second;
    }
    
    return nullptr;
}

UiLabel *UiWindow::GetDynamicLabel(std::string const &id) {
    assert(initialized_);
    
    for (auto &label_entry : dynamic_label_list_) {
        if (label_entry.first == id)
            return &label_entry.second;
    }
    
    return nullptr;
}
