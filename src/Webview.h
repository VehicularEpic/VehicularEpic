#pragma once

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

    Shader ShaderProgram = Shader("webview.vs", "webview.fs");

    VertexArrayObject Object = VertexArrayObject();
};
