#include "weapon.hpp"

Weapon::Weapon(std::string const &short_description, bool two_handed, std::size_t damage_mod, std::size_t speed_mod) :
Item (short_description),
two_handed_ {two_handed},
damage_mod_ {damage_mod},
speed_mod_ {speed_mod} {
}
