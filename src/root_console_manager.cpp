#include "root_console_manager.hpp"

#include "game_constants.hpp"
#include "game_utils.hpp"
#include "map_entity.hpp"

RootConsoleManager::RootConsoleManager() {
    main_view_ = std::make_unique<TCODConsole>(kMapWidth, kMapHeight);
}

void RootConsoleManager::Initialize(size_t width, size_t height, std::string const &root_name) {
    assert (!initialized_);
    
    // Set fields
    width_ = width;
    height_ = height;
    camera_x_ = 0;
    camera_y_ = 0;

    // Set the font
    TCODConsole::setCustomFont("res/sborogue.png", TCOD_FONT_LAYOUT_ASCII_INROW);

    // Initialize the TCOD Console
    TCODConsole::initRoot(width,
                          height,
                          root_name.c_str());
    
    // Set the framerate
    TCODSystem::setFps(kDefaultFrameRate);

    // Map missing characters
    MapCharacters();
    
    initialized_ = true;
}

void RootConsoleManager::Clear() {
    assert(initialized_);

    TCODConsole::root->clear();
}

void RootConsoleManager::Render(TurnPhase turn_phase) {
    assert(initialized_ && right_window_ && left_window_ && bottom_window_ && full_screen_window_);
    
    // Clear the screen
    Clear();
    
    // Blit the consoles on the root console
    if (turn_phase == TurnPhase::MENU_) {
        TCODConsole::blit(full_screen_window_->GetConsole(), 0, 0, 0, 0,
                          TCODConsole::root, 0, 0);
    } else {
        TCODConsole::blit(main_view_.get(), camera_x_, camera_y_, kCameraWidth, kCameraHeight,
                          TCODConsole::root, kEnvironmentConsoleWidth, 0);
        
        TCODConsole::blit(left_window_->GetConsole(), 0, 0, 0, 0,
                          TCODConsole::root, 0, 0);
        
        TCODConsole::blit(right_window_->GetConsole(), 0, 0, 0, 0,
                          TCODConsole::root, TCODConsole::root->getWidth() - kPlayerInfoWindowWidth, 0);
        
        TCODConsole::blit(bottom_window_->GetConsole(), 0, 0, 0, 0,
                          TCODConsole::root, 0, TCODConsole::root->getHeight() - kMessageLogWindowHeight);
    }

    TCODConsole::flush();
}

void RootConsoleManager::RenderStartScreen() {
    assert(initialized_ && start_screen_window_);
    
    // Clear the screen
    Clear();
    
    // Blit the consoles on the root console
    TCODConsole::blit(start_screen_window_->GetConsole(), 0, 0, 0, 0,
                      TCODConsole::root, 0, 0);
    
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

void RootConsoleManager::SetLeftWindow(UiWindow *window) {
    assert(initialized_);
    
    left_window_ = window;
}

void RootConsoleManager::SetRightWindow(UiWindow *window) {
    assert(initialized_);
    
    right_window_ = window;
}

void RootConsoleManager::SetBottomWindow(UiWindow *window) {
    assert(initialized_);
    
    bottom_window_ = window;
}

void RootConsoleManager::SetStartScreenWindow(UiWindow *window) {
    assert(initialized_);
    
    start_screen_window_ = window;
}

void RootConsoleManager::SetFullScreenWindow(UiWindow *window) {
    assert(initialized_);
    
    full_screen_window_ = window;
}

void RootConsoleManager::UpdateCameraPosition(MapLocation const &location, bool ignore_map_bounds) {
    assert(initialized_);
    
    auto x {(int)location.x_}, y {(int)location.y_};
    
    camera_x_ = x - kCameraWidth/2;
    camera_y_ = y - kCameraHeight/2;
    
    if (camera_x_ < 0) camera_x_ = 0;
    if (camera_y_ < 0) camera_y_ = 0;

    if (camera_x_ + kCameraWidth > kMapWidth) camera_x_ = kMapWidth - kCameraWidth;
    if (camera_y_ + kCameraHeight > kMapHeight) camera_y_ = kMapHeight - kCameraHeight;
}
