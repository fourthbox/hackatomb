#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include "item.hpp"

class Weapon : public Item {
public:
    Weapon(std::string const &short_description, bool two_handed, std::size_t damage_mod, std::size_t speed_mod);
    
private:
    bool two_handed_;
    std::size_t damage_mod_, speed_mod_;
};

#endif /* WEAPON_HPP_ */
