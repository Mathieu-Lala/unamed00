/**
 * @file src/module/graphic/AbstractGLFW/Keyboard.hpp
 *
 */

#ifndef ABSTRACT_GLFW_KEYBOARD
# define ABSTRACT_GLFW_KEYBOARD

#include <GLFW/glfw3.h>

#include <graphic/Key.hpp>

#include <iostream>

constexpr graphic::KeyBoard::Key toValidKeyCode(int glfw_scancode)
{
    using namespace graphic;

    switch (glfw_scancode) {
        case GLFW_KEY_SPACE: return KeyBoard::Space;
        //case GLFW_KEY_APOSTROPHE: return KeyBoard::;
        case GLFW_KEY_COMMA: return KeyBoard::Comma;
        //case GLFW_KEY_MINUS: return KeyBoard::;
        case GLFW_KEY_PERIOD: return KeyBoard::Period;
        case GLFW_KEY_SLASH: return KeyBoard::Slash;
        case GLFW_KEY_0: return KeyBoard::Num0;
        case GLFW_KEY_1: return KeyBoard::Num1;
        case GLFW_KEY_2: return KeyBoard::Num2;
        case GLFW_KEY_3: return KeyBoard::Num3;
        case GLFW_KEY_4: return KeyBoard::Num4;
        case GLFW_KEY_5: return KeyBoard::Num5;
        case GLFW_KEY_6: return KeyBoard::Num6;
        case GLFW_KEY_7: return KeyBoard::Num7;
        case GLFW_KEY_8: return KeyBoard::Num8;
        case GLFW_KEY_9: return KeyBoard::Num9;
        case GLFW_KEY_SEMICOLON: return KeyBoard::Semicolon;
        case GLFW_KEY_EQUAL: return KeyBoard::Equal;
        case GLFW_KEY_A: return KeyBoard::A;
        case GLFW_KEY_B: return KeyBoard::B;
        case GLFW_KEY_C: return KeyBoard::C;
        case GLFW_KEY_D: return KeyBoard::D;
        case GLFW_KEY_E: return KeyBoard::E;
        case GLFW_KEY_F: return KeyBoard::F;
        case GLFW_KEY_G: return KeyBoard::G;
        case GLFW_KEY_H: return KeyBoard::H;
        case GLFW_KEY_I: return KeyBoard::I;
        case GLFW_KEY_J: return KeyBoard::J;
        case GLFW_KEY_K: return KeyBoard::K;
        case GLFW_KEY_L: return KeyBoard::L;
        case GLFW_KEY_M: return KeyBoard::M;
        case GLFW_KEY_N: return KeyBoard::N;
        case GLFW_KEY_O: return KeyBoard::O;
        case GLFW_KEY_P: return KeyBoard::P;
        case GLFW_KEY_Q: return KeyBoard::Q;
        case GLFW_KEY_R: return KeyBoard::R;
        case GLFW_KEY_S: return KeyBoard::S;
        case GLFW_KEY_T: return KeyBoard::T;
        case GLFW_KEY_U: return KeyBoard::U;
        case GLFW_KEY_V: return KeyBoard::V;
        case GLFW_KEY_W: return KeyBoard::W;
        case GLFW_KEY_X: return KeyBoard::X;
        case GLFW_KEY_Y: return KeyBoard::Y;
        case GLFW_KEY_Z: return KeyBoard::Z;
        case GLFW_KEY_LEFT_BRACKET: return KeyBoard::LBracket;
        case GLFW_KEY_BACKSLASH: return KeyBoard::Backslash;
        case GLFW_KEY_RIGHT_BRACKET: return KeyBoard::RBracket;
        //case GLFW_KEY_GRAVE_ACCENT: return KeyBoard::;
        //case GLFW_KEY_WORLD_1: return KeyBoard::;
        //case GLFW_KEY_WORLD_2: return KeyBoard::;
        case GLFW_KEY_ESCAPE: return KeyBoard::Escape;
        case GLFW_KEY_ENTER: return KeyBoard::Enter;
        case GLFW_KEY_TAB: return KeyBoard::Tab;
        case GLFW_KEY_BACKSPACE: return KeyBoard::Backspace;
        case GLFW_KEY_INSERT: return KeyBoard::Insert;
        case GLFW_KEY_DELETE: return KeyBoard::Delete;
        case GLFW_KEY_RIGHT: return KeyBoard::Right;
        case GLFW_KEY_LEFT: return KeyBoard::Left;
        case GLFW_KEY_DOWN: return KeyBoard::Down;
        case GLFW_KEY_UP: return KeyBoard::Up;
        case GLFW_KEY_PAGE_UP: return KeyBoard::PageUp;
        case GLFW_KEY_PAGE_DOWN: return KeyBoard::PageDown;
        case GLFW_KEY_HOME: return KeyBoard::Home;
        case GLFW_KEY_END: return KeyBoard::End;
        //case GLFW_KEY_CAPS_LOCK: return KeyBoard::;
        //case GLFW_KEY_SCROLL_LOCK: return KeyBoard::;
        //case GLFW_KEY_NUM_LOCK: return KeyBoard::;
        //case GLFW_KEY_PRINT_SCREEN: return KeyBoard::;
        case GLFW_KEY_PAUSE: return KeyBoard::Pause;
        case GLFW_KEY_F1: return KeyBoard::F1;
        case GLFW_KEY_F2: return KeyBoard::F2;
        case GLFW_KEY_F3: return KeyBoard::F3;
        case GLFW_KEY_F4: return KeyBoard::F4;
        case GLFW_KEY_F5: return KeyBoard::F5;
        case GLFW_KEY_F6: return KeyBoard::F6;
        case GLFW_KEY_F7: return KeyBoard::F7;
        case GLFW_KEY_F8: return KeyBoard::F8;
        case GLFW_KEY_F9: return KeyBoard::F9;
        case GLFW_KEY_F10: return KeyBoard::F10;
        case GLFW_KEY_F11: return KeyBoard::F11;
        case GLFW_KEY_F12: return KeyBoard::F12;
        case GLFW_KEY_F13: return KeyBoard::F13;
        case GLFW_KEY_F14: return KeyBoard::F14;
        case GLFW_KEY_F15: return KeyBoard::F15;
        //case GLFW_KEY_F16: return KeyBoard::F16;
        //case GLFW_KEY_F17: return KeyBoard::F17;
        //case GLFW_KEY_F18: return KeyBoard::F18;
        //case GLFW_KEY_F19: return KeyBoard::F19;
        //case GLFW_KEY_F20: return KeyBoard::F20;
        //case GLFW_KEY_F21: return KeyBoard::F21;
        //case GLFW_KEY_F22: return KeyBoard::F22;
        //case GLFW_KEY_F23: return KeyBoard::F23;
        //case GLFW_KEY_F24: return KeyBoard::F24;
        //case GLFW_KEY_F25: return KeyBoard::F25;
        case GLFW_KEY_KP_0: return KeyBoard::Numpad0;
        case GLFW_KEY_KP_1: return KeyBoard::Numpad1;
        case GLFW_KEY_KP_2: return KeyBoard::Numpad2;
        case GLFW_KEY_KP_3: return KeyBoard::Numpad3;
        case GLFW_KEY_KP_4: return KeyBoard::Numpad4;
        case GLFW_KEY_KP_5: return KeyBoard::Numpad5;
        case GLFW_KEY_KP_6: return KeyBoard::Numpad6;
        case GLFW_KEY_KP_7: return KeyBoard::Numpad7;
        case GLFW_KEY_KP_8: return KeyBoard::Numpad8;
        case GLFW_KEY_KP_9: return KeyBoard::Numpad9;
        //case GLFW_KEY_KP_DECIMAL: KeyBoard::;
        case GLFW_KEY_KP_DIVIDE: return KeyBoard::Divide;
        case GLFW_KEY_KP_MULTIPLY: return KeyBoard::Multiply;
        case GLFW_KEY_KP_SUBTRACT: return KeyBoard::Subtract;
        case GLFW_KEY_KP_ADD: return KeyBoard::Add;
        //case GLFW_KEY_KP_ENTER: return KeyBoard::Enter;
        //case GLFW_KEY_KP_EQUAL: return KeyBoard::Equal;
        case GLFW_KEY_LEFT_SHIFT: return KeyBoard::LShift;
        case GLFW_KEY_LEFT_CONTROL: return KeyBoard::LControl;
        case GLFW_KEY_LEFT_ALT: return KeyBoard::LAlt;
        //case GLFW_KEY_LEFT_SUPER: return KeyBoard::;
        case GLFW_KEY_RIGHT_SHIFT: return KeyBoard::RShift;
        case GLFW_KEY_RIGHT_CONTROL: return KeyBoard::RControl;
        case GLFW_KEY_RIGHT_ALT: return KeyBoard::RAlt;
        //case GLFW_KEY_RIGHT_SUPER: return KeyBoard::;
        case GLFW_KEY_MENU: return KeyBoard::Menu;

        case GLFW_KEY_UNKNOWN:
        default: return graphic::KeyBoard::Unknown;
    }
}

#endif /* !ABSTRACT_GLFW_KEYBOARD */
