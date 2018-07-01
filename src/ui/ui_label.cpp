#include "ui_label.hpp"

UiLabel::UiLabel(std::string const &static_text,
                 TCOD_colctrl_t static_color,
                 std::string const &id) :
static_text_ {static_text},
static_color_ {static_color},
id_ {id.empty() ? static_text : id} {
}

UiSimpleLabel::UiSimpleLabel(size_t x, size_t y,
                             std::string const &static_text,
                             TCOD_colctrl_t static_color,
                             std::string const &id) :
UiLabel(static_text, static_color, id),
x_ {x},
y_ {y} {
}

UiLabelWithHandler::UiLabelWithHandler(size_t x, size_t y,
                                       int handle,
                                       std::string const &static_text,
                                       std::function<bool()> callback,
                                       TCOD_colctrl_t static_color,
                                       std::string const &id) :
UiSimpleLabel(x, y, static_text, static_color, id),
handle_ {handle},
action_ {callback} {
}

UiLabelAndText::UiLabelAndText(size_t x, size_t y,
                               std::string const &static_text, std::string const &dynamic_text,
                               TCOD_colctrl_t static_color, TCOD_colctrl_t dynamic_color,
                               std::string const &id) :
UiSimpleLabel(x, y, static_text, static_color, id),
dynamic_text_ {dynamic_text},
dynamic_color_ {dynamic_color} {
}

UiCenteredLabel::UiCenteredLabel(size_t width, size_t height,
                                 std::string const &static_text,
                                 TCOD_colctrl_t static_color,
                                 std::string const &id) :
UiLabel(static_text, static_color, id),
width_ {width},
height_ {height} {
}

void UiSimpleLabel::Draw(TCODConsole *console) {
    assert(!static_text_.empty());
    
    console->print(x_, y_,
                   "%c%s%c",
                   static_color_,
                   static_text_.c_str(),
                   TCOD_COLCTRL_STOP);
}

void UiLabelWithHandler::Draw(TCODConsole *console) {
    assert(!static_text_.empty());
    
    console->print(x_, y_,
                   "%c%c %s%c",
                   static_color_,
                   (char)*handle_,
                   static_text_.c_str(),
                   TCOD_COLCTRL_STOP);
}

bool UiLabelWithHandler::TriggerAction() const {
    assert (action_);
    
    return action_();
}

void UiLabelWithHandler::UpdateAction(std::function<bool()> callback) {
    assert (callback);
    
    action_ = callback;
}

Int_n UiLabelWithHandler::GetHandle() const {    
    return handle_;
}

void UiLabelWithHandler::SetHandle(int handle) {
    assert(handle >= 0);
    
    handle_ = handle;
}

void UiLabelAndText::Draw(TCODConsole *console) {
    assert(!static_text_.empty());

    console->print(x_, y_,
                   "%c%s %c%s%c",
                   static_color_,
                   static_text_.c_str(),
                   dynamic_color_,
                   dynamic_text_.c_str(),
                   TCOD_COLCTRL_STOP);
}

void UiCenteredLabel::Draw(TCODConsole *console) {
    assert(!static_text_.empty());
    
    console->printRect(0, 0,
                       width_, height_,
                       "%c%s%c",
                       static_color_,
                       static_text_.c_str(),
                       TCOD_COLCTRL_STOP);
}
