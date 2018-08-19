#ifndef UI_LABEL_HPP_
#define UI_LABEL_HPP_

#include <functional>
#include <string>

#include "libtcod.hpp"

class UiLabel {
public:
    UiLabel(std::string const &static_text,
            TCOD_colctrl_t static_color = TCOD_COLCTRL_1,
            std::string const &id = "");
    
    virtual void Draw(TCODConsole *console) = 0;
    
    inline std::string GetId() const { return id_; }
    
protected:
    std::string static_text_, id_;
    TCOD_colctrl_t static_color_;
};

class UiSimpleLabel : public UiLabel {
public:
    UiSimpleLabel(size_t x, size_t y,
                  std::string const &static_text,
                  TCOD_colctrl_t static_color = TCOD_COLCTRL_1,
                  std::string const &id = "");

    void Draw(TCODConsole *console) override;

protected:
    size_t x_, y_;
};

class UiLabelWithHandler : public UiSimpleLabel {
public:
    UiLabelWithHandler(size_t x, size_t y,
                       int handle,
                       std::string const &static_text,
                       std::function<bool()> callback = nullptr,
                       TCOD_colctrl_t static_color = TCOD_COLCTRL_1,
                       std::string const &id = "");

    void SetHandle(int handle);
    int GetHandle() const;
    bool TriggerAction() const;
    void UpdateAction(std::function<bool()> callback);
    
    void Draw(TCODConsole *console) override;

private:
    int handle_;
    std::function<bool()> action_;
};

class UiLabelAndText : public UiSimpleLabel {
public:
    UiLabelAndText(size_t x, size_t y,
                   std::string const &static_text, std::string const &dynamic_text = "",
                   TCOD_colctrl_t static_color = TCOD_COLCTRL_1,
                   TCOD_colctrl_t dynamic_color = TCOD_COLCTRL_1,
                   std::string const &id = "");

    inline void SetDynamicText(std::string const &text) { dynamic_text_ = text; }
    void Draw(TCODConsole *console) override;

private:
    std::string dynamic_text_;
    TCOD_colctrl_t dynamic_color_;
};

class UiCenteredLabel : public UiLabel {
public:
    UiCenteredLabel(size_t width, size_t height,
                    std::string const &static_text,
                    TCOD_colctrl_t static_color = TCOD_COLCTRL_1,
                    std::string const &id = "");

    void Draw(TCODConsole *console) override;
    
private:
    size_t width_, height_;
};

class UiColoredTextLabel : public UiSimpleLabel {
public:
    UiColoredTextLabel(size_t x, size_t y,
                       std::string const &colored_text = "",
                       std::string const &id = "");

    void Draw(TCODConsole *console) override;
    inline void SetColoredText(std::string const &text) { static_text_ = text; }
};

typedef std::shared_ptr<UiLabel> UiLabel_sp;

#endif /* UI_LABEL_HPP_ */
