#pragma once

#ifndef _Shader
#define _Shader

#include <glad/glad.h>

#include <string>
#include <vector>

class Shader {
public:
    Shader(const std::string &, const std::string &);

    void Bind() const {
        glUseProgram(this->Program);
    }

    static void Unbind() {
        glUseProgram(0);
    }

private:
    GLuint Program = glCreateProgram();

    static void Compile(const std::string &, GLuint, GLenum);
};


#endif
