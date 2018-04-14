#ifndef TILE_HPP_
#define TILE_HPP_

#include "libpmg.hpp"

class Tile : public libpmg::Tile {
public:
    Tile(std::shared_ptr<libpmg::Tile> other);
};

typedef std::shared_ptr<Tile> Tile_p;

#endif /* TILE_HPP_ */
