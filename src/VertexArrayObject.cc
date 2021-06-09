#include "VertexArrayObject.h"

void VertexArrayObject::Add(const void *Data, GLint Length, GLint AttribSize) {
    this->Bind();

    GLuint BufferObject;
    auto Index = (GLuint) Buffers.size();

    glGenBuffers(1, &BufferObject);
    Buffers.push_back(BufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[Index]);
    glBufferData(GL_ARRAY_BUFFER, Length * (GLint) sizeof(GLfloat), Data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(Index);
    glVertexAttribPointer(Index, AttribSize, GL_FLOAT, GL_FALSE, AttribSize * (GLint) sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    VertexArrayObject::Unbind();
}
