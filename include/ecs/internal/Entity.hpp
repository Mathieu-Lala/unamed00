/**
 * @file include/ecs/internal/Entity.hpp
 *
 */

#ifndef ENTITY_HPP_
# define ENTITY_HPP_

namespace ecs {

namespace entity {

struct Handler {

    ID m_id;

    Handler(ID id) : m_id(id) { }
    ~Handler() = default;

    template<typename ComponentType, typename... Args>
    Handler &add(Args &&...args)
    {
        World::get()->addComponent<ComponentType>(m_id, std::forward<Args>(args)...);
        return *this;
    }

    template<typename ComponentType>
    ComponentType *get() const
        { return World::get()->getComponent<ComponentType>(m_id); }

};

} // namespace entity

} // namespace ecs

#endif /* !ENTITY_HPP_ */
