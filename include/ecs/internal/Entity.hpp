/**
 * @file include/ecs/internal/Entity.hpp
 *
 */

#ifndef ECS_INTERNAL_ENTITY_HPP_
# define ECS_INTERNAL_ENTITY_HPP_

namespace ecs {

namespace entity {

struct Handler {

    ID m_id;
    World &m_world;

    Handler(ID id, World &w) : m_id(id), m_world(w) { }
    ~Handler() = default;

    template<typename ComponentType, typename... Args>
    Handler &add(Args &&...args)
    {
        m_world.addComponent<ComponentType>(m_id, std::forward<Args>(args)...);
        return *this;
    }

    template<typename ComponentType>
    ComponentType *get() const
        { return m_world.getComponent<ComponentType>(m_id); }

    template<typename ComponentType>
    bool own(const ComponentType *component) const noexcept
        { return this->get<ComponentType>() == component; }

};

} // namespace entity

} // namespace ecs

#endif /* !ECS_INTERNAL_ENTITY_HPP_ */
