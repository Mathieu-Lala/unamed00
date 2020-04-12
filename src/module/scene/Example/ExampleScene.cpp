/**
 * @file src/module/scene/Example/ExampleScene.cpp
 *
 */

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include <data/Component.hpp>

#include "ExampleScene.hpp"

bool ExampleScene::onCreate(const std::unique_ptr<ecs::World> &world)
{
    this->restartParty(world);
    return true;
}

void ExampleScene::onUpdate(const std::unique_ptr<ecs::World> &world, float elapsedTime, const graphic::Event &event)
{
    if (event.type != graphic::Event::NONE)
        world->tickSystem<const data::CWithEvent>([&event](const data::CWithEvent *action) {
            action->callback(event);
        });

    world->tickSystem<data::CRectShape, data::CVelocity>([&elapsedTime, &world]
    (data::CRectShape *shape, data::CVelocity *velocity) {

        shape->x += velocity->x * elapsedTime / 100.0f;
        shape->y += velocity->y * elapsedTime / 100.0f;

        if (shape->x < -1.0f) { velocity->x *= -1.0f; shape->x = -1.0f; }
        else if (shape->x + shape->w > 1.0f) { velocity->x *= -1.0f; shape->x = 1.0f - shape->w;  }
        if (shape->y < -1.0f) { velocity->y *= -1.0f; shape->y = -1.0f; }
        else if (shape->y + shape->h > 1.0f) { velocity->y *= -1.0f; shape->y = 1.0f - shape->h; }

    });

    const auto player = world->getEntityHandle(this->m_player);

    world->tickSystem<data::CVelocity>([this, &player](data::CVelocity *velocity) {
        if (player.own(velocity)) return;
        velocity->x += ((std::rand() % 3) - 1) / 10000.0f;
        velocity->y += ((std::rand() % 3) - 1) / 10000.0f;
    });

    for (const auto &entity : world->entitiesWith<const data::CRectShape>())
        if (player.get<const data::CRectShape>()->collide(entity.get<const data::CRectShape>())) {
            std::cout << "you died :(" << std::endl << "Your score: " << this->m_level << std::endl;
            return this->restartParty(world);
        }

    this->m_gameClock += elapsedTime;
    if (this->m_gameClock >= 5000) {
        m_gameClock = 0.0f;
        this->m_level++;
        this->spawnEnnemies(world, this->m_level * 10);
    }

    player.get<data::CColor>()->a = (5000 - this->m_gameClock) / 5000.0f;
}

void ExampleScene::restartParty(const std::unique_ptr<ecs::World> &world)
{
    world->clearAll();

    m_gameClock = 0;
    m_level = 0;

    world->createEntity()
    .add<data::CWithEvent>([this, &world](const graphic::Event &e) {
        if (e.type == graphic::Event::KEY_PRESSED && e.key.code == graphic::KeyBoard::R)
            this->restartParty(world);
    });

    auto player = world->createEntity(); player
    .add<data::CRectShape>(0.0f, 0.0f, 0.05f, 0.05f)
    .add<data::CVelocity>(0.0f, 0.0f)
    .add<data::CColor>(1.0f, 1.0f, 1.0f, 1.0f)
    .add<data::CWithEvent>([player](const graphic::Event &e){
        auto velocity = player.get<data::CVelocity>();

        if (e.type == graphic::Event::KEY_PRESSED || e.type == graphic::Event::KEY_RELEASED) {
            auto press = e.type == graphic::Event::KEY_PRESSED;
            switch (e.key.code) {
                case graphic::KeyBoard::Up:    velocity->y = press ?  0.05f : 0.0f; break;
                case graphic::KeyBoard::Down:  velocity->y = press ? -0.05f : 0.0f; break;
                case graphic::KeyBoard::Left:  velocity->x = press ? -0.05f : 0.0f; break;
                case graphic::KeyBoard::Right: velocity->x = press ?  0.05f : 0.0f; break;
                default: break;
            }
        }
    });
    this->m_player = player.m_id;

    this->spawnEnnemies(world, 10);
}

void ExampleScene::spawnEnnemies(const std::unique_ptr<ecs::World> &world, int count)
{
    constexpr float size = 100.0f;

    for (int i = 0; i != count; i++) {
        const auto x = std::cos(i * 2 * M_PI / static_cast<float>(count));
        const auto y = std::sin(i * 2 * M_PI / static_cast<float>(count));

        world->createEntity()
            .add<data::CRectShape>(x / 2.0f, y / 2.0f, 1 / size, 1 / size)
            .add<data::CVelocity>(x / 100.0f, y / 100.0f);
    }

    world->flush();
}
