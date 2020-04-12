include(src/module/graphic/AbstractSFML/AbstractSFML.cmake)
make_module_sfml("abstract_sfml" SHARED)

include(src/module/graphic/AbstractGLFW/AbstractGLFW.cmake)
make_module_glfw("abstract_glfw" SHARED)

include(src/module/scene/Example/Example.cmake)
make_scene_example("scene_example" SHARED)

include(src/module/scene/Collision/Collision.cmake)
make_scene_collision("scene_collision" SHARED)
