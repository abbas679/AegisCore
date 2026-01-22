#include "core/Event.h"

namespace aegis::core {

Event::Event(std::uint64_t id_, std::string name_)
    : id(id_), name(std::move(name_)) {}

} // namespace aegis::core
