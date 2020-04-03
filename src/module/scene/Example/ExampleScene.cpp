/**
 * @file src/module/scene/example/ExampleScene.cpp
 *
 */

#include <data/Component.hpp>

#include "ExampleScene.hpp"

bool ExampleScene::onCreate(const std::unique_ptr<ecs::World> &world)
{
    world->createEntity().add<CShape>(0, 0, 1, 1);
    world->createEntity().add<CShape>(-1, -1, 1, 1);

    return true;
}

void ExampleScene::onUpdate(const std::unique_ptr<ecs::World> &)
{
}

unsigned int ExampleScene::getSkyColor()
{
    return 0xFF00FFFFu;
}
