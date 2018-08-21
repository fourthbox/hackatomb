#include "item.hpp"

#include "libpmg.hpp"

Item::Item(std::string const &short_description) :
uuid_ {libpmg::Utils::GenerateUUID()},
short_description_ {short_description} {
}
