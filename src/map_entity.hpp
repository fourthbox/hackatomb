#ifndef MAP_ENTITY_HPP_
#define MAP_ENTITY_HPP_

#include "libtcod.hpp"
#include "initiable_object.hpp"

class MapEntity : public InitiableObject {
public:    
    inline void Initialize(std::size_t x, std::size_t y, int sprite, TCODColor color, std::string const &name) {
        x_ = x;
        y_ = y;
        sprite_ = sprite;
        color_ = color;
        name_ = name;
    }

    virtual ~MapEntity() = 0;
    
    inline std::string GetName() const { return name_; }
    inline std::pair<size_t, size_t> GetPosition() const { return std::make_pair(x_, y_); }

protected:
    std::size_t x_, y_;      /**< Location on the current map. */
    int sprite_;        /**< Character used to represent this actor. */
    TCODColor color_;   /**< Color used to represent this actor. */
    std::string name_;  /**< Name of this actor. */

};

inline MapEntity::~MapEntity() {}

#endif /* MAP_ENTITY_HPP_ */
