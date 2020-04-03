/**
 * @file include/ecs/internal/World.hpp
 *
 */

#ifndef ECS_INTERNAL_WORLD_HPP_
# define ECS_INTERNAL_WORLD_HPP_

# include <algorithm>
# include <functional>
# include <memory>
# include <queue>
# include <vector>

namespace ecs {

class World {
public:
    World() = default;
    ~World() = default;

    entity::Handler createEntity();
    void destroyEntity(entity::ID);

    entity::Handler getEntityHandle(entity::ID);

    bool isValid(entity::ID entityID) const
        { return m_entities[entityID]; }

    auto getEntityCount() const
        { return m_componentMasks.size(); }

    bool hasComponents(entity::ID entityID, component::Mask mask) const
        { return (m_componentMasks[entityID] & mask) == mask; }

    template<typename ComponentType, typename... Args>
    void addComponent(entity::ID, Args &&...);

    template<typename... Components>
    using System = std::function<void(std::add_pointer_t<Components>...)>;

    template<typename... Components>
    void tickSystem(const System<Components...> &);

    template<typename ComponentType>
    ComponentType *getComponent(entity::ID entityID)
        { return getPool<std::decay_t<ComponentType>>(false)->get(entityID); }

    void flush()
        { m_entities.assign(m_entities.size(), true); }

private:

    // boolean value : valid entity or not
    std::vector<bool> m_entities;

    // list of entity id re-usable by the world // allow continuous array
    std::priority_queue<entity::ID, std::vector<entity::ID>, std::greater<>> m_freeEntityID;

    // continuous array of mask of component corresponding at each entity
    std::vector<component::Mask> m_componentMasks;

    // emplacement of the real component in memory
    std::array<std::unique_ptr<component::PoolBase>, component::MAX> m_componentPools;

    template<typename ComponentType>
    component::Pool<ComponentType> *getPool(bool alloc = true);

    template<typename... Components>
    EntityList entitiesWith()
        { return { component::getMask<Components...>(), *this }; }

    template<typename... Components>
    void forEachEntity(const std::function<void(const entity::Handler &)> &);
};

// Implementation

inline void World::destroyEntity(entity::ID entityID)
{
    for (component::ID compID = 0; compID < m_componentPools.size(); ++compID) {
        const auto hasComponent = (m_componentMasks[entityID] & component::maskFromID(compID)) > 0;
        if (m_componentPools[compID] && hasComponent)
            m_componentPools[compID]->remove(entityID);
    }
    m_componentMasks[entityID] = 0;
    m_freeEntityID.push(entityID);
}

template<typename ComponentType, typename... Args>
inline void World::addComponent(entity::ID entityID, Args &&...args)
{
    m_componentMasks[entityID] |= component::getMask<ComponentType>();
    getPool<ComponentType>()->add(entityID, std::forward<Args>(args)...);
}

template<typename ComponentType>
inline component::Pool<ComponentType> *World::getPool(bool alloc)
{
    const auto compID = component::getID<ComponentType>();
    if (alloc && !m_componentPools[compID])
        m_componentPools[compID] = std::make_unique<component::Pool<ComponentType>>();
    return dynamic_cast<component::Pool<ComponentType> *>(m_componentPools[compID].get());
}

template<typename... Components>
inline void World::forEachEntity(const std::function<void(const entity::Handler &)> &f)
{
    const auto entityList = this->entitiesWith<Components...>();
    std::for_each(entityList.begin(), entityList.end(), f);
}

} // namespace ecs

#endif /* !ECS_INTERNAL_WORLD_HPP_ */
