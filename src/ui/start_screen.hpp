#ifndef START_SCREEN_HPP_
#define START_SCREEN_HPP_

#include "initiable_object.hpp"

class StartScreen : public InitiableObject {
public:
    void CycleMenu(bool direction);
    void SelectMenu();
};

#endif /* START_SCREEN_HPP_ */
