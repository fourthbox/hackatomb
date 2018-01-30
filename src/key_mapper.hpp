#ifndef KEY_MAPPER_HPP_
#define KEY_MAPPER_HPP_

#include "libtcod.hpp"

class KeyMapper {
public:
    static TCOD_key_t LastKey;
    static TCOD_mouse_t LastMousePosition;

    enum struct Action {
        NONE,
        MOVE_N,
        MOVE_NE,
        MOVE_E,
        MOVE_SE,
        MOVE_S,
        MOVE_SW,
        MOVE_W,
        MOVE_NW
    };
    
    static Action GetActionByKey();
};


#endif /* KEY_MAPPER_HPP_ */
