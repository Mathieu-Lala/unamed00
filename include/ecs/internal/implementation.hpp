/**
 * @file include/ecs/internal/implementation.hpp
 *
 */

#ifndef ECS_INTERNAL_IMPLEMENTATION_HPP_
# define ECS_INTERNAL_IMPLEMENTATION_HPP_

#include <iostream>

namespace ecs {

inline entity::Handler World::createEntity()
{
    entity::ID new_id;

    if (m_freeEntityID.empty()) {
        m_componentMasks.push_back(0);
        m_entities.push_back(false);

        new_id = m_componentMasks.size() - 1;

    } else {
        new_id = m_freeEntityID.top();
        m_freeEntityID.pop();

        m_componentMasks[new_id] = 0;
        m_entities[new_id] = false;
    }

    return { new_id, *this };
}

inline entity::Handler World::getEntityHandle(entity::ID entityID)
{
    return { entityID, *this };
}

inline entity::Handler Iterator::operator*() const
{
    return this->m_list->m_world.getEntityHandle(m_index);
}

inline Iterator &Iterator::operator++()
{
    const auto count = this->m_list->m_world.getEntityCount();

    auto i = this->m_index + 1;
    for (; i < count && (!this->m_list->m_world.isValid(i) ||
        !this->m_list->m_world.hasComponents(i, m_list->m_mask)); i++);
    m_index = i >= count ? MAX_INDEX : i;
    return *this;
}

template<typename... Components>
inline void World::tickSystem(const System<Components...> &f)
{
    this->forEachEntity<Components...>([&f](const entity::Handler &e) {
        f(e.get<Components>()...);
    });
}

};

#endif /* !ECS_INTERNAL_IMPLEMENTATION_HPP_ */
