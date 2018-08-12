#include "ui_label.hpp"

#include "game_globals.hpp"

#include <deque>
#include <regex>

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

void UiSimpleLabel::Draw(TCODConsole *console) {
    assert(!static_text_.empty());
    
    console->print(x_, y_,
                   "%c%s%c",
                   static_color_,
                   static_text_.c_str(),
                   TCOD_colctrl_t::TCOD_COLCTRL_STOP);
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

void UiLabelWithHandler::Draw(TCODConsole *console) {
    assert(!static_text_.empty());
    
    console->print(x_, y_,
                   "%c%c %s%c",
                   static_color_,
                   (char)*handle_,
                   static_text_.c_str(),
                   TCOD_colctrl_t::TCOD_COLCTRL_STOP);
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

UiLabelAndText::UiLabelAndText(size_t x, size_t y,
                               std::string const &static_text, std::string const &dynamic_text,
                               TCOD_colctrl_t static_color, TCOD_colctrl_t dynamic_color,
                               std::string const &id) :
UiSimpleLabel(x, y, static_text, static_color, id),
dynamic_text_ {dynamic_text},
dynamic_color_ {dynamic_color} {
}

void UiLabelAndText::Draw(TCODConsole *console) {
    assert(!static_text_.empty());
    
    console->print(x_, y_,
                   "%c%s %c%s%c",
                   static_color_,
                   static_text_.c_str(),
                   dynamic_color_,
                   dynamic_text_.c_str(),
                   TCOD_colctrl_t::TCOD_COLCTRL_STOP);
}

UiCenteredLabel::UiCenteredLabel(size_t width, size_t height,
                                 std::string const &static_text,
                                 TCOD_colctrl_t static_color,
                                 std::string const &id) :
UiLabel(static_text, static_color, id),
width_ {width},
height_ {height} {
}

void UiCenteredLabel::Draw(TCODConsole *console) {
    assert(!static_text_.empty());
    
    console->printRectEx(width_/2, (height_-4)/2,
                         width_, height_,
                         TCOD_bkgnd_flag_t::TCOD_BKGND_DEFAULT,
                         TCOD_alignment_t::TCOD_CENTER,
                         "%c%s%c",
                         static_color_,
                         static_text_.c_str(),
                         TCOD_colctrl_t::TCOD_COLCTRL_STOP);
}

UiColoredTextLabel::UiColoredTextLabel(size_t x, size_t y,
                                       std::string const &colored_text,
                                       std::string const &id) :
UiSimpleLabel(x, y, colored_text, TCOD_COLCTRL_1, id) {
}

void UiColoredTextLabel::Draw(TCODConsole *console) {
    if (static_text_.empty())
        return;
    
    // libtcod print functions use variadic arguments, which are resolved at compile time
    // This makes impossible to dynamically use multiple texts and colors for different contexts
    // To work aroung this problem, the print function will always be called with 10 colors and 10 substrings
    // The unneeded strings and colors will be defaulted to empty and white
    
    // Create the text queue
    std::deque<std::string> substring_queue;
    std::regex delimiter_token {"\%\\d"};
    std::regex_token_iterator<std::string::iterator> text_iter {static_text_.begin(), static_text_.end(), delimiter_token, -1};
    std::regex_token_iterator<std::string::iterator> text_end_it;
    
    while (text_iter != text_end_it)
        substring_queue.push_front(*text_iter++);
    
    // Create the color queue
    std::deque<TCOD_colctrl_t> color_queue;
    std::sregex_iterator color_iter {static_text_.begin(), static_text_.end(), delimiter_token};
    std::sregex_iterator color_end_it;
    
    while(color_iter != color_end_it) {
        for (auto const &match : *color_iter) {
            cout << match.str() << endl;
            
            assert(match.str().length() == 2);
            
            switch (match.str().at(1)) {
                case '1':
                    color_queue.push_back(TCOD_COLCTRL_1);
                    break;
                case '2':
                    color_queue.push_back(TCOD_COLCTRL_2);
                    break;
                case '3':
                    color_queue.push_back(TCOD_COLCTRL_3);
                    break;
                case '4':
                    color_queue.push_back(TCOD_COLCTRL_4);
                    break;
                case '5':
                    color_queue.push_back(TCOD_COLCTRL_5);
                    break;
                default:
                    abort();
            }
        }
        
        color_iter++;
    }
    
    // Utility functions to return last element of a queue, and pop back
    auto get_color_and_pop = [&] () -> TCOD_colctrl_t {
        if (color_queue.empty())
            return TCOD_COLCTRL_1;
        
        auto col {color_queue.back()};
        color_queue.pop_back();
        return col;
    };
    
    auto get_text_and_pop = [&] () -> std::string {
        if (substring_queue.empty())
            return "";

        auto text {substring_queue.back()};
        substring_queue.pop_back();
        return text;
    };
    
    // Pop the stacks until they are empty
    console->print(x_, y_,
                   "%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                   get_color_and_pop(),
                   get_text_and_pop().c_str(),
                   get_color_and_pop(),
                   get_text_and_pop().c_str(),
                   get_color_and_pop(),
                   get_text_and_pop().c_str(),
                   get_color_and_pop(),
                   get_text_and_pop().c_str(),
                   get_color_and_pop(),
                   get_text_and_pop().c_str(),
                   get_color_and_pop(),
                   get_text_and_pop().c_str(),
                   get_color_and_pop(),
                   get_text_and_pop().c_str(),
                   get_color_and_pop(),
                   get_text_and_pop().c_str(),
                   get_color_and_pop(),
                   get_text_and_pop().c_str(),
                   get_color_and_pop(),
                   get_text_and_pop().c_str(),
                   TCOD_colctrl_t::TCOD_COLCTRL_STOP);
}
