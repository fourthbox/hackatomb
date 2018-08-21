#ifndef ARMOR_HPP_
#define ARMOR_HPP_

#include "item.hpp"

class Armor : public Item {
public:
    Armor(std::string const &short_description, std::size_t armor_rating);

private:
    std::size_t armor_rating_;
};

#endif /* ARMOR_HPP_ */
