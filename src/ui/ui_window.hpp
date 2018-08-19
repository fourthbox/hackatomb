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
    virtual void Initialize(size_t width, size_t height, std::string const &name = "", std::initializer_list<UiLabel_sp> labels = {});
    
    /**
     Draw the window onto the console
     */
    virtual void Draw();
    
    /**
     Add a label into the window
     @param label The label to add
     */
    void AddLabel(UiLabel_sp label);
    
    /**
     Removes a label into the window by id.
     Will crash if wrong id.
     @param id The id of the label to add
     */
    void RemoveLabel(std::string id);
    
    bool UpdateLabelById(std::string const &label_id, std::string const &label_text);
    bool UpdateColoredLabelById(std::string const &label_id, std::string const &label_text);
    
    inline TCODConsole *GetConsole() { return console_.get(); }
    
protected:
    size_t width_, height_; /**< Size fo the window. */
    std::string name_;      /**< Name that appean on top of the window. */
    std::unique_ptr<TCODConsole> console_;  /**< Console upon which the window is drawn. */
    
    std::unordered_map<std::string, UiLabel_sp> label_list_ids_; /**< Id and labels */
    std::unordered_map<int, UiLabel_sp> label_list_handles_; /**< Handles and labels */
};

#endif /* UI_WINDOW_HPP_ */
