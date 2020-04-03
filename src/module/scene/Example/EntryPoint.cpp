/**
 * @file src/module/scene/example/EntryPoint.cpp
 *
 */

#include <config/api.hpp>

#include "ExampleScene.hpp"

EXTERN_C DECLSPEC scene::IScene *createScene()
{
    return new ExampleScene;
}

EXTERN_C DECLSPEC void destroyScene(scene::IScene *w)
{
    delete w;
}
