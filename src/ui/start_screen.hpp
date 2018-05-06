#ifndef START_SCREEN_HPP_
#define START_SCREEN_HPP_

#include <vector>

#include "ui_window.hpp"

class Engine;

class StartScreen : public InitiableObject {
public:
    void Initialize(Engine *engine);
    UiWindow *GetWindow();

    void Draw();
    void CycleMenu(bool direction);
    void SelectMenu();
    
private:
    Engine* engine_;
    UiWindow *start_screen_window_;
    std::vector<UiLabel*>::iterator selected_label_;
    std::vector<UiLabel*> selectable_labels_;
};

#endif /* START_SCREEN_HPP_ */
