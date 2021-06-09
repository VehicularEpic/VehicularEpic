#pragma once

#ifndef _Webview
#define _Webview

#include "Shader.h"
#include "VertexArrayObject.h"

class Webview {
public:
    Webview();

    void Resize(int, int);

    void Paint(int, int, const void *);

    void Render();

private:
    GLuint Texture = 0;

    Shader ShaderProgram = Shader(
            "resources/shaders/webview.vs",
            "resources/shaders/webview.fs"
    );

    VertexArrayObject Object = VertexArrayObject();
};


#endif
