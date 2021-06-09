#pragma once

#ifndef _VertexArrayObject
#define _VertexArrayObject

#include <glad/glad.h>

#include <vector>

class VertexArrayObject {
public:
    VertexArrayObject() {
        glGenVertexArrays(1, &Buffer);
    }

    void Bind() const {
        glBindVertexArray(Buffer);
    }

    void Add(const void *, GLint, GLint);

    static void Unbind() {
        glBindVertexArray(0);
    }

private:
    GLuint Buffer = 0;
    std::vector<GLuint> Buffers;

};


#endif
