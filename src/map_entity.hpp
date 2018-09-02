#ifndef MAP_ENTITY_HPP_
#define MAP_ENTITY_HPP_

#include <experimental/optional>

#include "dungeon_factory.hpp"
#include "initiable_object.hpp"
#include "libtcod.hpp"

/**
 Struct to individually locate a position on a map, in a dungeon floor
 */
struct MapLocation {
    std::size_t x_, y_, floor_;
    DungeonCategory dungeon_category_;
    
    MapLocation(DungeonCategory const &dungeon_category, std::size_t const &floor, std::size_t const &x, std::size_t const &y) :
    dungeon_category_ {dungeon_category},
    floor_ {floor},
    x_ {x},
    y_ {y} {
    }
    
    inline bool operator== (const MapLocation &fisrt) {
        return this->x_ == fisrt.x_
        && this->y_ == fisrt.y_
        && this->dungeon_category_ == fisrt.dungeon_category_
        && this->floor_ == fisrt.floor_;
    }
    
    inline std::pair<size_t, size_t> GetPosition() const { return std::make_pair(x_, y_); }
};

typedef std::experimental::optional<MapLocation> MapLocation_opt;

class MapEntity : public InitiableObject {
public:
    inline MapEntity() : map_location_ {std::experimental::nullopt} {}
    inline void Initialize(MapLocation const &map_location, int sprite, TCODColor color, std::string const &name) {
        map_location_ = map_location;
        sprite_ = sprite;
        color_ = color;
        name_ = name;
    }

    virtual ~MapEntity() = 0;
    
    inline std::string GetName() const { return name_; }
    
    inline std::pair<size_t, size_t> GetPosition() const { assert (map_location_); return map_location_->GetPosition(); }
    inline MapLocation const &GetMapLocation() const { assert (map_location_); return *map_location_; }
    
protected:
    MapLocation_opt map_location_;
    int sprite_;        /**< Character used to represent this actor. */
    TCODColor color_;   /**< Color used to represent this actor. */
    std::string name_;  /**< Name of this actor. */

};

inline MapEntity::~MapEntity() {}

#endif /* MAP_ENTITY_HPP_ */
