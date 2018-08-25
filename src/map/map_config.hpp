#ifndef MAP_CONFIG_HPP_
#define MAP_CONFIG_HPP_

#include <cstring>

struct MapConfig {
    std::size_t experience_yield_;
    
    MapConfig(size_t experience_yield) :
    experience_yield_ {experience_yield} {
    }
};

#endif /* MAP_CONFIG_HPP_ */
