#include "root_console_manager.hpp"

#include <cassert>

#include "game_constants.hpp"
#include "game_utils.hpp"

RootConsoleManager::RootConsoleManager() : initialized_ {false}
{}

void RootConsoleManager::Initialize(size_t width, size_t height,
                             size_t left_offset, size_t right_offset,
                             size_t top_offset, size_t bottom_offset, std::string root_name) {
    if (initialized_) {
        Utils::LogWarning("RootConsoleManager", "Root Console already initialized.");
        return;
    }
    
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

void RootConsoleManager::SetChar(size_t x, size_t y, int sprite, TCODColor color) {
    assert(initialized_);
    
    TCODConsole::root->setChar(x + left_offset_, y + top_offset_, sprite);
    TCODConsole::root->setCharForeground(x + left_offset_, y + top_offset_, color);
}

void RootConsoleManager::SetBackground(size_t x, size_t y, TCODColor color) {
    assert(initialized_);
    
    TCODConsole::root->setCharBackground(x + left_offset_, y + top_offset_, color);
}

void RootConsoleManager::Clear() {
    assert(initialized_);

    TCODConsole::root->clear();
}

void RootConsoleManager::Render() {
    assert(initialized_);

    TCODConsole::flush();
}

void RootConsoleManager::MapCharacters() {
    TCODConsole::mapAsciiCodeToFont(kCharDoubleLineOpenNorth, 11, 13);
    TCODConsole::mapAsciiCodeToFont(kCharDoubleLineOpenEast, 14, 13);
    TCODConsole::mapAsciiCodeToFont(kCharDoubleLineOpenSouth, 13, 13);
    TCODConsole::mapAsciiCodeToFont(kCharDoubleLineOpenWest, 12, 13);
    TCODConsole::mapAsciiCodeToFont(kCharDoubleLineCenter, 15, 13);
    
}
