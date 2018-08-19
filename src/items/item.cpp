#include "item.hpp"

#include "libpmg.hpp"

Item::Item() {
    uuid_ = libpmg::Utils::GenerateUUID();
}
