#include "key_mapper.hpp"

TCOD_key_t KeyMapper::LastKey;
TCOD_mouse_t KeyMapper::LastMousePosition;

KeyMapper::Action KeyMapper::GetActionByKey() {
    switch (LastKey.c) {
        case 'k':
            return Action::MOVE_N;
        case 'u':
            return Action::MOVE_NE;
        case 'l':
            return Action::MOVE_E;
        case 'n':
            return Action::MOVE_SE;
        case 'j':
            return Action::MOVE_S;
        case 'b':
            return Action::MOVE_SW;
        case 'h':
            return Action::MOVE_W;
        case 'y':
            return Action::MOVE_NW;
            
        default:
            return Action::NONE;
            break;
    }
    
    return Action::NONE;
}
