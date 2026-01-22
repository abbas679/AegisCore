#pragma once

#include <string>
#include <cstdint>

namespace aegis::core {

struct Event {
    std::uint64_t id;
    std::string name;

    Event(std::uint64_t id_, std::string name_);
};

} // namespace aegis::core
