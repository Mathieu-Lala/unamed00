/**
 * @file src/module/scene/example/ExampleScene.cpp
 *
 */

#include <data/Component.hpp>

#include "ExampleScene.hpp"

bool ExampleScene::onCreate(const std::unique_ptr<ecs::World> &world)
{
    world->createEntity().add<CRectShape>(0.0f, 0.0f, 0.1f, 0.1f);

    world->createEntity()
        .add<CRectShape>(-1.0f, -1.0f, 0.1f, 0.1f)
        .add<CVelocity>(0.1f, 0.1f);

    return true;
}

void ExampleScene::onUpdate(const std::unique_ptr<ecs::World> &world)
{
    world->tickSystem<CRectShape, CVelocity>([](CRectShape *shape, CVelocity *velocity) {

        shape->x += velocity->x;
        shape->y += velocity->y;

        if (shape->x < -1.0f || shape->x + shape->w > 1.0f) velocity->x *= -1.0f;
        if (shape->y < -1.0f || shape->y + shape->h > 1.0f) velocity->y *= -1.0f;

    });

    world->tickSystem<CVelocity>([](CVelocity *velocity) {

        velocity->x += ((std::rand() % 3) - 1) / 1000.0f;
        velocity->y += ((std::rand() % 3) - 1) / 1000.0f;

    });
}

unsigned int ExampleScene::getSkyColor()
{
    return 0xFF00FFFFu;
}
