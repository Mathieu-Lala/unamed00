/**
 * @file include/scene/IScene.hpp
 *
 */

#ifndef ISCENE_HPP_
# define ISCENE_HPP_

# include <ecs/ECS.hpp>

namespace scene {

class IScene {
public:
    using Ctor = IScene *(*)();
    using Dtor = void(*)(IScene *);

    virtual ~IScene() = default;

    virtual bool onCreate(const std::unique_ptr<ecs::World> &) = 0;
    virtual void onUpdate(const std::unique_ptr<ecs::World> &) = 0;

    virtual unsigned int getSkyColor() = 0;

protected:
};

} // namespace scene

#endif /* !ISCENE_HPP_ */
