/**
 * @file include/ecs/internal/implementation.hpp
 *
 */

#ifndef IMPLEMENTATION_HPP_
# define IMPLEMENTATION_HPP_

namespace ecs {

entity::Handler World::createEntity()
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

    return { new_id };
}

entity::Handler World::getEntityHandle(entity::ID entityID)
{
    return { entityID };
}

entity::Handler Iterator::operator*() const
{
    return World::get()->getEntityHandle(m_index);
}

Iterator &Iterator::operator++()
{
    const auto &world = *World::get().get();
    const auto count = world.getEntityCount();

    auto i = this->m_index + 1;
    for (; i < count && (!world.isValid(i) || !world.hasComponents(i, m_list->m_mask)); i++);
    m_index = i >= count ? MAX_INDEX : i;
    return *this;
}

template<typename... Components>
void World::tickSystem(const System<Components...> &f)
{
    this->forEachEntity<Components...>([&f](const entity::Handler &e) {
        f(e.get<Components>()...);
    });
}

};

#endif /* !IMPLEMENTATION_HPP_ */
