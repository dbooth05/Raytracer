#ifndef KEYCODES_H
#define KEYCODES_H

#include <stdint.h>
#include <iostream>

namespace BaseEngine {
    typedef enum class KeyCode : uint16_t {
        // from glfw3.h
        SPACE       = 32,   /*   */
        APOSTROPHE  = 39,   /* ' */
        COMMA       = 44,   /* , */
        MINUS       = 45,   /* - */
        PERIOD      = 46,   /* . */
        SLASH       = 47,   /* / */

        DO = 48,    /* 0 */
        D1 = 49,    /* 1 */
        D2 = 50,    /* 2 */
        D3 = 51,    /* 3 */
        D4 = 52,    /* 4 */
        D5 = 53,    /* 5 */
        D6 = 54,    /* 6 */
        D7 = 55,    /* 7 */
        D8 = 56,    /* 8 */
        D9 = 57,    /* 9 */

        SEMICOLON   = 59,   /* ; */
        EQUAL       = 61,   /* = */

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

        LEFTBRACKET     = 91,   /* [ */
        BACKSLASH       = 92,   /* \ */
        RIGHTBRACKET    = 93,   /* ] */
        GRAVEACCENT     = 94,   /* ` */

        /* FUNCTION KEYS */
        ESCAPE      = 256,
        ENTER       = 257,
        TAB         = 258,
        BACKSPACE   = 259,
        INSERT      = 260,
        DELETE      = 261,
        ARROW_RIGHT = 262,
        ARROW_LEFT  = 263,
        ARROW_DOWN  = 264,
        ARROW_UP    = 265,
        PAGE_UP     = 266,
        PAGE_DOWN   = 267,
        HOME        = 268,
        END         = 269,
        CAPS_LOCK   = 280,
        SCROLL_LOCK = 281,
        NUM_LOCK    = 282,
        PRINT_SCRN  = 283,
        PAUSE       = 284,

        F1  = 290,
        F2  = 291,
        F3  = 292,
        F4  = 293,
        F5  = 294,
        F6  = 295,
        F7  = 296,
        F8  = 297,
        F9  = 298,
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

        /* KEYPAD */
        KPO = 320,  /* 0 */
        KP1 = 321,  /* 1 */
        KP2 = 322,  /* 2 */
        KP3 = 323,  /* 3 */
        KP4 = 324,  /* 4 */
        KP5 = 325,  /* 5 */
        KP6 = 326,  /* 6 */
        KP7 = 327,  /* 7 */
        KP8 = 328,  /* 8 */
        KP9 = 329,  /* 9 */

        KP_DECIMAL  = 330,  /* . */
        KP_DIVIDE   = 331,  /* / */
        KP_MULTIPLY = 332,  /* * */
        KP_SUBTRACT = 333,  /* - */
        KP_ADD      = 334,  /* + */
        KP_ENTER    = 335,
        KP_EQUAL    = 336,

        /* OTHER KEYS */
        LEFT_SHIFT  = 340,
        LEFT_CTRL   = 341,
        LEFT_ALT    = 342,
        LEFT_SUPER  = 343,
        RIGHT_SHIFT = 344,
        RIGHT_CTRL  = 345,
        RIGHT_ALT   = 346,
        RIGHT_SUPER = 347,
        MENU        = 348
    } Key;

    enum class KeyState {
        NONE = -1,
        PRESSED,
        HELD,
        RELEASED
    };

    enum class CursorMode {
        NORMAL = 0,
        HIDDEN = 1,
        LOCKED = 2
    };

    typedef enum class MouseButton : uint16_t {
        B0 = 0,
        B1 = 1,
        B2 = 2,
        B3 = 3,
        B4 = 4,
        B5 = 5,
        LEFT = B0,
        RIGHT = B1,
        MIDDLE = B2
    } Button;

    inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode) {
        os << static_cast<int32_t>(keyCode);
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, MouseButton button) {
        os << static_cast<int32_t>(button);
        return os;
    }
}

#endif
