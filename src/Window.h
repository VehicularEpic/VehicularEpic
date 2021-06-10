#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <string>
#include <vector>
#include <functional>

#include "InputAction.h"
#include "MouseButton.h"

#define LISTENER(type)                      \
private:                                    \
    std::vector<type> type ## s;            \
                                            \
public:                                     \
    void Add##type(const type &listener) {  \
        type ## s.push_back(listener);      \
    }

class Window {

    typedef std::function<void()> WindowCloseListener;

    typedef std::function<void(int, int)> SizeListener;
    typedef SizeListener WindowSizeListener;
    typedef SizeListener FramebufferSizeListener;

    typedef std::function<void(double, double)> MouseListener;
    typedef MouseListener MouseMoveListener;
    typedef MouseListener MouseEnterListener;
    typedef MouseListener MouseLeaveListener;

    typedef std::function<void(MouseButton, double, double)> MouseButtonListener;
    typedef MouseButtonListener MouseDownListener;
    typedef MouseButtonListener MouseUpListener;

    typedef std::function<void(double, double, double, double)> ScrollListener;

    typedef std::function<void(int, int)> KeyListener;
    typedef KeyListener KeyDownListener;
    typedef KeyListener KeyUpListener;

    typedef std::function<void(unsigned int)> TextListener;

LISTENER(WindowCloseListener)

LISTENER(WindowSizeListener)

LISTENER(FramebufferSizeListener)

LISTENER(MouseMoveListener)

LISTENER(MouseEnterListener)

LISTENER(MouseLeaveListener)

LISTENER(MouseDownListener)

LISTENER(MouseUpListener)

LISTENER(ScrollListener)

LISTENER(KeyDownListener)

LISTENER(KeyUpListener)

LISTENER(TextListener)


public:
    explicit Window(const std::string &);

    void Show();

    void Update();

    void Destroy();

    bool ShouldClose();

    static void VSync(bool);

    int GetWidth() const {
        return Width;
    }

    int GetHeight() const {
        return Height;
    }

private:
    GLFWwindow *Win;

    int Width = 1280;
    int Height = 720;

    static void WindowCloseCallback(GLFWwindow *);

    static void WindowSizeCallback(GLFWwindow *, int, int);

    static void FramebufferSizeCallback(GLFWwindow *, int, int);

    static void CursorPosCallback(GLFWwindow *, double, double);

    static void CursorEnterCallback(GLFWwindow *, int);

    static void MouseButtonCallback(GLFWwindow *, int, int, int);

    static void ScrollCallback(GLFWwindow *, double, double);

    static void KeyCallback(GLFWwindow *, int, int, int, int);

    static void CharCallback(GLFWwindow *, unsigned int);
};
