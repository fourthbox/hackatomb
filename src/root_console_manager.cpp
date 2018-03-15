#include "root_console_manager.hpp"

#include <cassert>

#include "game_constants.hpp"
#include "game_utils.hpp"

RootConsoleManager::RootConsoleManager() :
initialized_ {false} {
    assert(!initialized_);
    
    main_view_ = std::make_shared<TCODConsole>(kMapWidth, kMapHeight);
}

void RootConsoleManager::Initialize(size_t width, size_t height,
                             size_t left_offset, size_t right_offset,
                             size_t top_offset, size_t bottom_offset, std::string root_name) {
    assert (!initialized_);
    
    // Set fields
    width_ = width;
    height_ = height;
    left_offset_ = left_offset;
    right_offset_ = right_offset;
    top_offset_ = top_offset;
    bottom_offset_ = bottom_offset;

    // Set the font
    TCODConsole::setCustomFont("res/sborogue.png", TCOD_FONT_LAYOUT_ASCII_INROW);

    // Initialize the TCOD Console
    TCODConsole::initRoot(width,
                          height,
                          root_name.c_str());

    // Map missing characters
    MapCharacters();
    
    initialized_ = true;
}

void RootConsoleManager::Clear() {
    assert(initialized_);

    TCODConsole::root->clear();
}

void RootConsoleManager::Render() {
    assert(initialized_);
    
    // Clear the screen
    Clear();
    
    // Blit the consoles on the root console
    TCODConsole::blit(main_view_.get(), 0, 0, 0, 0,
                      TCODConsole::root, kEnvironmentConsoleWidth, 0);
    
    // Blit the windows on the windows on the root console
    TCODConsole::blit(left_window_->console_.get(), 0, 0, 0, 0,
                      TCODConsole::root, 0, 0);

    TCODConsole::blit(right_window_->console_.get(), 0, 0, 0, 0,
                      TCODConsole::root, TCODConsole::root->getWidth() - kPlayerInfoConsoleWidth, 0);

    TCODConsole::blit(bottom_window_->console_.get(), 0, 0, 0, 0,
                      TCODConsole::root, 0, TCODConsole::root->getHeight() - kMessageLogConsoleHeight);

    TCODConsole::flush();
}

void RootConsoleManager::MapCharacters() {
    assert(!initialized_);
    
    TCODConsole::mapAsciiCodeToFont(kCharDoubleLineOpenNorth, 11, 13);
    TCODConsole::mapAsciiCodeToFont(kCharDoubleLineOpenEast, 14, 13);
    TCODConsole::mapAsciiCodeToFont(kCharDoubleLineOpenSouth, 13, 13);
    TCODConsole::mapAsciiCodeToFont(kCharDoubleLineOpenWest, 12, 13);
    TCODConsole::mapAsciiCodeToFont(kCharDoubleLineCenter, 15, 13);
}

void RootConsoleManager::SetLeftWindow(std::shared_ptr<UiWindow> window) {
    assert(initialized_);
    
    left_window_ = window;
}

void RootConsoleManager::SetRightWindow(std::shared_ptr<UiWindow> window) {
    assert(initialized_);
    
    right_window_ = window;
}

void RootConsoleManager::SetBottomWindow(std::shared_ptr<UiWindow> window) {
    assert(initialized_);
    
    bottom_window_ = window;
}

