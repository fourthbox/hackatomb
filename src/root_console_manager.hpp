/**
 This class manages the initialization, draw and management of the root console
 @file root_console_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ROOT_CONSOLE_MANAGER_HPP_
#define ROOT_CONSOLE_MANAGER_HPP_

#include <string>

#include "libtcod.hpp"

#include "console_proxy.hpp"
#include "ui_window.hpp"

class RootConsoleManager {
public:
    RootConsoleManager();
    void Initialize(size_t width, size_t height,
                    size_t left_offset, size_t right_offset,
                    size_t top_offset, size_t bottom_offset,
                    std::string root_name);
    void Render();
    
    ConsoleProxy& GetMainView();
    void SetLeftWindow(UiWindow &window);
    void SetRightWindow(UiWindow &window);
    void SetBottomWindow(UiWindow &window);
    
private:
    bool initialized_;
    size_t width_, height_, left_offset_, right_offset_, top_offset_, bottom_offset_;
    UiWindow *left_window_, *right_window_, *bottom_window_;
    
    ConsoleProxy main_view_;  /**< The console upon which the main view will be drawn. */
    
    void MapCharacters();
    void Clear();

};

#endif /* ROOT_CONSOLE_MANAGER_HPP_ */
