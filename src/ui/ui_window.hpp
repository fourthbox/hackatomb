/**
 @file ui_window.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef UI_WINDOW_HPP_
#define UI_WINDOW_HPP_

#include "libtcod.hpp"

#include <memory>
#include <string>
#include <unordered_map>

/**
 Struct that defines the labels that can be embedded into windows.
 */
struct UiLabel {
    size_t x_, y_;              /**< Coordinates of the top-left point of the label. */
    std::string text_, id_;      /**< Label text, and unique id. */
    
    UiLabel(size_t x, size_t y, std::string text, std::string id) :
        x_ {x},
        y_ {y},
        text_ {text},
        id_ {id} {
        }
};

/**
 This class represent a drawable window.
 */
class UiWindow {
public:
    std::unique_ptr<TCODConsole> console_;  /**< Console upon which the window is drawn. */

    UiWindow();
    
    /**
     Initialize the Window, the console and the static labels.
     @param width The width of the window.
     @param height The height of the window.
     @param name The name that will appear on top of the window.
     @param labels The static labels for the window.
     */
    void Initialize(size_t width, size_t height, std::string name = "", std::initializer_list<UiLabel> labels = {});
    
    /**
     Draw the window onto the console
     */
    void Draw();
    
private:
    bool initialized_;      /**< Utility switch for initialization security checks. */
    size_t width_, height_; /**< Size fo the window. */
    std::string name_;      /**< Name that appean on top of the window. */
    
    std::unordered_map<std::string, UiLabel> static_label_list_;    /**< List for static labels. */
    std::unordered_map<std::string, UiLabel> dynamic_label_list_;   /**< List for dynamic labels. */
};

#endif /* UI_WINDOW_HPP_ */
