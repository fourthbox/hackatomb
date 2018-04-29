/**
 @file root_console_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ROOT_CONSOLE_MANAGER_HPP_
#define ROOT_CONSOLE_MANAGER_HPP_

#include <string>

#include "ui_window.hpp"

/**
 Class that manages the initialization and rendering of the root console.
 */
class RootConsoleManager : public InitiableObject {
public:
    std::shared_ptr<TCODConsole> main_view_;  /**< The console upon which the main view will be drawn. */

    RootConsoleManager();
    
    /**
     Initialize this instance of the class.
     @param width Width of the root console.
     @param height Height of the root console.
     @param root_name Name of the window.
     */
    void Initialize(size_t width, size_t height, std::string root_name);
    
    /**
     Blit the consoles onto the root console.
     */
    void Render();
    
    void RenderStartScreen();
    
    /**
     Set left_window_ to point to the specific window.
     @param window A pointer to the window.
     */
    void SetLeftWindow(std::shared_ptr<UiWindow> window);
    
    /**
     Set right_window_ to point to the specific window.
     @param window A pointer to the window.
     */
    void SetRightWindow(std::shared_ptr<UiWindow> window);
    
    /**
     Set bottom_window_ to point to the specific window.
     @param window A pointer to the window.
     */
    void SetBottomWindow(std::shared_ptr<UiWindow> window);
    
    void SetStartScreenWindow(std::shared_ptr<UiWindow> window);
    
private:
    size_t width_, height_;     /**< Size of the root console. */
    std::shared_ptr<UiWindow> left_window_, right_window_, bottom_window_, start_screen_window_;   /**< Pointers to the fixed windows. */
    
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
