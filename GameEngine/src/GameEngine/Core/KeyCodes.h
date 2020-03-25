#pragma once

namespace GE {
    typedef enum class KeyCode : uint16_t
    {
        // From glfw3.h
        Space = 32,
        Apostrophe = 39, /* ' */
        Comma = 44, /* , */
        Minus = 45, /* - */
        Period = 46, /* . */
        Slash = 47, /* / */

        D0 = 48, /* 0 */
        D1 = 49, /* 1 */
        D2 = 50, /* 2 */
        D3 = 51, /* 3 */
        D4 = 52, /* 4 */
        D5 = 53, /* 5 */
        D6 = 54, /* 6 */
        D7 = 55, /* 7 */
        D8 = 56, /* 8 */
        D9 = 57, /* 9 */

        Semicolon = 59, /* ; */
        Equal = 61, /* = */

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LeftBracket = 91,  /* [ */
        Backslash = 92,  /* \ */
        RightBracket = 93,  /* ] */
        GraveAccent = 96,  /* ` */

        World1 = 161, /* non-US #1 */
        World2 = 162, /* non-US #2 */

        /* Function keys */
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        /* Keypad */
        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDecimal = 330,
        KPDivide = 331,
        KPMultiply = 332,
        KPSubtract = 333,
        KPAdd = 334,
        KPEnter = 335,
        KPEqual = 336,

        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftSuper = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightSuper = 347,
        Menu = 348
    } Key;

    inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
    {
        os << static_cast<int32_t>(keyCode);
        return os;
    }
}


// From glfw3.h
#define GE_KEY_SPACE           ::GE::Key::Space
#define GE_KEY_APOSTROPHE      ::GE::Key::Apostrophe    /* ' */
#define GE_KEY_COMMA           ::GE::Key::Comma         /* , */
#define GE_KEY_MINUS           ::GE::Key::Minus         /* - */
#define GE_KEY_PERIOD          ::GE::Key::Period        /* . */
#define GE_KEY_SLASH           ::GE::Key::Slash         /* / */
#define GE_KEY_0               ::GE::Key::D0
#define GE_KEY_1               ::GE::Key::D1
#define GE_KEY_2               ::GE::Key::D2
#define GE_KEY_3               ::GE::Key::D3
#define GE_KEY_4               ::GE::Key::D4
#define GE_KEY_5               ::GE::Key::D5
#define GE_KEY_6               ::GE::Key::D6
#define GE_KEY_7               ::GE::Key::D7
#define GE_KEY_8               ::GE::Key::D8
#define GE_KEY_9               ::GE::Key::D9
#define GE_KEY_SEMICOLON       ::GE::Key::Semicolon     /* ; */
#define GE_KEY_EQUAL           ::GE::Key::Equal         /* = */
#define GE_KEY_A               ::GE::Key::A
#define GE_KEY_B               ::GE::Key::B
#define GE_KEY_C               ::GE::Key::C
#define GE_KEY_D               ::GE::Key::D
#define GE_KEY_E               ::GE::Key::E
#define GE_KEY_F               ::GE::Key::F
#define GE_KEY_G               ::GE::Key::G
#define GE_KEY_H               ::GE::Key::H
#define GE_KEY_I               ::GE::Key::I
#define GE_KEY_J               ::GE::Key::J
#define GE_KEY_K               ::GE::Key::K
#define GE_KEY_L               ::GE::Key::L
#define GE_KEY_M               ::GE::Key::M
#define GE_KEY_N               ::GE::Key::N
#define GE_KEY_O               ::GE::Key::O
#define GE_KEY_P               ::GE::Key::P
#define GE_KEY_Q               ::GE::Key::Q
#define GE_KEY_R               ::GE::Key::R
#define GE_KEY_S               ::GE::Key::S
#define GE_KEY_T               ::GE::Key::T
#define GE_KEY_U               ::GE::Key::U
#define GE_KEY_V               ::GE::Key::V
#define GE_KEY_W               ::GE::Key::W
#define GE_KEY_X               ::GE::Key::X
#define GE_KEY_Y               ::GE::Key::Y
#define GE_KEY_Z               ::GE::Key::Z
#define GE_KEY_LEFT_BRACKET    ::GE::Key::LeftBracket   /* [ */
#define GE_KEY_BACKSLASH       ::GE::Key::Backslash     /* \ */
#define GE_KEY_RIGHT_BRACKET   ::GE::Key::RightBracket  /* ] */
#define GE_KEY_GRAVE_ACCENT    ::GE::Key::GraveAccent   /* ` */
#define GE_KEY_WORLD_1         ::GE::Key::World1        /* non-US #1 */
#define GE_KEY_WORLD_2         ::GE::Key::World2        /* non-US #2 */

/* Function keys */
#define GE_KEY_ESCAPE          ::GE::Key::Escape
#define GE_KEY_ENTER           ::GE::Key::Enter
#define GE_KEY_TAB             ::GE::Key::Tab
#define GE_KEY_BACKSPACE       ::GE::Key::Backspace
#define GE_KEY_INSERT          ::GE::Key::Insert
#define GE_KEY_DELETE          ::GE::Key::Delete
#define GE_KEY_RIGHT           ::GE::Key::Right
#define GE_KEY_LEFT            ::GE::Key::Left
#define GE_KEY_DOWN            ::GE::Key::Down
#define GE_KEY_UP              ::GE::Key::Up
#define GE_KEY_PAGE_UP         ::GE::Key::PageUp
#define GE_KEY_PAGE_DOWN       ::GE::Key::PageDown
#define GE_KEY_HOME            ::GE::Key::Home
#define GE_KEY_END             ::GE::Key::End
#define GE_KEY_CAPS_LOCK       ::GE::Key::CapsLock
#define GE_KEY_SCROLL_LOCK     ::GE::Key::ScrollLock
#define GE_KEY_NUM_LOCK        ::GE::Key::NumLock
#define GE_KEY_PRINT_SCREEN    ::GE::Key::PrintScreen
#define GE_KEY_PAUSE           ::GE::Key::Pause
#define GE_KEY_F1              ::GE::Key::F1
#define GE_KEY_F2              ::GE::Key::F2
#define GE_KEY_F3              ::GE::Key::F3
#define GE_KEY_F4              ::GE::Key::F4
#define GE_KEY_F5              ::GE::Key::F5
#define GE_KEY_F6              ::GE::Key::F6
#define GE_KEY_F7              ::GE::Key::F7
#define GE_KEY_F8              ::GE::Key::F8
#define GE_KEY_F9              ::GE::Key::F9
#define GE_KEY_F10             ::GE::Key::F10
#define GE_KEY_F11             ::GE::Key::F11
#define GE_KEY_F12             ::GE::Key::F12
#define GE_KEY_F13             ::GE::Key::F13
#define GE_KEY_F14             ::GE::Key::F14
#define GE_KEY_F15             ::GE::Key::F15
#define GE_KEY_F16             ::GE::Key::F16
#define GE_KEY_F17             ::GE::Key::F17
#define GE_KEY_F18             ::GE::Key::F18
#define GE_KEY_F19             ::GE::Key::F19
#define GE_KEY_F20             ::GE::Key::F20
#define GE_KEY_F21             ::GE::Key::F21
#define GE_KEY_F22             ::GE::Key::F22
#define GE_KEY_F23             ::GE::Key::F23
#define GE_KEY_F24             ::GE::Key::F24
#define GE_KEY_F25             ::GE::Key::F25

/* Keypad */
#define GE_KEY_KP_0            ::GE::Key::KP0
#define GE_KEY_KP_1            ::GE::Key::KP1
#define GE_KEY_KP_2            ::GE::Key::KP2
#define GE_KEY_KP_3            ::GE::Key::KP3
#define GE_KEY_KP_4            ::GE::Key::KP4
#define GE_KEY_KP_5            ::GE::Key::KP5
#define GE_KEY_KP_6            ::GE::Key::KP6
#define GE_KEY_KP_7            ::GE::Key::KP7
#define GE_KEY_KP_8            ::GE::Key::KP8
#define GE_KEY_KP_9            ::GE::Key::KP9
#define GE_KEY_KP_DECIMAL      ::GE::Key::KPDecimal
#define GE_KEY_KP_DIVIDE       ::GE::Key::KPDivide
#define GE_KEY_KP_MULTIPLY     ::GE::Key::KPMultiply
#define GE_KEY_KP_SUBTRACT     ::GE::Key::KPSubtract
#define GE_KEY_KP_ADD          ::GE::Key::KPAdd
#define GE_KEY_KP_ENTER        ::GE::Key::KPEnter
#define GE_KEY_KP_EQUAL        ::GE::Key::KPEqual

#define GE_KEY_LEFT_SHIFT      ::GE::Key::LeftShift
#define GE_KEY_LEFT_CONTROL    ::GE::Key::LeftControl
#define GE_KEY_LEFT_ALT        ::GE::Key::LeftAlt
#define GE_KEY_LEFT_SUPER      ::GE::Key::LeftSuper
#define GE_KEY_RIGHT_SHIFT     ::GE::Key::RightShift
#define GE_KEY_RIGHT_CONTROL   ::GE::Key::RightControl
#define GE_KEY_RIGHT_ALT       ::GE::Key::RightAlt
#define GE_KEY_RIGHT_SUPER     ::GE::Key::RightSuper
#define GE_KEY_MENU            ::GE::Key::Menu
