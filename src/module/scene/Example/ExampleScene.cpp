/**
 * @file src/module/scene/example/ExampleScene.cpp
 *
 */

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include <data/Component.hpp>

#include "ExampleScene.hpp"

void ExampleScene::restartParty(const std::unique_ptr<ecs::World> &world)
{
    world->clearAll();

    world->createEntity()
    .add<CWithEvent>([this, &world](const graphic::Event &e) {
        if (e.type == graphic::Event::KEY_PRESSED && e.key.code == graphic::KeyBoard::R)
            this->restartParty(world);
    });

    m_gameClock = 0;
    m_level = 0;

    auto player = world->createEntity(); player
    .add<CRectShape>(0.0f, 0.0f, 0.05f, 0.05f)
    .add<CVelocity>(0.0f, 0.0f)
    .add<CWithEvent>([player](const graphic::Event &e){
        auto velocity = player.get<CVelocity>();

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
            .add<CRectShape>(x / 2.0f, y / 2.0f, 1 / size, 1 / size)
            .add<CVelocity>(x / 100.0f, y / 100.0f);
    }

    world->flush();
}

bool ExampleScene::onCreate(const std::unique_ptr<ecs::World> &world)
{
    this->restartParty(world);
    return true;
}

constexpr bool collide(const CRectShape *a, const CRectShape *b)
{
    return a && b && a != b &&
        a->x < b->x + b->w && a->x + a->w > b->x &&
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

    auto player = world->getEntityHandle(this->m_player);

    world->tickSystem<CVelocity>([this, &player](CVelocity *velocity) {
        if (player.own(velocity)) return;
        velocity->x += ((std::rand() % 3) - 1) / 10000.0f;
        velocity->y += ((std::rand() % 3) - 1) / 10000.0f;
    });

    for (const auto &entity : world->entitiesWith<const CRectShape>())
        if (collide(player.get<const CRectShape>(), entity.get<const CRectShape>())) {
            std::cout << "you died :(" << std::endl << "Your score: " << this->m_level << std::endl;
            this->restartParty(world);
            break;
        }

    this->m_gameClock += elapsedTime;
    if (this->m_gameClock >= 5000) {
        m_gameClock = 0.0f;
        this->m_level++;
        this->spawnEnnemies(world, this->m_level * 10);
    }
}

unsigned int ExampleScene::getSkyColor()
{
    return 0x000000FF;
}
