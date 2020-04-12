/**
 * @file src/module/scene/Collision/CollisionScene.cpp
 *
 */

#include "CollisionScene.hpp"

bool CollisionScene::onCreate(const std::unique_ptr<ecs::World> &)
{
    return true;
}

void CollisionScene::onUpdate(const std::unique_ptr<ecs::World> &, float, const graphic::Event &)
{
}
