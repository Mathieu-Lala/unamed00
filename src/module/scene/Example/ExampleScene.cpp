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

    auto player = world->createEntity()
        .add<CRectShape>(0.0f, 0.0f, 0.05f, 0.05f)
        .add<CVelocity>(0.0f, 0.0f);

    player.add<CWithEvent>([player](const graphic::Event &e){
            auto velocity = player.get<CVelocity>();

            if (e.type == graphic::Event::KEY_PRESSED) {
                switch (e.key.code) {
                    case graphic::KeyBoard::Up: velocity->y = 0.05f; break;
                    case graphic::KeyBoard::Down: velocity->y = -0.05f; break;
                    case graphic::KeyBoard::Left: velocity->x = -0.05f; break;
                    case graphic::KeyBoard::Right: velocity->x = 0.05f; break;
                    default: break;
                }

            } else if (e.type == graphic::Event::KEY_RELEASED) {
                switch (e.key.code) {
                    case graphic::KeyBoard::Up: velocity->y = 0.0f; break;
                    case graphic::KeyBoard::Down: velocity->y = 0.0f; break;
                    case graphic::KeyBoard::Left: velocity->x = 0.0f; break;
                    case graphic::KeyBoard::Right: velocity->x = 0.0f; break;
                    default: break;
                }
            }
        });

    m_player = player.m_id;

    return true;
}

constexpr bool collide(const CRectShape *a, const CRectShape *b)
{
    return a->x < b->x + b->w && a->x + a->w > b->x &&
           a->y < b->y + b->h && a->h + a->y > b->y;
}

void ExampleScene::onUpdate(const std::unique_ptr<ecs::World> &world, float elapsedTime, const graphic::Event &event)
{
    if (event.type != graphic::Event::NONE)
        world->tickSystem<const CWithEvent>([&event](const CWithEvent *action){
            action->callback(event);
        });

    world->tickSystem<CRectShape, CVelocity>([&elapsedTime, &world](CRectShape *shape, CVelocity *velocity) {

        shape->x += velocity->x * elapsedTime / 100.0f;
        shape->y += velocity->y * elapsedTime / 100.0f;

        if (shape->x < -1.0f) { velocity->x *= -1.0f; shape->x = -1.0f; }
        else if (shape->x + shape->w > 1.0f) { velocity->x *= -1.0f; shape->x = 1.0f - shape->w;  }
        if (shape->y < -1.0f) { velocity->y *= -1.0f; shape->y = -1.0f; }
        else if (shape->y + shape->h > 1.0f) { velocity->y *= -1.0f; shape->y = 1.0f - shape->h; }

    });

    const auto withHitBox = world->entitiesWith<CRectShape>();
    for (const auto &entity : withHitBox)
        for (const auto &i : withHitBox)
            if (entity.m_id != i.m_id && collide(entity.get<CRectShape>(), i.get<CRectShape>()))
                world->destroyEntity(entity.m_id);

    world->tickSystem<CVelocity>([this, &world](CVelocity *velocity) {

        if (velocity == world->getEntityHandle(this->m_player).get<CVelocity>()) return;

        velocity->x += ((std::rand() % 3) - 1) / 10000.0f;
        velocity->y += ((std::rand() % 3) - 1) / 10000.0f;

    });
}

unsigned int ExampleScene::getSkyColor()
{
    return 0x000000FF;
}
