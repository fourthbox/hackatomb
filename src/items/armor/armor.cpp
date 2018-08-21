#include "armor.hpp"

Armor::Armor(std::string const &short_description, std::size_t armor_rating) :
Item(short_description),
armor_rating_ {armor_rating} {
}
