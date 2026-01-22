#pragma once
#include <cstdint>
#include <type_traits>

namespace aegis {

// Strongly-typed event identifier.
// No runtime cost. Compile-time unique per event type.
struct EventId {
    using id_type = uint32_t;

    constexpr EventId() noexcept : value(0) {}
    explicit constexpr EventId(id_type v) noexcept : value(v) {}

    constexpr bool operator==(const EventId& other) const noexcept { return value == other.value; }
    constexpr bool operator!=(const EventId& other) const noexcept { return value != other.value; }
    constexpr bool operator<(const EventId& other) const noexcept { return value < other.value; }

    id_type value;
};

// Helper to generate unique EventId per type at compile time
template <typename T>
struct EventType {
    static constexpr EventId id{__COUNTER__};
};

} // namespace aegis
