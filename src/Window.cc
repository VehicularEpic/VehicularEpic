#include "Window.h"

static void ErrorCallback(int Error, const char *Description) {
    fprintf(stderr, "GLFW Error: %s (%d)\n", Description, Error);
}

Window::Window(const std::string &Title) {
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

#if defined(OS_MAC)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Win = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);

    if (!Win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(Win, this);
    glfwSetInputMode(Win, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    glfwSetWindowSizeCallback(Win, Window::WindowSizeCallback);
    glfwSetWindowCloseCallback(Win, Window::WindowCloseCallback);

    glfwSetCursorPosCallback(Win, Window::CursorPosCallback);
    glfwSetCursorEnterCallback(Win, Window::CursorEnterCallback);

    glfwSetMouseButtonCallback(Win, Window::MouseButtonCallback);
    glfwSetScrollCallback(Win, Window::ScrollCallback);

    glfwSetKeyCallback(Win, Window::KeyCallback);
    glfwSetCharCallback(Win, Window::CharCallback);

    glfwMakeContextCurrent(Win);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSetFramebufferSizeCallback(Win, Window::FramebufferSizeCallback);
}

void Window::Show() {
    glfwShowWindow(Win);
    glfwGetWindowSize(Win, &Width, &Height);
}

void Window::Update() {
    glfwSwapBuffers(Win);
    glfwPollEvents();
}

void Window::Destroy() {
    glfwDestroyWindow(Win);
    glfwTerminate();
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(Win);
}

void Window::VSync(bool value) {
    glfwSwapInterval(value);
}

void Window::WindowCloseCallback(GLFWwindow *Win) {
    auto Instance = static_cast<Window *>(glfwGetWindowUserPointer(Win));

    for (const auto &listener : Instance->WindowCloseListeners) {
        listener();
    }
}

void Window::WindowSizeCallback(GLFWwindow *Win, int Width, int Height) {
    auto *Instance = static_cast<Window *>(glfwGetWindowUserPointer(Win));

    Instance->Width = Width;
    Instance->Height = Height;

    for (const auto &listener : Instance->WindowSizeListeners) {
        listener(Instance->Width, Instance->Height);
    }
}

void Window::FramebufferSizeCallback(GLFWwindow *Win, int Width, int Height) {
    auto Instance = static_cast<Window *>(glfwGetWindowUserPointer(Win));

    glViewport(0, 0, Width, Height);

    for (const auto &listener : Instance->FramebufferSizeListeners) {
        listener(Width, Height);
    }
}

void Window::CursorPosCallback(GLFWwindow *Win, double PosX, double PosY) {
    auto Instance = static_cast<Window *>(glfwGetWindowUserPointer(Win));

    for (const auto &listener : Instance->MouseMoveListeners) {
        listener(PosX, PosY);
    }
}

void Window::CursorEnterCallback(GLFWwindow *Win, int Entered) {
    auto Instance = static_cast<Window *>(glfwGetWindowUserPointer(Win));

    double PosX, PosY;
    glfwGetCursorPos(Win, &PosX, &PosY);

    if (GLFW_TRUE == Entered) {
        for (const auto &listener : Instance->MouseEnterListeners) {
            listener(PosX, PosY);
        }
    }

    if (GLFW_FALSE == Entered) {
        for (const auto &listener : Instance->MouseLeaveListeners) {
            listener(PosX, PosY);
        }
    }
}

void Window::MouseButtonCallback(GLFWwindow *Win, int Button, int Action, int Mods) {
    auto Instance = static_cast<Window *>(glfwGetWindowUserPointer(Win));

    double PosX, PosY;
    glfwGetCursorPos(Win, &PosX, &PosY);

    if (InputAction::Press == Action) {
        for (const auto &listener : Instance->MouseDownListeners) {
            listener(static_cast<MouseButton>(Button), PosX, PosY);
        }
    }

    if (InputAction::Release == Action) {
        for (const auto &listener : Instance->MouseUpListeners) {
            listener(static_cast<MouseButton>(Button), PosX, PosY);
        }
    }
}

void Window::ScrollCallback(GLFWwindow *Win, double OffsetX, double OffsetY) {
    auto Instance = static_cast<Window *>(glfwGetWindowUserPointer(Win));

    double PosX, PosY;
    glfwGetCursorPos(Win, &PosX, &PosY);

    for (const auto &listener : Instance->ScrollListeners) {
        listener(PosX, PosY, OffsetX * 100, OffsetY * 100);
    }
}

void Window::KeyCallback(GLFWwindow *Win, int Key, int Scancode, int Action, int Mods) {
    auto Instance = static_cast<Window *>(glfwGetWindowUserPointer(Win));

    if (GLFW_KEY_UNKNOWN == Key) {
        return;
    }

    if (!(GLFW_MOD_NUM_LOCK & Mods)) {
        if (GLFW_KEY_KP_0 == Key) {
            Key = GLFW_KEY_INSERT;
        }

        if (GLFW_KEY_KP_DECIMAL == Key) {
            Key = GLFW_KEY_DELETE;
        }

        if (GLFW_KEY_KP_1 == Key) {
            Key = GLFW_KEY_END;
        }

        if (GLFW_KEY_KP_2 == Key) {
            Key = GLFW_KEY_DOWN;
        }

        if (GLFW_KEY_KP_3 == Key) {
            Key = GLFW_KEY_PAGE_DOWN;
        }

        if (GLFW_KEY_KP_4 == Key) {
            Key = GLFW_KEY_LEFT;
        }

        if (GLFW_KEY_KP_5 == Key) {
            return;
        }

        if (GLFW_KEY_KP_6 == Key) {
            Key = GLFW_KEY_RIGHT;
        }

        if (GLFW_KEY_KP_7 == Key) {
            Key = GLFW_KEY_HOME;
        }

        if (GLFW_KEY_KP_8 == Key) {
            Key = GLFW_KEY_UP;
        }

        if (GLFW_KEY_KP_9 == Key) {
            Key = GLFW_KEY_PAGE_UP;
        }
    }

    if (InputAction::Press == Action || GLFW_REPEAT == Action) {
        for (const auto &listener : Instance->KeyDownListeners) {
            listener(Key, Mods);
        }
    }

    if (InputAction::Release == Action) {
        for (const auto &listener : Instance->KeyUpListeners) {
            listener(Key, Mods);
        }
    }
}

void Window::CharCallback(GLFWwindow *Win, unsigned int Codepoint) {
    auto Instance = static_cast<Window *>(glfwGetWindowUserPointer(Win));

    for (const auto &listener : Instance->TextListeners) {
        listener(Codepoint);
    }
}
