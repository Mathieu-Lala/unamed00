/**
 * @file src/module/scene/Collision/CollisionScene.hpp
 *
 */

#ifndef COLLISIONCENE_HPP_
# define COLLISIONCENE_HPP_

# include <scene/IScene.hpp>

class CollisionScene : public scene::IScene {
public:
    CollisionScene() = default;
    virtual ~CollisionScene() = default;

    bool onCreate(const std::unique_ptr<ecs::World> &) override;
    void onUpdate(const std::unique_ptr<ecs::World> &, float, const graphic::Event &) override;

    unsigned int getSkyColor() override
        { return 0xFF00FFFF; }

protected:
private:

};

#endif
