#include "ui_label.hpp"

static const char kSimpleLabel[] = "%c%s%c";
static const char kLabelAndDynamic[] = "%c%s:%c%s%c";
static const char kLabelAndHandler[] = "%s %c%s%c";

UiLabel::UiLabel(size_t x, size_t y,
                 std::string const &static_text, std::string const &dynamic_text,
                 std::experimental::optional<TCOD_colctrl_t> static_color,
                 std::experimental::optional<TCOD_colctrl_t> dynamic_color,
                 std::string const &id) :
x_ {x},
y_ {y},
static_text_ {static_text},
dynamic_text_ {dynamic_text},
static_color_ {static_color},
dynamic_color_ {dynamic_color},
id_ {id.empty() ? static_text : id},
handle_ {-1} {
}

void UiLabel::Draw(TCODConsole &console) {
    if (dynamic_text_.empty()) {
        if (handle_ == -1) {
            console.print(x_, y_,
                          kSimpleLabel,
                          static_color_.value_or(TCOD_COLCTRL_1),
                          static_text_.c_str(),
                          TCOD_COLCTRL_STOP);
        } else {
            // create empty string, then char to string, string to char*. abhorrent to say the least
            std::string handle("");
            handle += handle_;
            
            console.print(x_, y_,
                          kLabelAndHandler,
                          handle.c_str(),
                          static_color_.value_or(TCOD_COLCTRL_1),
                          static_text_.c_str(),
                          TCOD_COLCTRL_STOP);
        }
    } else {
        console.print(x_, y_,
                      kLabelAndDynamic,
                      static_color_.value_or(TCOD_COLCTRL_1),
                      static_text_.c_str(),
                      dynamic_color_.value_or(TCOD_COLCTRL_1),
                      dynamic_text_.c_str(),
                      TCOD_COLCTRL_STOP);
    }
}

bool UiLabel::TriggerAction() const {
    assert (action_);
    
    return action_();
}

void UiLabel::UpdateAction(std::function<bool()> callback) {
    assert (action_);

    action_ = callback;
}

int UiLabel::GetHandle() const {    
    return handle_;
}

void UiLabel::SetHandle(int handle) {
    assert(handle >= 0);

    handle_ = handle;
}
