/**
 * @file src/module/scene/example/ExampleScene.cpp
 *
 */

#include <cmath>

#include <data/Component.hpp>

#include "ExampleScene.hpp"

bool ExampleScene::onCreate(const std::unique_ptr<ecs::World> &world)
{
    constexpr float size = 100.0f;

    constexpr float count = 200.0f;
    for (int i = 0; i != count; i++) {
        const auto x = std::cos(i * 2 * M_PI / count);
        const auto y = std::sin(i * 2 * M_PI / count);

        world->createEntity()
            .add<CRectShape>(x / 2.0f, y / 2.0f, 1 / size, 1 / size)
            .add<CVelocity>(x / 100.0f, y / 100.0f);
    }

    return true;
}

constexpr bool collide(const CRectShape *a, const CRectShape *b)
{
    return a->x < b->x + b->w && a->x + a->w > b->x &&
           a->y < b->y + b->h && a->h + a->y > b->y;
}

void ExampleScene::onUpdate(const std::unique_ptr<ecs::World> &world, float elapsedTime)
{
    world->tickSystem<CRectShape, CVelocity>([&elapsedTime, &world](CRectShape *shape, CVelocity *velocity) {

        shape->x += velocity->x * elapsedTime / 100.0f;
        shape->y += velocity->y * elapsedTime / 100.0f;

        for (const auto &i : world->entitiesWith<CRectShape>())
            if (const auto other = i.get<CRectShape>(); other != shape && collide(other, shape))
                { velocity->x *= -1.0f; velocity->y *= -1.0f; }

        if (shape->x < -1.0f) { velocity->x *= -1.0f; shape->x = -1.0f; }
        else if (shape->x + shape->w > 1.0f) { velocity->x *= -1.0f; shape->x = 1.0f - shape->w;  }
        if (shape->y < -1.0f) { velocity->y *= -1.0f; shape->y = -1.0f; }
        else if (shape->y + shape->h > 1.0f) { velocity->y *= -1.0f; shape->y = 1.0f - shape->h; }

    });

    world->tickSystem<CVelocity>([](CVelocity *velocity) {

        velocity->x += ((std::rand() % 3) - 1) / 10000.0f;
        velocity->y += ((std::rand() % 3) - 1) / 10000.0f;

    });
}

unsigned int ExampleScene::getSkyColor()
{
    return 0x000000FF;
}
