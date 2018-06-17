#ifndef UI_LABEL_HPP_
#define UI_LABEL_HPP_

#include <string>
#include <experimental/optional>

#include "libtcod.hpp"

class UiLabel {
public:
    UiLabel(size_t x, size_t y,
            std::string const &static_text, std::string const &dynamic_text = "",
            std::experimental::optional<TCOD_colctrl_t> static_color = std::experimental::nullopt,
            std::experimental::optional<TCOD_colctrl_t> dynamic_color = std::experimental::nullopt,
            std::string const &id = "");
    
    void Draw(TCODConsole &console);
    bool TriggerAction() const;
    void UpdateAction(std::function<bool()> callback);
    
    inline std::string GetId() const { return id_; }
    void SetHandle(int handle);
    int GetHandle() const;

    inline void SetDynamicText(std::string text) { dynamic_text_ = text; }
    
private:
    size_t x_, y_;              /**< Coordinates of the top-left point of the label. */
    std::string static_text_, dynamic_text_, id_;      /**< Label text, and unique id. */
    std::experimental::optional<TCOD_colctrl_t> static_color_, dynamic_color_;\
    int handle_; // it's a char
    std::function<bool()> action_;
};

#endif /* UI_LABEL_HPP_ */
