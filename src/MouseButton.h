#pragma once

#ifndef _MouseButton
#define _MouseButton

#include <GLFW/glfw3.h>

enum MouseButton : int {

    Left = GLFW_MOUSE_BUTTON_LEFT,
    Right = GLFW_MOUSE_BUTTON_RIGHT,
    Middle = GLFW_MOUSE_BUTTON_MIDDLE

};

#endif
