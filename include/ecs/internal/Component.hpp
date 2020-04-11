/**
 * @file include/ecs/internal/Component.hpp
 *
 */

#ifndef ECS_INTERNAL_COMPONENT_HPP_
# define ECS_INTERNAL_COMPONENT_HPP_

# include <cassert>
# include <cinttypes>
# include <limits>
# include <type_traits>

# include "config/api.hpp"

namespace ecs {

namespace component {

using Mask = std::uint64_t;
static_assert(std::is_unsigned_v<Mask>, "Mask type must be unsigned");

constexpr auto MAX = std::numeric_limits<Mask>::digits;

using ID = std::uint64_t;

namespace {
ID counter = 0ul;

template<typename ComponentType>
ID getID() noexcept
{
    static auto id = counter++;
    assert(id < MAX);
    return id;
}

} // anonymous namespace

constexpr Mask maskFromID(ID id) noexcept
{
    return 1ul << id;
}

template<typename... Args>
constexpr Mask getMask() noexcept
{
    return (... | maskFromID(getID<std::decay_t<Args>>()));
}

} // namespace component

} // namespace ecs

#endif /* !ECS_INTERNAL_COMPONENT_HPP_ */
