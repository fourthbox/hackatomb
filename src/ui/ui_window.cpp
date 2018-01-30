#include "ui_window.hpp"

#include <cassert>

using std::string;

UiWindow::UiWindow(size_t width, size_t height, string name, std::initializer_list<UiLabel> labels) :
    width_ {width},
    height_ {height},
    name_ {name}
{
    // Initialize the static labels
    for (auto const & label : labels) {
        assert( static_label_list_.insert({label.id_, label})
               .second );
    }
    
    // Initialize the console
    console_ = new TCODConsole(width_, height_);
        
    // Clear the console
    console_->setDefaultBackground(TCODColor::black);
    console_->clear();

    // Draw frame and title
    console_->printFrame(0, 0, width_, height_,
                         true,
                         TCOD_bkgnd_flag_t::TCOD_BKGND_DEFAULT,
                         name.empty() ? NULL : name.c_str());
    
    // Draw the static labels
    for (auto const & label_entry : static_label_list_) {
        console_->print(label_entry.second.x_,
                        label_entry.second.y_,
                        label_entry.second.text_.c_str());
    }
}

UiWindow::~UiWindow() {
    delete console_;
}

TCODConsole* UiWindow::Draw() {
    return console_;
}
