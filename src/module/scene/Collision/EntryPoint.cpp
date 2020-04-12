/**
 * @file src/module/scene/Collision/EntryPoint.cpp
 *
 */

#include <config/api.hpp>

#include "CollisionScene.hpp"

EXTERN_C DECLSPEC scene::IScene *createScene()
{
    return new CollisionScene;
}

EXTERN_C DECLSPEC void destroyScene(scene::IScene *w)
{
    delete w;
}
