/**
 @file ui_window.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef UI_WINDOW_HPP_
#define UI_WINDOW_HPP_

#include "initiable_object.hpp"
#include "libtcod.hpp"
#include "ui_label.hpp"

#include <unordered_map>

/**
 This class represent a drawable window.
 */
class UiWindow : public InitiableObject {
public:
    /**
     Initialize the Window, the console and the static labels.
     @param width The width of the window.
     @param height The height of the window.
     @param name The name that will appear on top of the window.
     @param static_labels The static labels for the window.
     @param dynamic_labels The dynamic labels for the window
     */
    virtual void Initialize(size_t width, size_t height, std::string const &name = "", std::initializer_list<UiLabel> labels = {});
    
    /**
     Draw the window onto the console
     */
    virtual void Draw();
    
    bool UpdateLabelById(std::string const &label_id, std::string const &label_text);
    void UpdateTriggerByHandle(int handle, std::function<bool()> callback);
    
    bool TriggerByHandle(int handle);
    
    inline TCODConsole *GetConsole() { return console_.get(); }
    
protected:
    size_t width_, height_; /**< Size fo the window. */
    std::string name_;      /**< Name that appean on top of the window. */
    std::unique_ptr<TCODConsole> console_;  /**< Console upon which the window is drawn. */
    
    std::unordered_map<std::string, std::shared_ptr<UiLabel>> label_list_ids_; /**< Id and labels */
    std::unordered_map<int, std::shared_ptr<UiLabel>> label_list_handles_; /**< Handles and labels */
};

#endif /* UI_WINDOW_HPP_ */
