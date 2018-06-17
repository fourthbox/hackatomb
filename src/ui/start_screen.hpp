#ifndef START_SCREEN_HPP_
#define START_SCREEN_HPP_

#include <vector>

#include "ui_window.hpp"

class Engine;

class StartScreen : public InitiableObject {
public:
    void Initialize(Engine *engine);
    UiWindow *GetWindow();
    void TriggerCommand(char cmd);

    void Draw();
    
private:
    Engine *engine_;
    std::unique_ptr<UiWindow> start_screen_window_;
};

#endif /* START_SCREEN_HPP_ */
