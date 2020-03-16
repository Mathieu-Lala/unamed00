include(src/module/graphic/AbstractSFML/AbstractSFML.cmake)
set(MODULE_SFML "abstract_sfml")
make_module_sfml(${MODULE_SFML} SHARED)

include(src/module/graphic/AbstractGLFW/AbstractGLFW.cmake)
set(MODULE_GLFW "abstract_glfw")
make_module_glfw(${MODULE_GLFW} SHARED)
