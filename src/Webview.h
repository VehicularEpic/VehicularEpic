#pragma once

#include "Shader.h"
#include "VertexArrayObject.h"

class Webview {
public:
    Webview();

    void Resize(int, int) const;

    void Paint(int, int, const void *) const;

    void Render();

private:
    GLuint Texture = 0;

    Shader ShaderProgram = Shader("webview.vs", "webview.fs");

    VertexArrayObject Object = VertexArrayObject();
};
