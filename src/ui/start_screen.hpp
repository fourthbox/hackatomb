#ifndef START_SCREEN_HPP_
#define START_SCREEN_HPP_

#include "ui_window.hpp"

class StartScreen : public InitiableObject{
public:
    void Initialize();
    std::shared_ptr<UiWindow> GetWindow();

    void Draw();
    void CycleMenu(bool direction);
    void SelectMenu();
    
private:
    std::shared_ptr<UiWindow> start_screen_window_;
};

#endif /* START_SCREEN_HPP_ */
