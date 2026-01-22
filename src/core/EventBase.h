#pragma once
#include "EventId.h"
#include <cstdint>
#include <chrono>

namespace aegis {

// Base class for all events.
// No virtual functions for performance.
// Holds metadata only; payload goes in derived structs.
struct EventBase {
    using timestamp_t = std::chrono::steady_clock::time_point;

    constexpr EventBase() noexcept 
        : type_id(EventId{}), timestamp(std::chrono::steady_clock::now()) {}

    explicit constexpr EventBase(EventId id) noexcept 
        : type_id(id), timestamp(std::chrono::steady_clock::now()) {}

    EventId type_id;
    timestamp_t timestamp;
};

} // namespace aegis
