#ifndef UI_WINDOW_HPP_
#define UI_WINDOW_HPP_

#include "libtcod.hpp"

#include <memory>
#include <string>
#include <unordered_map>

struct UiLabel {
    size_t x_, y_;
    std::string text_, id_;
    
    UiLabel(size_t x, size_t y, std::string text, std::string id) :
        x_ {x},
        y_ {y},
        text_ {text},
        id_ {id} {
        }
};

class UiWindow {
public:
    std::unique_ptr<TCODConsole> console_;

    UiWindow();
    void Initialize(size_t width, size_t height, std::string name = "", std::initializer_list<UiLabel> labels = {});
    void Draw();
    
private:
    bool initialized_;
    size_t width_, height_;
    std::string name_;
    
    std::unordered_map<std::string, UiLabel> static_label_list_;
    std::unordered_map<std::string, UiLabel> dynamic_label_list_;
};

#endif /* UI_WINDOW_HPP_ */
