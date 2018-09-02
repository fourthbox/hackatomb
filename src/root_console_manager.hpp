/**
 @file root_console_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ROOT_CONSOLE_MANAGER_HPP_
#define ROOT_CONSOLE_MANAGER_HPP_

#include <string>

#include "map.hpp"
#include "turn_manager.hpp"
#include "ui_window.hpp"

class MapLocation;

/**
 Class that manages the initialization and rendering of the root console.
 */
class RootConsoleManager : public InitiableObject {
public:
    std::unique_ptr<TCODConsole> main_view_;  /**< The console upon which the main view will be drawn. */

    RootConsoleManager();
    
    /**
     Initialize this instance of the class.
     @param width Width of the root console.
     @param height Height of the root console.
     @param root_name Name of the window.
     */
    void Initialize(size_t width, size_t height, std::string const &root_name);
    
    /**
     Blit the consoles onto the root console.
     */
    void Render(TurnPhase turn_phase);
    
    void RenderStartScreen();
    
    /**
     Set left_window_ to point to the specific window.
     @param window A pointer to the window.
     */
    void SetLeftWindow(UiWindow *window);
    
    /**
     Set right_window_ to point to the specific window.
     @param window A pointer to the window.
     */
    void SetRightWindow(UiWindow *window);
    
    /**
     Set bottom_window_ to point to the specific window.
     @param window A pointer to the window.
     */
    void SetBottomWindow(UiWindow *window);
    
    void SetStartScreenWindow(UiWindow *window);
    
    void SetFullScreenWindow(UiWindow *window);
    
    void UpdateCameraPosition(MapLocation const &location, bool ignore_map_bounds = false);
    
private:
    size_t width_, height_;     /**< Size of the root console. */
    UiWindow *left_window_, *right_window_, *bottom_window_, *start_screen_window_, *full_screen_window_;   /**< Pointers to the fixed windows. */
    int camera_x_, camera_y_;
    
    /**
     Map non-default characters to specific char codes.
     */
    void MapCharacters();
    
    /**
     Clears the console.
     */
    void Clear();

};

#endif /* ROOT_CONSOLE_MANAGER_HPP_ */
