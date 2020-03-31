/**
 * @file include/ecs/ECS.hpp
 * @brief header-only ecs - do not include the ./internal files yourself
 * made thanks to https://github.com/pfirsich/cpp-ecs
 */

#ifndef ECS_HPP_
# define ECS_HPP_

# include <cinttypes>

namespace ecs {
namespace entity {

using ID = std::size_t;

}
}

# include "internal/Component.hpp"
# include "internal/Pool.hpp"
# include "internal/List.hpp"
# include "internal/World.hpp"
# include "internal/Entity.hpp"

// as the headers include each others, some implementation
// need to be put in a third-party file
# include "internal/implementation.hpp"

#endif /* !ECS_HPP_ */
